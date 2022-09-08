#include "add_funcs.h"
void correct_index(vector<int>& index, int i) {
	int k = 0;
	while (k < size(index)) {
		if (index[k] > index[i]) {
			index[k]--;
		}
		k++;
	}
}

int find_left_min_x(const vector<rect*>& p) {
	int k = size(p) - 1;
	int min_w = 100000;
	int min_h = 100000;
	int index = 0;
	for (int i = 0; i <= k; i++) {
		if ((min_h >= p[i]->y) && (min_w >= p[i]->x)) {
			min_w = p[i]->x;
			min_h = p[i]->y;
			index = i;
		}
	}
	return index;
}

int find_left_lower_x(const vector<rect*>& p) {
	int k = size(p) - 1;
	int max_w = 1000000;
	int max_h = 1000000;
	int index = 0;
	for (int i = 0; i <= k; i++) {
		if ((max_w >= p[i]->x) && (max_h >= p[i]->y)) {
			max_w = p[i]->x;
			max_h = p[i]->y;
			index = i;
		}
	}
	return index;
}

int touched_min_y(const vector<rect*>& p, int j) {
	int k = size(p) - 1;
	int min_y = 1000000;
	for (int i = 0; i <= k; i++) {
		if ((min_y > p[i]->y) && (p[i]->x == p[j]->x + p[j]->width)) {
			min_y = p[i]->y;
		}
	}
	return min_y;
}

int index_right(const vector<rect*>& p, int j) {
	int k = size(p) - 1;
	for (int i = 0; i <= k; i++) {
		if ((p[j]->x + p[j]->width == p[i]->x) &&
			(((p[j]->y + p[j]->height >= p[i]->y) && (p[j]->y + p[j]->height <= p[i]->y + p[i]->height)) ||
				((p[i]->y + p[i]->height >= p[j]->y) && (p[i]->y + p[i]->height <= p[j]->y + p[j]->height)))) {
			if (p[i]->y == touched_min_y(p, j)) {
				return i;
			}
			else continue;
		}
	}
	return j;
}

bool empty_right(const vector<rect*>& p, int j) {
	int k = size(p) - 1;
	for (int i = 0; i <= k; i++) {
		if ((p[j]->x + p[j]->width == p[i]->x) &&
			(((p[j]->y + p[j]->height >= p[i]->y) && (p[j]->y + p[j]->height <= p[i]->y + p[i]->height)) ||
				((p[i]->y + p[i]->height >= p[j]->y) && (p[i]->y + p[i]->height <= p[j]->y + p[j]->height)))) {
			return false;
		}
	}
	return true;
}
int touched_min_x(const vector<rect*>& p, int j) {
	int k = size(p) - 1;
	int min_x = 1000000;
	for (int i = 0; i <= k; i++) {
		if ((min_x > p[i]->x) && (p[i]->y == p[j]->y + p[j]->height)) {
			min_x = p[i]->x;
		}
	}
	return min_x;
}


int index_top(const vector<rect*>& p, int j) {
	int k = size(p) - 1;
	for (int i = 0; i <= k; i++) {
		if ((p[j]->y + p[j]->height == p[i]->y) &&
			(((p[j]->x + p[j]->width >= p[i]->x) && (p[j]->x + p[j]->width <= p[i]->x + p[i]->width)) ||
				((p[i]->x + p[i]->width >= p[j]->x) && (p[i]->x + p[i]->width <= p[j]->x + p[j]->width)))) {
			if (p[i]->x == touched_min_x(p, j)) {
				return i;
			}
			else continue;
		}
	}
	return j;
}

bool empty_top(const vector<rect*>& p, int j) {
	int k = size(p) - 1;
	for (int i = 0; i <= k; i++) {
		if ((p[i]->y == p[j]->y + p[j]->height) &&
			(((p[j]->x + p[j]->width >= p[i]->x) && (p[j]->x + p[j]->width <= p[i]->x + p[i]->width)) ||
				((p[i]->x + p[i]->width >= p[j]->x) && (p[i]->x + p[i]->width <= p[j]->x + p[j]->width)))) {
			return false;
		}
	}
	return true;
}

void display(const vector<string>& T, int S, const vector<vector<rect*>>& rectangles, double sec, const vector<int>& obj_func, int sec_best) {
	cout << "S:" << S << endl;
	cout << "packing:" << endl;
	for (int i = 0; i < rectangles.size(); i++) {
		cout << T[i] << endl;
		for (int j = 0; j < rectangles[i].size(); j++) {
			cout << rectangles[i][j]->width << ", " << rectangles[i][j]->height << "   " << '(' << rectangles[i][j]->x << ',' << rectangles[i][j]->y << ')' << endl;
		}
		cout << "___" << endl;
	}
	string way2 = "C:\\drawing";
	ofstream fout1(way2 + "\\packing_draw.txt");
	for (int i = 0; i < size(rectangles); i++) {
		for (int j = 0; j < size(rectangles[i]); j++)
			fout1 << rectangles[i][j]->x << " " << rectangles[i][j]->y << " " << rectangles[i][j]->x + rectangles[i][j]->width << " " << rectangles[i][j]->y + rectangles[i][j]->height << endl;
	}
	fout1.close();
	cout << sec << " seconds" << endl;
	cout << sec_best << " seconds" << endl;
	string way1 = "C:\\Gabajoba";
	ofstream fout2(way1 + "\\plotSA.txt");
	for (int k = 0; k < size(obj_func); k++) fout2 << k << "\t" << obj_func[k] << endl;
	fout2.close();
}