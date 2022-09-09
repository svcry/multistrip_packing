#include"o-tree.h"

step* newstep(int l, int r, int h) {
	step* st = new step(l, r, h);
	return st;
}
void sclean(vector <step*>& c) {
	int num = size(c);
	for (int i = 0; i < num; i++) {
		delete c[i];
	}
	c.clear();
}
void vsclean(vector <vector <step*> >& c) {
	int num = size(c) - 1;
	for (int i = num; i >= 0; i--) {
		sclean(c[i]);
	}
	c.clear();
}
void L_changecontour(const rect* p, vector<step*>& c, int s, bool flag, int left_W) {
	if (size(c) == 0) {
		c.push_back(newstep(left_W, p->width + left_W, p->height)); //ставим первый прямоугольник в левый нижний угол
	}

	else if (!flag || s - 1 == size(c)) { //äàëåå ïðÿìîóãîëüíèêè ïåðâîé âåòêè ÈËÈ ïðÿìîóãîëüíèêè ïîä åîòîðûìè íèæå íåò íè÷åãî êðîìå îñè X ñòàâÿòñÿ äðóã çà äðóãîì âïëîòíóþ ïî îñè(çà èñêëþ÷åíèåì âòîðîãî ñëó÷àÿ)
		c.push_back(newstep(c[s - 2]->right, c[s - 2]->right + p->width, p->height));
	}

	else if (flag) { //åñëè íîâàÿ âåòêà (òî åñòü åñëè ïðî÷èòàëè íåñêîëüêî 1 ( â êîë-âå ìåíüøåì ÷åì íóëåé) è ïîòîì ÷èòàåì 0
		int j = s - 1; //íîìåð ñòóïåíüêè íà êîòîðóþ ñêëàäûâàåì ïðÿìîóãîëüíèê
		int max_h = c[j]->top; //âûñîòà ýòîé ñòóïåíüêè (ïîêà ÷òî ìàêñèìàëüíàÿ)
		while (j < size(c) && p->width  > c[j]->right - c[s - 1]->left) { //ïðîñìàòðèâàåì âñå ñòóïåíüêè è ñìîòðèì â êàêóþ íàèáîëåå âûñîêóþ áóäåò óïèðàòüñÿ íûíåøíèé ïðÿìîóãîëüíèê, èñõîäÿ èç åãî âûñîòû
			if (j + 1 == size(c)) {
				if (c[j]->top > max_h)
					max_h = c[j]->top;
				j++;

			}
			else {
				j++;
				if (c[j]->top > max_h)
					max_h = c[j]->top;
			}

		}
		if (j == size(c))
			j--;
		//ïîñëå ýòîãî öèêëà îïðåäåëèëàñü âûñîòà ñòóïåíüêè, â êîòîðóþ áóäåò óïèðàòüñÿ íûíåøíèé ïðÿìîóãîëüíèê
		vector<step*> c_new;
		int k = 0;
		while (k < s - 1) {
			c_new.push_back(newstep(c[k]->left, c[k]->right, c[k]->top));
			k++;
		} //ñîñòàâëÿåì íîâûé êîíòóð, âñå ñòóïåíüêè, êîòîðûå íàõîäèëèñü äî òîãî ìåñòà êóäà óïàë íûíåøíèé ïðÿìîóãîëüíèê, îñòàþòñÿ íà ìåñòå
		c_new.push_back(newstep(c[s - 1]->left, p->width + c[s - 1]->left, p->height + max_h)); //äîáàâëÿåì íîâóþ ñòóïåíüêó
		if (p->width < c[j]->right - c[s - 1]->left) { //åñëè íîâûé ïðÿìîóãîëüíèê çàêðûë ñëåäóþùóþ ñòóïåíüêó íå ïîëíîñòüþ
			if (j == 0) //åñëè ýòî ïåðâàÿ ñòóïåíüêà, òî âñå, ÷òî ïîä ýòèì ïðÿìîóãîëüíèêîì çàòèðàåòñÿ, à âûñîòà è ïðàâûé óãîë îñòàþòñÿ íåçèìåííûìè
				c_new.push_back(newstep(left_W + p->width, c[j]->right, c[j]->top));
			else //èíà÷å ëåâûé óãîë íà÷èíàåòñÿ îò îêîí÷àíèÿ ïðåäûäóùåé ñòóïåíüêè, îñòàëüíîå êàê ïðåäûäóùåì ñëó÷àå
				c_new.push_back(newstep(c_new[size(c_new) - 1]->right, c[j]->right, c[j]->top));
			if (c_new[size(c_new) - 1]->left == c_new[size(c_new) - 1]->right)
				c_new.pop_back();
		}

		while (j + 1 < size(c)) {
			c_new.push_back(newstep(c[j + 1]->left, c[j + 1]->right, c[j + 1]->top));
			j++;
		} //âñå ñëåäóþùèå ñòóïåíüêè ñîõðàíÿþòñÿ íåèçìåííî
		//äàëåå ïðîñòî çàìåíèëè êîíòóð
		int d = size(c) - 1;
		int v = size(c_new) - 1;
		for (int z = 0; z <= d; z++) {
			delete c[z];
		}
		c.clear();
		for (int z = 0; z <= v; z++) {
			c.push_back(newstep(c_new[z]->left, c_new[z]->right, c_new[z]->top));
			delete c_new[z];
		}
		c_new.clear();
	}
}

