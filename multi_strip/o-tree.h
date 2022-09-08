#pragma once

#include "add_funcs.h"
using namespace std;
struct step {
	int left; //b
	int right;
	int top; //t
	step(int l, int r, int t) : left(l), right(r), top(t) {}
};


step* newstep(int l, int r, int h);
void sclean(vector <step*>& c);
void vsclean(vector <vector <step*> >& c);
void L_changecontour(const rect* p, vector<step*>& c, int s, bool flag, int left_W);
vector<vector<step*>> L_decode(const vector<string>& T, vector<vector<rect*>>& rectangles, int W);
void B_changecontour(const rect* p, vector<step*>& c, int s, bool flag, int left_W);
vector<vector<step*>> B_decode(const vector<string>& T, vector<vector<rect*>>& rectangles, int W);
vector<string> Ltree_code(vector <vector<rect*>>& rectangles);
vector<string> Btree_code(vector <vector<rect*>>& rectangles);
vector<string> neighborhood(vector<string> T, vector<vector<rect*>>& rectangles, int& index_h);
