#include <stdio.h>
#include <stdlib.h>

int checkIfRateAvailable(double x, double y, int t, double rate) {
	double r1 = 1+rate, r2 = 1;
	while(t>=2) {
		r2 += r1;
		r1 *= (1+rate);
		t--;
	}
	return x*r1 < y*r2;
}

double searchProperRate(double x, double y, int t) {
	//TODO
	return 0;
}


int main(void)
{
	double rate;
	int N, X, Y, T;
	// I/O parts, do not modify
	scanf("%d", &N);
	for (int loop = 0; loop<N; loop++) {
		scanf("%d%d%d", &X,&Y,&T);
		rate = searchProperRate((double)X, (double)Y, T);
		printf("%.2f%%\n", 100 * rate);
	}
	return 0;
}