vector<vector<step*>> L_decode(const vector<string>& T, vector<vector<rect*>>& rectangles, int W) {
	vector<vector<step*>> contour;
	bool flag;
	int s;
	int l = 0;
	int pr = 0;
	int N = size(rectangles);
	for (int j = 0; j < N; j++) {
		vector<step*> tmp;
		contour.push_back(tmp);
	}
	int k = 0;
	while (k < N) {
		flag = false;
		s = 0;
		pr = 0;
		l = 0;
		while (l != size(T[k])) {
			if (T[k][l] == '0') {
				s++;
				rectangles[k][pr]->place = l;
				L_changecontour(rectangles[k][pr], contour[k], s, flag, k * W);
				rectangles[k][pr]->x = contour[k][s - 1]->left;
				rectangles[k][pr]->y = contour[k][s - 1]->top - rectangles[k][pr]->height;
				pr++;
			}
			else
			{
				s--;
				flag = true;
			}
			l++;
		}
		k++;
	}
	return contour;
}

void B_changecontour(const rect* p, vector<step*>& c, int s, bool flag, int left_W) { // b r t
	if (size(c) == 0) {
		c.push_back(newstep(0, p->width + left_W, p->height)); //ñòàâèì ïåðâóþ ñòóïåíüêó â (0,0)
	}
	else if (!flag || s - 1 == size(c)) {
		c.push_back(newstep(c[s - 2]->top, p->width + left_W, c[s - 2]->top + p->height)); //äîáàâëÿåì ñòóïåíüêè ïî ïåðâîé âåòêå äåðåâà
	}
	else if (flag) {
		int j = s - 1;
		int max_r = c[j]->right;
		while (j < size(c) && p->height > c[j]->top - c[s - 1]->left) { //â äàííîå äåêîäèðîâêå ìû ïðÿìîóãîëüíèêè óïèðàåì ìàêñèìàëüíî âëåâî, à ïîòîì óæå äâèãàåì âíèç
			if (j + 1 == size(c)) {
				if (c[j]->right > max_r)
					max_r = c[j]->right;
				j++;

			}
			else {
				j++;
				if (c[j]->right > max_r)
					max_r = c[j]->right;
			}

		}
		if (j == size(c))
			j--;

		vector<step*> c_new;
		int k = 0;

		while (k < s - 1) {
			c_new.push_back(newstep(c[k]->left, c[k]->right, c[k]->top));
			k++;
		}
		c_new.push_back(newstep(c[s - 1]->left, p->width + max_r, p->height + c[s - 1]->left));//íå óâåðåí
		if (p->height < c[j]->top - c[s - 1]->left) { //åñëè âëåçàåò ïî âûñîòå
			if (j == 0)
				c_new.push_back(newstep(p->height, c[j]->right, c[j]->top));
			else
				c_new.push_back(newstep(c_new[size(c_new) - 1]->top, c[j]->right, c[j]->top));
			if (c_new[size(c_new) - 1]->left == c_new[size(c_new) - 1]->top)
				c_new.pop_back();
		}

		while (j + 1 < size(c)) {
			c_new.push_back(newstep(c[j + 1]->left, c[j + 1]->right, c[j + 1]->top));
			j++;
		}


		int d = size(c) - 1;
		int v = size(c_new) - 1;
		for (int z = 0; z <= d; z++) {
			delete c[z];
		}
		c.clear();
		for (int z = 0; z <= v; z++) {
			c.push_back(newstep(c_new[z]->left, c_new[z]->right, c_new[z]->top));
			delete c_new[z];
		}
		c_new.clear();
	}
}

