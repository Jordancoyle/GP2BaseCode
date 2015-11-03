#ifndef _COMMON_H
#define _COMMON_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>
#include <vector>

using namespace std;
using namespace glm;

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const string ASSET_PATH = "assets";
const string SHADER_PATH = "/shaders";
const string TEXTURE_PATH = "/textures";
const string FONT_PATH = "/fonts";
const string MODEL_PATH = "/models";

#endif
