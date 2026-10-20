#ifndef CPONG_H
#define CPONG_H

#include <raylib.h>

void draw_net(int width, int height, int nets);
void handle_paddle_movement(Vector2 *paddle_left, Vector2 *paddle_right);

#endif /** CPONG_H **/
