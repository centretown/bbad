/**********************************************************************************************
 *
 *   raylib.lights - Some useful functions to deal with lights data
 *
 *   CONFIGURATION:
 *
 *   #define RLIGHTS_IMPLEMENTATION
 *       Generates the implementation of the library into the included file.
 *       If not defined, the library is in header only mode and can be included
 *in other headers or source files without problems. But only ONE file should
 *hold the implementation.
 *
 *   LICENSE: zlib/libpng
 *
 *   Copyright (c) 2017-2024 Victor Fisac (@victorfisac) and Ramon Santamaria
 *(@raysan5)
 *
 *   This software is provided "as-is", without any express or implied warranty.
 *In no event will the authors be held liable for any damages arising from the
 *use of this software.
 *
 *   Permission is granted to anyone to use this software for any purpose,
 *including commercial applications, and to alter it and redistribute it freely,
 *subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must not
 *claim that you wrote the original software. If you use this software in a
 *product, an acknowledgment in the product documentation would be appreciated
 *but is not required.
 *
 *     2. Altered source versions must be plainly marked as such, and must not
 *be misrepresented as being the original software.
 *
 *     3. This notice may not be removed or altered from any source
 *distribution.
 *
 **********************************************************************************************/

#ifndef RLIGHTS_H
#define RLIGHTS_H

#include "raylib.h"

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
#define MAX_LIGHTS 4 // Max dynamic lights supported by shader

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

// Light data
typedef struct {
  int type;
  bool enabled;
  Vector3 position;
  Vector3 target;
  Color color;
  float attenuation;

  // Shader locations
  int enabledLoc;
  int typeLoc;
  int positionLoc;
  int targetLoc;
  int colorLoc;
  int attenuationLoc;
} Light;

// Light type
typedef enum { LIGHT_DIRECTIONAL = 0, LIGHT_POINT } LightType;

#endif // RLIGHTS_H
