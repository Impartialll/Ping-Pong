/**********************************************************************************************
 *
 *   raylib - Advance Game template
 *
 *   Title Screen Functions Definitions (Init, Update, Draw, Unload)
 *
 *   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
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

#include "game.h"
#include "screens.h"
#include <stdio.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------

Rectangle pop_welcome_size = {.x = (SCREEN_W / 2) - (RECT_W / 2),
                              .y = (SCREEN_H / 2) - (RECT_H / 2),
                              .width = RECT_W,
                              .height = RECT_H};

Rectangle central_buttons = {.x = (SCREEN_W / 2) - 80,
                             .y = SCREEN_H / 2 + 30,
                             .width = 80,
                             .height = (RECT_H / 7)};

PopSettings pop_welcome_sets = {
    .h1_title = "Hello and Welcome to the",
    .h2_title = "Pong",
    .choose_mode = "Choose the game mode",
    .h1_title_size = 18,
    .h2_title_size = 24,
};

static int framesCounter = 0;
static int finishScreen = 0;
bool singleplayer = false;
bool multiplayer = false;

//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void) {
  // TODO: Initialize TITLE screen variables here!

  // Init text sizes
  InitTitleTextSize();

  framesCounter = 0;
  finishScreen = 0;
  singleplayer = false;
  multiplayer = false;
}

// Title Screen Update logic
void UpdateTitleScreen(void) {
  // TODO: Update TITLE screen variables here!
  if (multiplayer) {
    finishScreen = 1; // Move to OPTIONS
  } else if (singleplayer) {
    finishScreen = 2; // Move to GAMEPLAY
  }
}

// Title Screen Draw logic
void DrawTitleScreen(void) {
  if (GuiWindowBox(pop_welcome_size, "Pong start")) {
  }

  DrawText(pop_welcome_sets.h1_title,
           pop_welcome_size.x + (pop_welcome_size.width / 2) -
               (pop_welcome_sets.h1_title_width / 2),
           pop_welcome_size.y + 35, pop_welcome_sets.h1_title_size, BLACK);
  DrawText(pop_welcome_sets.h2_title,
           pop_welcome_size.x + (pop_welcome_size.width / 2) -
               (pop_welcome_sets.h2_title_width / 2),
           pop_welcome_size.y + 60, pop_welcome_sets.h2_title_size, VIOLET);

  GuiDrawText(pop_welcome_sets.choose_mode,
              (Rectangle){SCREEN_W / 2 - 60, SCREEN_H / 2, 120,
                          (pop_welcome_size.height / 7)},
              1, BLACK);

  if (GuiButton(central_buttons, "Singleplayer")) {
    singleplayer = true;
  }

  if (GuiButton((Rectangle){SCREEN_W / 2, SCREEN_H / 2 + 30, 80,
                            pop_welcome_size.height / 7},
                "Multiplayer")) {
    multiplayer = true;
  }
}

// Title Screen Unload logic
void UnloadTitleScreen(void) {
  // TODO: Unload TITLE screen variables here!
}

// Title Screen should finish?
int FinishTitleScreen(void) { return finishScreen; }

void InitTitleTextSize(void) {
  pop_welcome_sets.h1_title_width =
      MeasureText(pop_welcome_sets.h1_title, pop_welcome_sets.h1_title_size);
  pop_welcome_sets.h2_title_width =
      MeasureText(pop_welcome_sets.h2_title, pop_welcome_sets.h2_title_size);
  pop_welcome_sets.ip_port_width =
      MeasureText(pop_welcome_sets.port_title, pop_welcome_sets.ip_port_size);
}