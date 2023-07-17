#pragma once
#include<utility>
using namespace std;
class Line
{
private:
	//坐标
	float X;
	float Y;
	float X2;
	float Y2;
	//角度
	float angle;
	//长度
	float size;
public:
	Line(float x1, float y1, float x2, float y2);
	float get_angle();
	float get_size();
	void draw();
	std::pair<float, float> get_point(float scale);
	std::pair<float, float> get_first_point();
};
#pragma once
