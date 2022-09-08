#include"SA.h"

int solution(vector<string>& T, vector<vector<rect*>>& rectangles, int W, bool& can, int& index_h) {
	int maxH = 0;
	vector<int> maxW;
	for (int i = 0; i < size(rectangles); i++) {
		maxW.push_back((i + 1) * W);
	}
	vector<vector<step*> >contour;
	contour = L_decode(T, rectangles, W);
	for (int i = 0; i < size(contour); i++) {
		for (int j = 0; j < size(contour[i]); j++) {
			if (maxW[i] < contour[i][j]->right) {
				maxW[i] = contour[i][j]->right;
			}
			if (maxH < contour[i][j]->top) {
				maxH = contour[i][j]->top;
				index_h = i;
			}
		}
	}
	vsclean(contour);
	int j = 0;
	int forfeit = 1;
	while (j < size(rectangles)) {
		if (maxW[j] > (j + 1) * W) {
			forfeit += maxW[j] - (j + 1) * W;
			can = false;
		}
		j++;
	}
	if (forfeit == 1) {
		can = true;
	}
	maxH = maxH * forfeit;
	return maxH * maxW[size(maxW) - 1];
}


vector<vector<step*>> to_compact(vector<string>& T, vector<vector<rect*>>& rectangles, string& code, int W) {
	vector<vector<step*>> contour;
	if (code == "L") {
		T = Ltree_code(rectangles);
		contour = L_decode(T, rectangles, W);
		code = "B";
	}
	else if (code == "B") {
		T = Btree_code(rectangles);
		contour = B_decode(T, rectangles, W);
		code = "L";
	}
	return contour;
}
int last_solution(vector<string>& T, vector<vector<rect*>>& rectangles, int W, bool LB, bool& can) {
	int maxH = 0;
	int N = size(rectangles) - 1;
	vector<int> maxW;
	for (int i = 0; i < size(rectangles); i++) {
		maxW.push_back((i + 1) * W);
	}
	int S_all = 0;
	vector<vector<step*>> contour;
	if (LB) {
		string code = "B";
		for (int j = 0; j <= 5; j++) {
			vsclean(contour);
			contour = to_compact(T, rectangles, code, W);
		}
	}
	else contour = L_decode(T, rectangles, W);
	int index_h = 0;
	for (int i = 0; i < size(contour); i++) {
		for (int j = 0; j < size(contour[i]); j++) {
			if (maxW[i] < contour[i][j]->right) {
				maxW[i] = contour[i][j]->right;
			}
			if (maxH < contour[i][j]->top) {
				maxH = contour[i][j]->top;
				index_h = i;
			}
		}
	}
	vsclean(contour);

	for (int i = 0; i < size(rectangles); i++) {
		for (int j = 0; j < size(rectangles[i]); j++)
			S_all += rectangles[i][j]->height * rectangles[i][j]->width;
	}
	string way2 = "C:\\drawing";
	ofstream fout1(way2 + "\\strip_draw.txt");
	fout1 << maxH << endl;
	for (int i = 0; i < size(rectangles); i++) {
		fout1 << (i + 1) * W << " " << (i + 1) * W << endl;
	}
	fout1.close();
	cout << "W: " << maxW[size(maxW) - 1] << endl;
	cout << "H: " << maxH << endl;
	cout << "Dead space: " << 100 * double(maxW[size(maxW) - 1] * maxH - S_all) / double(maxW[size(maxW) - 1] * maxH) << "%" << endl;
	return maxH * maxW[size(maxW) - 1];
}

void simulated_annealing(int W, double r, bool LB, int M) {
	vector<vector<rect*>> rectangles;
	vector<string> T;
	int sec_best = 0;
	vector<int> obj_func;
	clock_t start = clock();
	for (int i = 0; i < M; i++) {
		vector <rect*> tmp;
		rectangles.push_back(tmp);
	}
	pushrect(rectangles, M);
	T = create_NFDH_string(rectangles, W);
	vector<string> T_best = T;
	vector<vector<rect*>> r0 = vrcopy(rectangles);
	vector<vector<rect*>> r_allowable = vrcopy(rectangles);
	vector<vector<rect*>> r_best = vrcopy(rectangles);
	vector<string> T0 = T;
	vector<string> T_allowable = T;
	bool can = false;
	bool change = true;
	double t;
	int index_h = 0;
	int it = 0;
	for (int i = 0; i < M; i++) {
		it += rectangles[i].size() - 1;
	}
	int L = pow(it, 2) / 10;
	int k = 0;
	int S, S_0, Sc;
	int num_of_set;
	num_of_set = (size(rectangles) - 1);
	t = 20;
	int iterations = 0;
	S = solution(T0, r0, W, can, index_h);
	int S_best = S;
	cout << S << endl;
	obj_func.push_back(S);
	Sc = S;
	while ((k < 10) && (iterations <= 50000000) /*&& (int(clock() / CLOCKS_PER_SEC) <= 600)*/) {
		for (int j = 0; j <= L; j++) {
			iterations++;
			if (change) {
				vrclean(rectangles);
				rectangles = vrcopy(r0);
				T = neighborhood(T0, rectangles, index_h);
			}
			else {
				T = neighborhood(T, rectangles, index_h);
			}
			S_0 = solution(T, rectangles, W, can, index_h);
			double D = S_0 - S;
			if (D > 0) {
				double p = exp(-(D / t));
				if (0.01 * (rand() % 101) < p) {
					S = S_0;
					change = false;
					T0 = T;
					vrclean(r0);
					r0 = vrcopy(rectangles);
					if (can) {
						obj_func.push_back(S_0);
						T_allowable = T0;
						vrclean(r_allowable);
						r_allowable = vrcopy(r0);
					}
				}
				else {
					change = true;
				}
			}
			else {
				S = S_0;
				change = false;
				T0 = T;
				vrclean(r0);
				r0 = vrcopy(rectangles);
				if (can) {
					obj_func.push_back(S_0);
					T_allowable = T0;
					vrclean(r_allowable);
					r_allowable = vrcopy(r0);
					if (S_best > S_0) {
						S_best = S_0;
						T_best = T;
						cout << S_0 << endl;
						sec_best = int(clock() / CLOCKS_PER_SEC);
						vrclean(r_best);
						r_best = vrcopy(r0);
					}
				}
			}
		}
		t = r * t;
		if (Sc == S) {
			k++;
			cout << k << endl;

		}
		else {
			Sc = S;
			k = 0;
			cout << k << endl;
		}
	}
	T = T_best;
	vrclean(rectangles);
	rectangles = vrcopy(r_best);
	S = last_solution(T, rectangles, W, LB, can);
	obj_func.push_back(S);
	T0.clear();
	T_allowable.clear();
	T_best.clear();
	vrclean(r0);
	vrclean(r_allowable);
	vrclean(r_best);
	clock_t end = clock();
	cout << "iterations: " << iterations << endl;
	double sec = (double)(end - start) / CLOCKS_PER_SEC;
	display(T, S, rectangles, sec, obj_func, sec_best);
	vrclean(rectangles);
	T.clear();
	obj_func.clear();
}