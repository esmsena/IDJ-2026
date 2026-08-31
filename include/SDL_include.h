#ifndef SDL_INCLUDE_H
#define SDL_INCLUDE_H

#if defined(_WIN32)
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#elif defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#endif

#endif
