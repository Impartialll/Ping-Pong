#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <string.h>
#include <sys/types.h>

// Types
typedef struct Ball {
  Vector2 position;
  Vector2 speed;
  float radius;
} Ball;

typedef struct Paddle {
  int paddleWidth;
  int paddleHeight;
  int leftPaddleX;
  int rightPaddleX;
} Paddle;

typedef struct Player {
  short position_y;
  int score;
} Player;

typedef struct WindowRect {
  int rectWidth;
  int rectHeight;
  int rectX;
  int rectY;
} WindowRect;

typedef struct GameState {
  int countdown;
  float countdownTimer;
  bool gamePaused;
} GameState;

typedef struct PopSettings {
  const char *h1_title;
  const char *h2_title;
  const char *ip_title;
  const char *port_title;
  const char *choose_mode;
  int h1_title_size;
  int h2_title_size;
  int ip_port_size;
  int h1_title_width;
  int h2_title_width;
  int ip_port_width;
} PopSettings;

typedef u_int32_t u32;

typedef struct WindowSettings {
  char *title;
  char *footer;
  u32 screenWidth;
  u32 screenHeight;
  u32 targetFPS;
  u32 fontSize;
} WindowSettings;

// IP Settings structure
typedef struct {
  unsigned char ip[4];
  unsigned short port;
} IpSettings;

extern bool show_start_popup;
extern bool show_ipset_popup;
extern bool on_window_quit;
extern bool singleplayer;

Vector2 GetRandomBallSpeed(int minSpeed, int maxSpeed);
void ResetBall(Ball *ball, int screenWidth, int screenHeight);

#endif