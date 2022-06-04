/****************************************************************************
GFC - Games Fundamental Classes version 2.60
Copyright (C) 2009-2018 Jarek Francik, Kingston University London

This work is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License:
http://creativecommons.org/licenses/by-sa/4.0/

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Created by Jarek Francik
jarek@kingston.ac.uk
****************************************************************************/
#pragma once

#ifndef GFC_VERSION
#define GFC_VERSION	160
#endif

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_net.h"
#include "SDL_ttf.h"
#include "SDL_rotozoom.h"
#include "SDL_gfxPrimitives.h"

#ifndef max
#define max(x, y)	((x) > (y) ? (x) : (y))
#endif

#ifndef min
#define min(x, y)	((x) < (y) ? (x) : (y))
#endif

#ifndef RAD2DEG
#define RAD2DEG(x)	((float)(x) * 180.0f / (float)M_PI)
#endif

#ifndef DEG2RAD
#define DEG2RAD(x)  ((float)(x) * (float)M_PI / 180.0f)
#endif

#include <sstream>

#ifdef _USRDLL
   #define EXT_DECL		__declspec(dllexport)
#else
   #define EXT_DECL		__declspec(dllimport)
#endif


#include "Color.h"
#include "Vector.h"
#include "Rectangle.h"
#include "GameApp.h"
#include "Game.h"
#include "Graphics.h"
#include "Sprite.h"
#include "SpriteRect.h"
#include "SpriteOval.h"
#include "SpriteText.h"
#include "SpriteContainer.h"
#include "Sound.h"
#include "Font.h"


