/**********************************************************************************************
 *
 *   raylib - Advance Game template
 *
 *   Options Screen Functions Definitions (Init, Update, Draw, Unload)
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

#include "raygui.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

Rectangle pop = {.x = (SCREEN_W / 2) - (RECT_W / 2),
                 .y = (SCREEN_H / 2) - (RECT_H / 2),
                 .width = RECT_W,
                 .height = RECT_H};

PopSettings pop_options_sets = {
    .h1_title = "IP Settings",
    .h2_title = "Please, enter the data",
    .ip_title = "IP Adress",
    .port_title = "Port",
    .h1_title_size = 24,
    .h2_title_size = 18,
    .ip_port_size = 12,
};

Rectangle cancel_button = {.x = (SCREEN_W / 2) - ((RECT_W / 4) * 1.5) + 5,
                           .y = SCREEN_H - RECT_H + 15,
                           .width = (RECT_W / 4),
                           .height = (RECT_H / 7)};

Rectangle apply_button = {.x = (SCREEN_W / 2) + ((RECT_W / 4) / 2) - 5,
                          .y = SCREEN_H - RECT_H + 15,
                          .width = (RECT_W / 4),
                          .height = (RECT_H / 7)};

Rectangle ip_input_box = {.x = (SCREEN_W / 2) - 115,
                          .y = (SCREEN_H / 2) + 10,
                          .height = 30,
                          .width = 90};

Rectangle port_input_box = {.x = (SCREEN_W / 2) + 25,
                            .y = (SCREEN_H / 2) + 10,
                            .height = 30,
                            .width = 90};

IpSettings sets = {{0, 0, 0, 0}, 5600};
char ip_str[16];
char port_str[6];

bool back_pressed = false;
bool editMode1 = false;
bool editMode2 = false;

//----------------------------------------------------------------------------------
// Options Screen Functions Definition
//----------------------------------------------------------------------------------

// Options Screen Initialization logic
void InitOptionsScreen(void) {
  // TODO: Initialize OPTIONS screen variables here!

  // Init text sizes
  InitOptionsTextSize();

  framesCounter = 0;
  finishScreen = 0;
  back_pressed = false;
  editMode1 = false;
  editMode2 = false;
}

// Options Screen Update logic
void UpdateOptionsScreen(void) {
  // TODO: Update OPTIONS screen variables here!
  if (back_pressed) {
    finishScreen = 1;
  }

  // Focus/Defocus on text input
  if (CheckCollisionPointRec(GetMousePosition(), ip_input_box)) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      editMode1 = true;
      editMode2 = false;
    }
  }
  if (CheckCollisionPointRec(GetMousePosition(), port_input_box)) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      editMode1 = false;
      editMode2 = true;
    }
  }
  if (!CheckCollisionPointRec(GetMousePosition(), ip_input_box) &&
      !CheckCollisionPointRec(GetMousePosition(), port_input_box)) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      editMode1 = false;
      editMode2 = false;
    }
  }
}

// Options Screen Draw logic
void DrawOptionsScreen(void) {
  // TODO: Draw OPTIONS screen here!
  if (GuiWindowBox(pop, "IP Settings")) {
    back_pressed = true;
  }

  DrawText(pop_options_sets.h1_title,
           pop.x + (pop.width / 2) - (pop_options_sets.h1_title_width / 2),
           pop.y + 35, pop_options_sets.h1_title_size, BLACK);
  DrawText(pop_options_sets.h2_title,
           pop.x + (pop.width / 2) - (pop_options_sets.h2_title_width / 2),
           pop.y + 63, pop_options_sets.h2_title_size, BLACK);

  DrawText(pop_options_sets.ip_title, (SCREEN_W / 2) - 100, (SCREEN_H / 2) - 7,
           pop_options_sets.ip_port_size, BLACK);
  DrawText(pop_options_sets.port_title,
           (SCREEN_W / 2) + 83 - pop_options_sets.ip_port_width,
           (SCREEN_H / 2) - 7, pop_options_sets.ip_port_size, BLACK);

  if (GuiTextBox(ip_input_box, ip_str, 16, editMode1)) {
    sscanf(ip_str, "%hhu.%hhu.%hhu.%hhu", &sets.ip[0], &sets.ip[1], &sets.ip[2],
           &sets.ip[3]);
    printf("Updated IP: %d.%d.%d.%d\n", sets.ip[0], sets.ip[1], sets.ip[2],
           sets.ip[3]);
  }

  if (GuiTextBox(port_input_box, port_str, 6, editMode2)) {
    sscanf(port_str, "%hd", &sets.port);
    printf("Updated PORT: %d\n", sets.port);
  }

  if (GuiButton(cancel_button, "Cancel")) {
    back_pressed = true;
  }
  if (GuiButton(apply_button, "Apply")) {
    // Actions for save the data
    editMode1 = false;
    editMode2 = false;
    printf("Your ip: %s\nYour port: %s\n", ip_str, port_str);
  }
}

// Options Screen Unload logic
void UnloadOptionsScreen(void) {
  // TODO: Unload OPTIONS screen variables here!
}

// Options Screen should finish?
int FinishOptionsScreen(void) { return finishScreen; }

void InitOptionsTextSize(void) {
  pop_options_sets.h1_title_width =
      MeasureText(pop_options_sets.h1_title, pop_options_sets.h1_title_size);
  pop_options_sets.h2_title_width =
      MeasureText(pop_options_sets.h2_title, pop_options_sets.h2_title_size);
  pop_options_sets.ip_port_width =
      MeasureText(pop_options_sets.port_title, pop_options_sets.ip_port_size);
}