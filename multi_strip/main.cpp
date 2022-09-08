#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include"SA.h"
#include<cstdlib>
using namespace std;


int main(int argc, char** argv) {
	srand(time(nullptr));
	int W = 5;
	int M = 2;
	cin >> W;
	cin >> M;
	simulated_annealing(W, 0.99, true, M);
	return 0;
}

/*set terminal wxt
plot "C:\\Gabajoba\\plotSA.txt" using 1:2 with lines linecolor 3*/
