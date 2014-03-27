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

// ---------------------------------------- //
//       Helper Methods                     //
// ---------------------------------------- // 

// Convert int to string
std::string toString(int value);

// Convert double to string
std::string toString(double value);

// Convert string to int
int toInt(std::string s);

// Convert string to double
double toDouble(std::string s);

// Return setting from file 
std::string getSetting(std::string fileString, std::string setting);
