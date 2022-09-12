#include"rectangle.h"

rect* newrect(int w, int h, int x, int y, int p) {
	rect* r = new rect(w, h, x, y, p);
	return r;
}

vector <rect*> rcopy(vector<rect*>& rectangles) {
	vector<rect*> r;
	for (int i = 0; i < size(rectangles); i++) {
		r.push_back(newrect(rectangles[i]->width, rectangles[i]->height, rectangles[i]->x, rectangles[i]->y, rectangles[i]->place));
	}
	return r;
}

vector<vector<rect*>> vrcopy(vector<vector<rect*>>& rectangles) {
	vector<vector<rect*>> r;
	for (int i = 0; i < size(rectangles); i++) {
		r.push_back(rcopy(rectangles[i]));
	}
	return r;
}

void rclean(vector <rect*>& r) {
	int num = size(r);
	for (int i = 0; i < num; i++) {
		delete r[i];
	}
	r.clear();
}
void vrclean(vector <vector <rect*> >& r) {
	int num = size(r) - 1;
	for (int i = num; i >= 0; i--) {
		rclean(r[i]);
	}
	r.clear();
}
vector<string> create_NFDH_string(vector<vector <rect*>>& rectangles, int W) {
	int N = size(rectangles);
	int k = 0;
	int n = 0;
	int h_level = 0;
	int index_h;
	vector<string> t;
	for (int i = 0; i < N; i++) {
		string tmp;
		t.push_back(tmp);
	}
	while (k < N) {
		n = size(rectangles[k]);
		int w_level;
		int i = 1;
		int count = 1;
		sort(rectangles[k].begin(), rectangles[k].end(), [](const rect* a, const rect* b) { return a->height > b->height; });
		h_level = 0;
		index_h = 0;
		w_level = k * W + rectangles[k][0]->width;
		rectangles[k][0]->x = k * W;
		rectangles[k][0]->y = h_level;
		index_h = 0;
		t[k] += '0';
		while (i < n) {
			index_h = i;
			while (i != n && w_level + rectangles[k][i]->width <= (k + 1) * W) {
				count++;
				t[k] += '0';
				rectangles[k][i]->x = w_level;
				rectangles[k][i]->y = h_level;
				w_level += rectangles[k][i]->width;
				i++;
			}
			for (int j = 0; j < count; j++) {
				t[k] += '1';
			}
			h_level += rectangles[k][index_h]->height;
			count = 0;
			w_level = k * W;
		}

		k++;
	}
	return t;
}

void pushrect(vector <vector <rect*>>& rectangles, int M)

{
	int n;
	int w;
	int h;
	int k = 0;
	int i = 0;
	ifstream fin;
	string way = "C:\\solution\\packing59.txt";
	fin.open(way);
	fin >> n;
	int del = n / M;
	while (fin >> w >> h) {
		if (size(rectangles[k]) < del) {
		}
		else if (k == M - 1) {
		}
		else {
			k++;
		}
		rectangles[k].push_back(newrect(w, h, 0, 0, 0));
		i++;
	}
	fin.close();
}
