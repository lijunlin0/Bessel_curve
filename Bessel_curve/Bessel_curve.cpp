#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<vector>
#include"Line.h"
#include"Time.h"
using namespace std;
const int WIDTH = 1000;
const int HEIGHT = 1000;
long long Time::UpdateMS = 0;

COLORREF value_to_color(int value)
{
	switch (value)
	{
	case 1:return GREEN;
	case 2:return RED;
	case 3:return CYAN;
	case 4:return YELLOW;
	case 5:return BROWN;
	case 6:return MAGENTA;
	case 7:return BLUE;
	default:return CYAN;
	}
}

void initial(vector<pair<float, float>> points,vector<Line> Lines)
{
	for (int i = 0; i < points.size(); i++)
	{
		if (i == 0 || i == points.size() - 1)
		{
			setfillcolor(BROWN);
		}
		else
		{
			setfillcolor(RED);
		}
		//画点
		solidcircle(points[i].first, points[i].second, 5);//起始点
		if (i <= Lines.size()-1)
		{
			setlinecolor(MAGENTA);
			setlinestyle(PS_ENDCAP_FLAT, 1);
			Lines[i].draw();
		}
	}
}

void draw(float scale, vector<pair<float, float>> initial_points, vector<Line> initial_Lines, vector<pair<float, float>> *points, vector<Line> Lines, int color)
{
	initial(initial_points, initial_Lines);
	setlinecolor(value_to_color(color));
	if (Lines.size() == 1)
	{
		for (int i = 0; i < (points->size()-1); i++)
		{
			setlinestyle(PS_ENDCAP_FLAT,3);
			line(points->at(i).first, points->at(i).second, points->at(i + 1).first, points->at(i + 1).second);
		}
		pair<float, float> p = Lines[0].get_point(scale);
		points->push_back(p);
	}
	else
	{
		vector<Line> Lines2;
		for (int i = 0; i < Lines.size()-1; i++)
		{
			pair<float, float> p1 = Lines[i].get_point(scale);
			pair<float, float> p2 = Lines[i + 1].get_point(scale);
			Line l(p1.first, p1.second, p2.first, p2.second);
			setlinestyle(PS_ENDCAP_FLAT, 1);
			l.draw();
			Lines2.push_back(l);
		}
		draw(scale, initial_points, initial_Lines, points, Lines2, color + 1);
	}
}

int main()
{
	vector<pair<float, float>> points;
	vector<pair<float, float>> points_draw;
	vector<Line> Lines;
	const int MAX = 10;

	initgraph(WIDTH, HEIGHT, SHOWCONSOLE);
	setlinecolor(LIGHTBLUE);

	float scale = 0;
	ExMessage msg;//创建消息变量
	while (true)
	{
		bool b = peekmessage(&msg, EX_MOUSE);
		if (b && msg.message == WM_LBUTTONDOWN)
		{
			points_draw.clear();
			scale = 0;
			pair<float, float> p(msg.x, msg.y);
			solidcircle(p.first, p.second, 5);
			points.push_back(p);
			Lines.clear();
			if (points.size() >= 3)
			{
				//存线
				for (int i = 0; i < points.size() - 1; i++)
				{
					Line l(points[i].first, points[i].second, points[i + 1].first, points[i + 1].second);
					Lines.push_back(l);
				}
			}	
		}
		if (points.size() >= 3)
		{
			long long currentMS = Time::CurrentTime();
			if (currentMS - Time::UpdateMS < Time::FrameMS)
			{
				continue;
			}
			Time::UpdateMS = currentMS;


			BeginBatchDraw();

			clearrectangle(0, 0, 1000, 1000);
			draw(scale, points, Lines, &points_draw, Lines, 1);

			EndBatchDraw();

			scale += 0.005;
			if (scale >= 1) scale = 0;
			cout << scale << ' ' << points.size() << endl;
		}
		
	}
	return 0;
}