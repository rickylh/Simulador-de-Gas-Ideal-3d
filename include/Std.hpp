#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#include <GL/glew.h>

#ifdef __WINDOWS__
#include <SDL.h>
#include <SDL_opengl.h>

#else

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4 getIdentidade4x4();