vector<vector<step*>> B_decode(const vector<string>& T, vector<vector<rect*>>& rectangles, int W) {
	vector<vector<step*>> contour;
	bool flag = false;
	int s;
	int l = 0;
	int pr = 0;
	int N = size(rectangles);
	for (int j = 0; j < N; j++) {
		vector<step*> tmp;
		contour.push_back(tmp);
	}
	int k = 0;
	while (k < N) {
		flag = false;
		s = 0;
		pr = 0;
		l = 0;
		while (l != size(T[k])) {
			if (T[k][l] == '0') {
				s++;
				rectangles[k][pr]->place = l;
				B_changecontour(rectangles[k][pr], contour[k], s, flag, k * W);
				rectangles[k][pr]->x = contour[k][s - 1]->right - rectangles[k][pr]->width;
				rectangles[k][pr]->y = contour[k][s - 1]->left;
				pr++;
			}
			else
			{
				s--;
				flag = true;
			}
			l++;
		}
		k++;
	}
	return contour;
}

vector<string> Ltree_code(vector <vector<rect*>>& rectangles) {
	vector<string> T;
	int N = size(rectangles) - 1;
	int k = 0;
	vector<vector<rect*>> rects = vrcopy(rectangles);
	vrclean(rectangles);
	for (int i = 0; i <= N; i++) {
		string tmp;
		T.push_back(tmp);
		vector<rect*> dmp;
		rectangles.push_back(dmp);
	}

	while (k <= N) {
		//vector <rect*> r;
		int i = 0;
		int distance = 0;
		int nodes_in_branch = 0; //êîë-âî âåðøèí â âåòêå
		vector<int> index;
		while (!rects[k].empty()) {
			i = find_left_min_x(rects[k]);
			index.push_back(i);
			int j = 0;
			do {
				j = i;
				i = index_right(rects[k], i);
				index.push_back(i);
				distance++;
			} while (j != i);
			index.pop_back();
			for (j = 0; j < distance; j++) {
				T[k] += '0';
				i = index[j];
				rectangles[k].push_back(newrect(rects[k][i]->width, rects[k][i]->height, rects[k][i]->x, rects[k][i]->y, rects[k][i]->place));
			}
			while (distance != 0) {
				if (empty_right(rects[k], index[distance - 1])) {
					correct_index(index, distance - 1);
					rects[k].erase(rects[k].cbegin() + index[distance - 1]);
					index.pop_back();
					distance--;
					T[k] += '1';
				}
				else {
					i = index[distance - 1];
					int j = 0;
					do {
						j = i;
						i = index_right(rects[k], i);
						index.push_back(i);
						nodes_in_branch++;
					} while (j != i);
					index.pop_back();
					nodes_in_branch--;
					for (j = distance; j < distance + nodes_in_branch; j++) {
						T[k] += '0';
						i = index[j];
						rectangles[k].push_back(newrect(rects[k][i]->width, rects[k][i]->height, rects[k][i]->x, rects[k][i]->y, rects[k][i]->place));
					}
					distance += nodes_in_branch;
					nodes_in_branch = 0;
				}
			}
			index.clear();
		}
		k++;

	}
	rects.clear();
	return T;
}
vector<string> Btree_code(vector <vector<rect*>>& rectangles) {
	vector<string> T;
	int N = size(rectangles) - 1;
	int k = 0;
	vector<vector<rect*>> rects = vrcopy(rectangles);
	vrclean(rectangles);
	for (int i = 0; i <= N; i++) {
		string tmp;
		T.push_back(tmp);
		vector<rect*> dmp;
		rectangles.push_back(dmp);
	}
	while (k <= N) {
		//vector <rect*> r;
		int i = 0;
		int distance = 0;
		int nodes_in_branch = 0; //êîë-âî âåðøèí â âåòêå
		vector<int> index;
		while (!rects[k].empty()) {
			i = find_left_lower_x(rects[k]);
			index.push_back(i);
			int j = 0;
			do {
				j = i;
				i = index_top(rects[k], i);
				index.push_back(i);
				distance++;
			} while (j != i);
			index.pop_back();
			for (j = 0; j < distance; j++) {
				T[k] += '0';
				i = index[j];
				rectangles[k].push_back(newrect(rects[k][i]->width, rects[k][i]->height, rects[k][i]->x, rects[k][i]->y, rects[k][i]->place));
			}
			while (distance != 0) {
				if (empty_top(rects[k], index[distance - 1])) {
					correct_index(index, distance - 1);
					rects[k].erase(rects[k].cbegin() + index[distance - 1]);
					index.pop_back();
					distance--;
					T[k] += '1';
				}
				else {
					i = index[distance - 1];
					int j = 0;
					do {
						j = i;
						i = index_top(rects[k], i);
						index.push_back(i);
						nodes_in_branch++;
					} while (j != i);
					index.pop_back();
					nodes_in_branch--;
					for (j = distance; j < distance + nodes_in_branch; j++) { //îøèáêà áûëà òóò
						T[k] += '0';
						i = index[j];
						rectangles[k].push_back(newrect(rects[k][i]->width, rects[k][i]->height, rects[k][i]->x, rects[k][i]->y, rects[k][i]->place));
					}
					distance += nodes_in_branch;
					nodes_in_branch = 0;
				}
			}
			index.clear();
		}
		k++;
	}
	rects.clear();
	return T;
}

