#pragma once

#include <map>
#include <set>
#include <bitset>
#include <functional>
#include <memory>
#include <typeinfo>
#include <cstddef>



class ECS {
public:
  using entity = std::uint8_t;
  static constexpr entity max_entities = __UINT8_MAX__;

  using component_id = std::uint8_t;
  static constexpr component_id max_components = __UINT8_MAX__;
  using component_bits = std::bitset<max_components>;

  using function = std::function<void(const entity&, const component_bits&)>;

private:
  ECS() { }
  ~ECS() { }

  class entity_manager {
  private:
    entity_manager() { }
    ~entity_manager() { }

    static unsigned index__;
    static std::map<entity, component_bits> entities__;
    static std::vector<function> observers__;

    static bool max_size() { return (entities__.size() >= max_entities); }
    static bool found(const entity ent) { return (entities__.find(ent) != entities__.cend()); }

    static void call_observers(const entity ent) {

      for (const auto& obs : observers__) {

	const auto& ent_bits = entities__[ent];
	obs(ent, ent_bits);

      }

    }

  public:
    static void add_observer(const function& observer) { observers__.push_back(observer); }

    static entity add_entity(const component_bits ent_bits) {
      if (max_size()) {
	std::cout << "ERROR: could not add entity" << std::endl;
	return index__;
      }

      const entity new_ent = index__++;

      entities__[new_ent] = ent_bits;
      call_observers(new_ent);
      return new_ent;
    }

    static void destroy_entity(const entity ent){
      if (!found(ent)) {
	std::cout << "ERROR: could not destroy entity" << std::endl;
	return;
      }

      entities__[ent].reset();
      call_observers(ent);
      entities__.erase(ent);
    }
    

    static void bits(const entity ent, const component_bits ent_bits) {
      if (!found(ent)) {
	std::cout << "ERROR: could not find entity" << std::endl;
	return;
      }

      entities__[ent] = ent_bits;
      call_observers(ent);
    }

    static component_bits bits(const entity ent) {
      if (!found(ent)) {
	std::cout << "ERROR: could not find entity" << std::endl;
	return 0;
      }

      return entities__[ent];
    }


  }; // entity_manager



  class base_component_container {
  public:
    virtual ~base_component_container() { }

    virtual void remove_component(const entity ent) = 0;

  };

  template<class T>
  class component_container : public base_component_container {
  private:
    std::map<entity, T> components__;

    bool max_size() const { return (this->components__.size() >= max_entities); }
    bool found(const entity ent) const { return (this->components__.find(ent) != this->components__.cend()); }

  public:
    void component(const entity ent, const T data) {
      if (this->max_size()) {
	std::cout << "ERROR: could not add component" << std::endl;
	return;
      }

      this->components__[ent] = data;
    }

    const T* component(const entity ent) {
      if (!(this->found(ent))) {
	std::cout << "ERROR: could not find component" << std::endl;
	return nullptr;
      }

      const T* comp = &(this->components__[ent]);
      return comp;
    }

    void remove_component(const entity ent) override {
      if (!(this->found(ent))) {
	std::cout << "ERROR: could not remove component" << std::endl;
	return;
      }

      this->components__.erase(ent);
    }

  }; // component_container

  class component_manager {
  private:
    component_manager() { }
    ~component_manager() { }

    static component_id current_id__;
    static std::map<const char*, component_id> ids__;
    static std::map<component_id, std::shared_ptr<base_component_container>> containers__;

    static bool max_size() { return (containers__.size() >= max_components); }
    static bool found(const char* name) { return (ids__.find(name) != ids__.cend()); }

  public:
    template<class T>
    static void register_component() {
      const char* name = typeid(T).name();

      if (found(name) || max_size()) {
	std::cout << "ERROR: could not register component" << std::endl;
	return;
      }

      const component_id id = current_id__++;

      ids__[name] = id;
      containers__[id] = std::make_shared<component_container<T>>();
    }



    template<class T>
    static component_id id() {
      const char* name = typeid(T).name();

      if (!found(name)) {
	std::cout << "ERROR: could not find component" << std::endl;
	return current_id__;
      }

      return ids__[name];
    }

    template<class T>
    static void component(const entity ent, const T data) {
      const char* name = typeid(T).name();

      if (!found(name)) {
	std::cout << "ERROR: could not find component" << std::endl;
	return;
      }

      const component_id id = ids__[name];
      auto components = std::static_pointer_cast<component_container<T>>(containers__[id]);

      components->component(ent, data);
    }

    template<class T>
    static const T* component(const entity ent) {
      const char* name = typeid(T).name();

      if (!found(name)) {
	std::cout << "ERROR: could not find component" << std::endl;
	return nullptr;
      }

      const component_id id = ids__[name];
      auto components = std::static_pointer_cast<component_container<T>>(containers__[id]);

      return components->component(ent);
    }

    template<class T>
    static void remove_component(const entity ent) {
      const char* name = typeid(T).name();

      if (!found(name)) {
	std::cout << "ERROR: could not find component" << std::endl;
	return;
      }

      const component_id id = ids__[name];
      auto components = std::static_pointer_cast<component_container<T>>(containers__[id]);

      components->remove_component(ent);
    }


    static void remove_all_components(const entity ent) {

      for (const auto components : containers__)
	components.second->remove_component(ent);

    }

  }; // component_manager

public:
  static void add_bits_observer(const function& observer) { entity_manager::add_observer(observer); }

  static entity add_entity(const component_bits ent_bits = 0) { return entity_manager::add_entity(ent_bits); }
  static void destroy_entity(const entity ent) {
    component_manager::remove_all_components(ent);
    entity_manager::destroy_entity(ent);
  }




  template<class T>
  static void register_component() { component_manager::register_component<T>(); }

  template<class T>
  static component_id id() { return component_manager::id<T>(); }

  template<class T>
  static void component(const entity ent, const T data) {
    component_id index = id<T>();
    component_bits ent_bits = entity_manager::bits(ent);
    ent_bits.set(index);

    component_manager::component<T>(ent, data);
    entity_manager::bits(ent, ent_bits);
  }

  template<class T>
  static const T* component(const entity ent) { return component_manager::component<T>(ent); }

  template<class T>
  static void remove_component(const entity ent) {
    component_id index = id<T>();
    component_bits ent_bits = entity_manager::bits(ent);
    ent_bits.set(index, 0);

    component_manager::remove_component<T>(ent);
    entity_manager::bits(ent, ent_bits);
  }

#include <ECS/subsystem.hpp>

};
