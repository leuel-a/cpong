#include "cpong.h"
#include <raylib.h>

const Color   DARK_GRAY_BG     = {20, 20, 19, 255};
const int     SCREEN_WIDTH     = 1000;
const int     SCREEN_HEIGHT    = 800;
const int     BALL_SIZE        = 20;
const float   BALL_SPEED       = 500.0;
const int     PADDLE_THICKNESS = BALL_SIZE;
const int     PADDLE_HEIGHT    = 100;
const int     PADDLE_PADDING   = 0.75 * BALL_SIZE;
const float   PADDLE_SPEED     = 0.75 * BALL_SIZE;
const Vector2 PADDLE_SIZE      = {.x = PADDLE_THICKNESS, .y = PADDLE_HEIGHT};

/**
 * main - entry point of the program
 *
 * Return: Nothing
 */
int main(void)
{

	Vector2 ballPos  = {.x = 0.0, .y = 0.0};
	Vector2 ballSize = {.x = BALL_SIZE, .y = BALL_SIZE};
	float   ball_dx  = BALL_SPEED;
	float   ball_dy  = BALL_SPEED;

	Vector2 paddle_left  = {.x = PADDLE_PADDING, .y = PADDLE_PADDING};
	Vector2 paddle_right = {
		.x = SCREEN_WIDTH - (PADDLE_THICKNESS + PADDLE_PADDING),
		.y = PADDLE_PADDING,
	};

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ping pong - raylib");

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();

		float ball_nx = ballPos.x + (dt * ball_dx);
		float ball_ny = ballPos.y + (dt * ball_dy);

		if (ball_nx < 0 || ball_nx + BALL_SIZE >= SCREEN_WIDTH) {
			ball_dx *= -1;
		} else {
			ballPos.x = ball_nx;
		}

		if (ball_ny < 0 || ball_ny + BALL_SIZE >= SCREEN_HEIGHT) {
			ball_dy *= -1;
		} else {
			ballPos.y = ball_ny;
		}

		handle_paddle_movement(&paddle_left, &paddle_right);

		BeginDrawing();

		{
			ClearBackground(DARK_GRAY_BG);
			// Ball
			DrawRectangleV(ballPos, ballSize, RAYWHITE);

			DrawRectangleV(paddle_left, PADDLE_SIZE, RAYWHITE);

			draw_net(SCREEN_WIDTH, SCREEN_HEIGHT, 51);

			DrawRectangleV(paddle_right, PADDLE_SIZE, RAYWHITE);
		}

		EndDrawing();
	}

	CloseWindow();

	return (0);
}

/**
 * handle_paddle_movement - handles paddle movement
 *
 * Return: Nothing.
 */
void handle_paddle_movement(Vector2 *paddle_left, Vector2 *paddle_right)
{
	if (IsKeyDown(KEY_S) &&
	    paddle_left->y + PADDLE_SPEED + PADDLE_SIZE.y <= SCREEN_HEIGHT) {
		paddle_left->y += PADDLE_SPEED;
	}

	if (IsKeyDown(KEY_W) && paddle_left->y - PADDLE_SPEED >= 0) {
		paddle_left->y -= PADDLE_SPEED;
	}

	if (IsKeyDown(KEY_UP) && paddle_right->y - PADDLE_SPEED >= 0) {
		paddle_right->y -= PADDLE_SPEED;
	}

	if (IsKeyDown(KEY_DOWN) &&
	    paddle_right->y + PADDLE_SPEED + PADDLE_SIZE.y <= SCREEN_HEIGHT) {
		paddle_right->y += PADDLE_SPEED;
	}
}

/**
 * draw_net - draws a net for the ping pong ui
 *
 * @width: the width of the screen
 * @height: the height of the screen
 * @nets: the number of nets to be used
 *
 * Return: Nothing.
 */
void draw_net(int width, int height, int nets)
{
	float net_height = (float)height / nets;
	float x          = (float)width / 2;

	for (int i = 0; i < nets; i++) {
		if (i % 2 == 0) {
			float y0 = i * net_height;
			float y1 = (i + 1) * net_height;

			DrawLine(x, y0, x, y1, WHITE);
		}
	}
}
