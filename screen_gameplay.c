/**********************************************************************************************
 *
 *   raylib - Advance Game template
 *
 *   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
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
#include <stdbool.h>
#include <stdio.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------

WindowSettings window = {
    .title = "Ping pong",
    .footer = "Created by two geniuses",
    .screenWidth = SCREEN_W,
    .screenHeight = SCREEN_H,
    .targetFPS = 60,
    .fontSize = (SCREEN_W / SCREEN_H) * 50,
};
WindowRect rect = {
    .rectWidth = SCREEN_W / 2 + 200,
    .rectHeight = SCREEN_H / 2 + 40,
    .rectX = (SCREEN_W - (SCREEN_W / 2 + 200)) / 2,
    .rectY = (SCREEN_H - (SCREEN_H / 2 + 40)) / 2,
};

GameState state = {.countdown = 3, .countdownTimer = 0.0f, .gamePaused = true};

// Ball properties
Ball ball = {.position = {SCREEN_H / 2.0f, SCREEN_H / 2.0f},
             .speed = {350},
             .radius = 15.0f};

// Paddles properties
Paddle pd = {.paddleWidth = 20,
             .paddleHeight = 100,
             .leftPaddleX = 100,
             .rightPaddleX = SCREEN_W - 120};

Player player1 = {
    .score = 0,
    .position_y = (SCREEN_H - 100) / 2,
};

Player player2 = {
    .score = 0,
    .position_y = (SCREEN_H - 100) / 2,
};

static int framesCounter = 0;
static int finishScreen = 0;

bool show_start_popup = false;
bool mouse_on_the_frame = false;

Vector2 mouse_pos = (Vector2){0, 0};

char key_string[2];
char *up_down = NULL;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void) {
  // TODO: Initialize GAMEPLAY screen variables here!

  player1.position_y = (SCREEN_H - 100) / 2;
  player2.position_y = (SCREEN_H - 100) / 2;

  framesCounter = 0;
  finishScreen = 0;
  show_start_popup = false;
  mouse_on_the_frame = false;
  mouse_pos = (Vector2){5, 630};
  ResetBall(&ball, window.screenWidth, window.screenHeight);
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void) {
  // TODO: Update GAMEPLAY screen variables here!
  // Limit the player's rectangle Y position to stay within the larger
  // rectangle
  if (player1.position_y < rect.rectY)
    player1.position_y = rect.rectY;
  if (player1.position_y + pd.paddleHeight > rect.rectY + rect.rectHeight)
    player1.position_y = rect.rectY + rect.rectHeight - pd.paddleHeight;

  if (player2.position_y < rect.rectY)
    player2.position_y = rect.rectY;
  if (player2.position_y + pd.paddleHeight > rect.rectY + rect.rectHeight)
    player2.position_y = rect.rectY + rect.rectHeight - pd.paddleHeight;

  // Back to the menu if Esc pressed
  if (IsKeyPressed(KEY_BACKSPACE)) {
    singleplayer = false;
    show_start_popup = true;
    state.gamePaused = true;
    state.countdown = 3;
    ResetBall(&ball, window.screenWidth, window.screenHeight);
    finishScreen = 1; // Back to TITLE
  }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void) {
  // TODO: Draw GAMEPLAY screen here!

  mouse_pos = GetMousePosition();
  bool mouse_on_the_frame =
      CheckCollisionPointRec(mouse_pos, (Rectangle){5, 5, 630, 455});

  if (mouse_on_the_frame) {
    if (state.gamePaused) {
      state.countdownTimer += GetFrameTime();
      if (state.countdownTimer >= 1.0f) {
        state.countdownTimer = 0.0f;
        state.countdown--;
        if (state.countdown <= 0) {
          state.gamePaused = false;
        }
      }
    } else {
      // Ball movement
      ball.position.x += ball.speed.x * GetFrameTime();
      ball.position.y += ball.speed.y * GetFrameTime();

      // Ball collision with top and bottom screen boundaries
      if (ball.position.y <= ball.radius ||
          ball.position.y >= window.screenHeight - ball.radius) {
        ball.speed.y *= -1;
      }

      // Ball collision with paddles
      if (ball.position.x - ball.radius <= pd.leftPaddleX + pd.paddleWidth &&
          ball.position.y >= player1.position_y &&
          ball.position.y <= player1.position_y + pd.paddleHeight) {
        ball.speed.x *= -1;
        ball.speed.y +=
            (ball.position.y - (player1.position_y + pd.paddleHeight / 2)) * 2;
      }

      if (ball.position.x + ball.radius >= pd.rightPaddleX &&
          ball.position.y >= player2.position_y &&
          ball.position.y <= player2.position_y + pd.paddleHeight) {
        ball.speed.x *= -1;
        ball.speed.y +=
            (ball.position.y - (player2.position_y + pd.paddleHeight / 2)) * 2;
      }

      // Ball collision with center rectangle boundaries
      if (ball.position.x - ball.radius < rect.rectX ||
          ball.position.x + ball.radius > rect.rectX + rect.rectWidth) {
        ball.speed.x *= -1;
      }
      if (ball.position.y - ball.radius < rect.rectY ||
          ball.position.y + ball.radius > rect.rectY + rect.rectHeight) {
        ball.speed.y *= -1;
      }

      // Goal!
      if (ball.position.x + ball.radius > pd.rightPaddleX + pd.paddleWidth) {
        player1.score++;
        state.gamePaused = true;
        state.countdown = 3;
        player1.position_y = (SCREEN_H - 100) / 2;
        player2.position_y = (SCREEN_H - 100) / 2;
        ResetBall(&ball, window.screenWidth, window.screenHeight);
      } else if (ball.position.x - ball.radius < pd.leftPaddleX) {
        player2.score++;
        state.gamePaused = true;
        state.countdown = 3;
        player1.position_y = (SCREEN_H - 100) / 2;
        player2.position_y = (SCREEN_H - 100) / 2;
        ResetBall(&ball, window.screenWidth, window.screenHeight);
      }
    }
  } else {
    state.gamePaused = true;
    state.countdown = 3;
  }

  // Playing field
  DrawRectangleLines(rect.rectX, rect.rectY, rect.rectWidth, rect.rectHeight,
                     BLACK);

  DrawText(
      window.title,
      (window.screenWidth - (strlen(window.title) * (window.fontSize / 2))) / 2,
      (window.fontSize / 2), window.fontSize, WHITE);

  DrawText(window.footer,
           (window.screenWidth - MeasureText(window.footer, 14)) / 2,
           window.screenHeight - 35, 14, BLACK);

  // Draw ball
  DrawCircleV(ball.position, ball.radius, BLACK);

  // Draw players
  if (mouse_on_the_frame) {
    DrawRectangle(100, player1.position_y, 20, 100, Fade(GREEN, 0.9f));

    DrawRectangle(pd.rightPaddleX, player2.position_y, pd.paddleWidth,
                  pd.paddleHeight, Fade(RED, 0.9f));
  }

  // Draw scores
  DrawText(TextFormat("Player 1: %d", player1.score), 70, 70, 20, BLACK);
  DrawText(TextFormat("Player 2: %d", player2.score), window.screenWidth - 140,
           70, 20, BLACK);

  // Draw countdown
  if (state.gamePaused && state.countdown > 0) {
    const char *countdownText = TextFormat("%d", state.countdown);
    int textWidth = MeasureText(countdownText, 60);
    DrawRectangle((window.screenWidth / 2) - (textWidth / 2) - 10,
                  window.screenHeight / 2 - (60 / 2) - 10, textWidth + 20,
                  60 + 20, LIGHTGRAY);
    DrawText(countdownText, (window.screenWidth / 2) - (textWidth / 2),
             window.screenHeight / 2 - (60 / 2), 60, BLACK);
  }

  // Draw pause
  if (!mouse_on_the_frame) {
    int textWidth = MeasureText("Pause", 60);
    DrawRectangle((window.screenWidth / 2) - (textWidth / 2) - 10,
                  window.screenHeight / 2 - (60 / 2) - 10, textWidth + 20,
                  60 + 20, LIGHTGRAY);
    DrawRectangleLines((window.screenWidth / 2) - (textWidth / 2) - 10,
                       window.screenHeight / 2 - (60 / 2) - 10, textWidth + 20,
                       60 + 20, BLACK);
    DrawText("Pause", (window.screenWidth / 2) - (textWidth / 2),
             window.screenHeight / 2 - (60 / 2), 60, BLACK);
  }

  // Player`s movement
  if (IsKeyDown((char)'W')) {
    if (!state.gamePaused) {
      player1.position_y -= 7;
    }
    key_string[0] = 'W';
    printf("char W is pressed\n");
  } else if (IsKeyDown((char)'S')) {
    if (!state.gamePaused) {
      player1.position_y += 7;
    }
    key_string[0] = 'S';
    printf("char S is pressed\n");
  }
  if (IsKeyDown(KEY_DOWN)) {
    if (!state.gamePaused) {
      player2.position_y += 7;
    }
    up_down = "Down";
  } else if (IsKeyDown(KEY_UP)) {
    if (!state.gamePaused) {
      player2.position_y -= 7;
    }
    up_down = "Up";
  }

  // Draw key pressed
  if (key_string[0] != '\0') {
    DrawText(key_string, 27, window.screenHeight - 196, 14, BLUE);
    DrawRectangleLines(20, window.screenHeight - 200, 22, 22, BLACK);
  }
  if (up_down != NULL) {
    DrawText(up_down, window.screenWidth - 40, window.screenHeight - 196, 14,
             BLUE);
    DrawRectangleLines(window.screenWidth - 45, window.screenHeight - 200, 40,
                       22, BLACK);
  }
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void) {
  // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void) { return finishScreen; }

Vector2 GetRandomBallSpeed(int minSpeed, int maxSpeed) {
  const Vector2 speed = {
      GetRandomValue(minSpeed, maxSpeed) * (GetRandomValue(0, 1) ? 1 : -1),
      GetRandomValue(minSpeed, maxSpeed) * (GetRandomValue(0, 1) ? 1 : -1)};
  return speed;
}

void ResetBall(Ball *ball, int screenWidth, int screenHeight) {
  ball->position = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
  ball->speed = GetRandomBallSpeed(200, 300);
}