#pragma once
#include <glew.h>
#include <SOIL/SOIL.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "SDL/SDL_rwops.h"

// Load a texture into opengl 
int loadPNG(std::string file);
