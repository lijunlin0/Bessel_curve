#include<graphics.h>
#include<math.h>
#include<iostream>
#include "Line.h"
const double PI = 3.1415926;

float Line::get_angle()
{
	return atan2(Y2 - Y, X2 - X)* 180 / PI;
}

float Line::get_size()
{
	return sqrt((Y2 - Y)*(Y2 - Y)+ (X2 - X) * (X2 - X));
}

Line::Line(float x1, float y1, float x2, float y2)
{
	X = x1;
	Y = y1;
	X2 = x2;
	Y2 = y2;
}

void Line::draw()
{
	line(X, Y, X2, Y2);
}

pair<float, float> Line::get_point(float scale)
{
	float radian = get_angle() * PI / 180;
	float x1 = X + scale * get_size() * cos(radian);
	float y1 = Y + scale * get_size() * sin(radian);
	pair<float, float> p;
	p.first = x1;
	p.second = y1;
	return p;
}

std::pair<float, float> Line::get_first_point()
{
	pair<float, float> p(X, Y);
	return p;
}
