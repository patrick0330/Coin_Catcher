#include "GameObject.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

GameObject::GameObject(float positions[]) {
	Position_x = positions[0];
	Position_x_size = positions[1];
	Position_y = positions[2];
	Position_y_size = positions[3];
}