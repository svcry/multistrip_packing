#pragma once
#include"rectangle.h"


void correct_index(vector<int>& index, int i);
int find_left_min_x(const vector<rect*>& p);
int find_left_lower_x(const vector<rect*>& p);
int touched_min_y(const vector<rect*>& p, int j);
int index_right(const vector<rect*>& p, int j);
bool empty_right(const vector<rect*>& p, int j);
int touched_min_x(const vector<rect*>& p, int j);
int index_top(const vector<rect*>& p, int j);
bool empty_top(const vector<rect*>& p, int j);
void display(const vector<string>& T, int S, const vector<vector<rect*>>& rectangles, double sec, const vector<int>& obj_func, int sec_best);