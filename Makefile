default:
	g++ src/*.cpp -o main \
	-I include \
	-Wall \
	-lSDL2main -lSDL2 -lSDL2_image
