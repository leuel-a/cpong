#ifndef CPONG_H
#define CPONG_H

#include <raylib.h>

void draw_net(int nets);
void handle_paddle_movement(Rectangle *paddle_left, Rectangle *paddle_right);
void draw_score(int left_score, int right_score);

#endif /** CPONG_H **/
