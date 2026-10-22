#include "cpong.h"
#include <raylib.h>

#define SCREEN_WIDTH     (1000)
#define SCREEN_HEIGHT    (800)
#define BALL_SIZE        (20)
#define BALL_SPEED       (500.0)
#define PADDLE_THICKNESS (BALL_SIZE)
#define PADDLE_HEIGHT    (100)
#define PADDLE_PADDING   (0.75 * BALL_SIZE)
#define PADDLE_SPEED     (0.75 * BALL_SIZE)
#define NET_COUNT        (51)
#define PADDLE_SIZE      ((Vector2){.x = PADDLE_THICKNESS, .y = PADDLE_HEIGHT})

/**
 * main - entry point of the program
 *
 * Return: Nothing
 */
int main(void)
{
	const Color DARK_GRAY_BG = {20, 20, 19, 255};

	int left_score  = 0;
	int right_score = 0;

	float ball_dx = BALL_SPEED;
	float ball_dy = BALL_SPEED;

	Rectangle collision;

	Rectangle ball = {
		.x      = (float)SCREEN_WIDTH / 2,
		.y      = (float)SCREEN_HEIGHT / 2,
		.width  = BALL_SIZE,
		.height = BALL_SIZE,
	};

	Rectangle left_paddle = {
		.x      = PADDLE_PADDING,
		.y      = PADDLE_PADDING,
		.width  = PADDLE_SIZE.x,
		.height = PADDLE_SIZE.y,
	};

	Rectangle right_paddle = {
		.x      = SCREEN_WIDTH - (PADDLE_THICKNESS + PADDLE_PADDING),
		.y      = PADDLE_PADDING,
		.width  = PADDLE_SIZE.x,
		.height = PADDLE_SIZE.y,
	};

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ping pong - raylib");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();

		float ball_nx = ball.x + (dt * ball_dx);
		float ball_ny = ball.y + (dt * ball_dy);

		if (ball_nx < 0 || ball_nx + BALL_SIZE >= SCREEN_WIDTH) {
			ball_dx *= -1;
		} else {
			ball.x = ball_nx;
		}

		if (ball_ny < 0 || ball_ny + BALL_SIZE >= SCREEN_HEIGHT) {
			ball_dy *= -1;
		} else {
			ball.y = ball_ny;
		}

		if (CheckCollisionRecs(left_paddle, ball)) {
			collision = GetCollisionRec(left_paddle, ball);

			if (collision.width < collision.height) {
				ball_dx *= -1;
				ball.x += (dt * ball_dx);
			}
		}

		if (CheckCollisionRecs(right_paddle, ball)) {
			collision = GetCollisionRec(right_paddle, ball);

			if (collision.width < collision.height) {
				ball_dx *= -1;
				ball.x += (dt * ball_dx);
			}
		}

		handle_paddle_movement(&left_paddle, &right_paddle);

		BeginDrawing();

		{
			ClearBackground(DARK_GRAY_BG);
			// Ball
			DrawRectangleRec(ball, RAYWHITE);

			DrawRectangleRec(left_paddle, RAYWHITE);

			draw_score(left_score, right_score);
			draw_net(51);

			DrawRectangleRec(right_paddle, RAYWHITE);
		}

		EndDrawing();
	}

	CloseWindow();

	return (0);
}

void draw_score(int left_score, int right_score)
{
	Font  font     = GetFontDefault();
	float fontSize = 70.0;

	const char *left_score_str  = TextFormat("%d", left_score);
	const char *right_score_str = TextFormat("%d", right_score);

	int text_size = MeasureText(left_score_str, fontSize);

	Vector2 left_score_pos = {
		.x = (float)SCREEN_WIDTH / 2 - 100,
		.y = 100,
	};

	Vector2 right_score_pos = {
		.x = (float)SCREEN_WIDTH / 2 + 100,
		.y = 100,
	};

	DrawTextEx(font, left_score_str, left_score_pos, fontSize, 0, RAYWHITE);
	DrawTextEx(font, right_score_str, right_score_pos, fontSize, 0, RAYWHITE);
}

/**
 * handle_paddle_movement - handles paddle movement
 *
 * Return: Nothing.
 */
void handle_paddle_movement(Rectangle *paddle_left, Rectangle *paddle_right)
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
void draw_net(int nets)
{
	float net_height = (float)SCREEN_HEIGHT / nets;
	float x          = (float)SCREEN_WIDTH / 2;

	for (int i = 0; i < nets; i++) {
		if (i % 2 == 0) {
			float y0 = i * net_height;
			float y1 = (i + 1) * net_height;

			DrawLine(x, y0, x, y1, WHITE);
		}
	}
}
