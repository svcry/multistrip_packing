#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<fstream>
using namespace std;
struct rect {
	int width;
	int height;
	int x;
	int y;
	int place;
	rect(int w = 0, int h = 0, int x = 0, int y = 0, int p = 0) :width(w), height(h), x(x), y(y), place(p) {}
};
rect* newrect(int w, int h, int x, int y, int p);
vector <rect*> rcopy(vector<rect*>& rectangles);
vector<vector<rect*>> vrcopy(vector<vector<rect*>>& rectangles);
void rclean(vector <rect*>& r);
void vrclean(vector <vector <rect*> >& r);
vector<string> create_NFDH_string(vector<vector <rect*>>& rectangles, int W);
void pushrect(vector <vector <rect*>>& rectangles, int M);
