#pragma once

/* subsystem template

class NAME {
private:
  NAME() { }
  ~NAME() { }

  static std::set<ECS::entity> entities;
  static ECS::component_bits subsystem_bits;

  static void found(const ECS::entity ent) { return (entities.find(ent) != entities.cend()); }

  static void observer(const ECS::entity& ent, const ECS::component_bits& ent_bits) {
    const ECS::component_bits final_bits = ent_bits & subsystem_bits;
    const bool same_bits = (final_bits == subsystem_bits),
      found_ent = found(ent);

    if (same_bits && !found_ent)
      entities.insert(ent);

    else if (!same_bits && found_ent)
      entities.erase(ent);

  }

public:
  static void init(const ECS::component_bits bits) {
    subsystem_bits = bits;
    ECS::add_bits_observer(observer);
  }

  static void work() {
    ...
  }

}; // NAME

*/



// subsystems definitions

#ifdef __INTERN__

// std::set<ECS::entity> NAME::entities;
// ECS::component_bits NAME::subsystem_bits;

#endif
