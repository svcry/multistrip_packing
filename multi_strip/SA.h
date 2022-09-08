#pragma once
#include"o-tree.h"
#include<time.h>
#include<math.h>
int solution(vector<string>& T, vector<vector<rect*>>& rectangles, int W, bool& can, int& index_h);
vector<vector<step*>> to_compact(vector<string>& T, vector<vector<rect*>>& rectangles, string& code, int W);
int last_solution(vector<string>& T, vector<vector<rect*>>& rectangles, int W, bool LB, bool& can);
void simulated_annealing(int W, double r, bool LB, int M);