vector<string> neighborhood(vector<string> T, vector<vector<rect*>>& rectangles, int& index_h) {
	int num = size(rectangles); // êîëè÷åñòâî 
	vector <int> N; //âåêòîð, êîòîðûé õðàíèò èíäåêñû íåïóñòûõ ïîëîñ
	bool empty = false;
	for (int l = 0; l < num; l++) {
		if (size(rectangles[l]) != 0) {
			N.push_back(l);
		}
	}
	int i;
	if (size(N) == 1) {
		i = N[0];
	}
	else {
		i = rand() % size(N);
		i = N[i];
	} //íîìåð ðàíäîìíîé íåïóñòîé ïîëîñû îòêóäà áåðåì ïðÿìîóãîëüíèê
	i = index_h; //íîìåð ñàìîé âûñîêîé ïîëîñû
	int j;
	if (num - 1 == 0) {
		j = 0;
	}
	else j = rand() % num; // íîìåð ðàíäîìíîé ïîëîñû
	int num1 = size(rectangles[i]); //êîëè÷åñòâî ïðÿìîóãîëüíèêîâ â ïîëîñå i
	int num2 = size(rectangles[j]);//êîëè÷åñòâî ïðÿìîóãîëüíèêîâ â ïîëîñå j
	int i1;
	int j1;
	if (num1 - 1 == 0) {
		i1 = 0;
	}
	else i1 = rand() % num1; //íîìåð ðàíäîìíîãî ïðÿìîóãîëüíèêà â ïîëîñå i
	if (num2 == 0) {
		j1 = 0;
	}
	else if (num2 == -1) {
		empty = true;
	}
	else j1 = rand() % num2/*1*/; //íîìåð ðàíäîìíîãî ïðÿìîóãîëüíèêà â ïîëîñå j
	if (T[i].substr(rectangles[i][i1]->place, 2) == "01") { //åñëè ïðÿìîóãîëüíèê i,i1 ëèñò
		T[i].erase(rectangles[i][i1]->place, 2); //òî óäàëÿåì ýòîò ëèñò èç äåðåâà
		if ((i == j) && (j1 >= i1)) {
			if (j1 == 0) {

			}
			else if (i1 == j1) {
				rectangles[j][j1]->place -= 1;
			}
			else
				rectangles[j][j1]->place -= 2;
		}
		if ((empty) || (T[j] == "")) {
			T[j] += "01";
		}
		else {
			if (rectangles[j][j1]->place + 1 == size(T[j])) {
				int fif = rand() % 2;
				if (fif == 0) {
					T[j].insert(rectangles[j][j1]->place + 1, "01");
				}
				else {
					T[j].insert(rectangles[j][j1]->place, "01");
				}
			}
			else {
				vector <int> K;
				int l = rectangles[j][j1]->place;
				while ((l != size(T[j]) - 1) && (T[j][l] != '1')) {
					K.push_back(l);
					l++;
				}
				while ((l != size(T[j]) - 1) && (T[j][l] != '0')) {
					K.push_back(l);
					l++;
				}
				int k;
				if ((size(K) == 1)) {
					k = 0;
				}
				else {
					k = rand() % (size(K) - 1);
				}
				T[j].insert(K[k], "01");
				K.clear();
			}
		} //âêëèíèâàåì ëèñò íà ìåñòî ïðÿìîóãîëüíèêà j,j1
		rect* tmp = newrect(rectangles[i][i1]->width, rectangles[i][i1]->height, rectangles[i][i1]->x, rectangles[i][i1]->y, rectangles[i][i1]->place);
		rectangles[i].erase(rectangles[i].cbegin() + i1); //óäàëÿåì ïðÿìîóãîëüíèê i1 èç ïîëîñû i
		if (empty) {
			rectangles[j].push_back(tmp);
		}
		else
			rectangles[j].insert(rectangles[j].cbegin() + j1, tmp); //äîáàâëÿåì ïðÿìîóãîëüíèê i1 â ïîëîñe j ïîñëå ïðÿìîóãîëüíèêà j1
	}
	else {
		if (empty) {
			j = rand() % size(N);
			j = N[j];
			j1 = rand() % size(rectangles[j]);
		}
		swap(rectangles[i][i1], rectangles[j][j1]); //ìåíÿåì ìåñòàìè ïðÿìîóãîëüíèêè i,i1 è j,j1
	}
	N.clear();
	return T;
}
