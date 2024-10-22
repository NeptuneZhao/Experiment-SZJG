#include <stdio.h>

int check_v1(const double x, const double y, const double rate, const int t)
{
	double r1 = rate + 1, r2 = 1;
	for (int i = t; i >= 2; i--)
	{
		r2 += r1;
		r1 *= rate + 1;
	}
	return x * r1 <= y * r2;
}

int check_v2(const double x, const double y, const double rate, const int t)
{
	double X = x;
	for (int i = 0; i < t; i++)
		X = X * (rate + 1) - y;
	return X <= 0;
}

int check(const double x, const double y, const double rate, const int t)
{
	return check_v1(x, y, rate, t) && check_v2(x, y, rate, t);
}

double searchProperRate(const double x, const double y, const int t)
{
	for (double d = 0.00001; ; d += 0.00001)
	{
		if (!check(x, y, d, t))
			return d - 0.00001;
	}
}

int main(void)
{
	int N, X, Y, T;

	// I/O parts, do not modify
	// 3.14% = 0.0314
	scanf("%d", &N); // NOLINT(cert-err34-c)

	for (int i = 0; i < N; i++)
	{
		scanf("%d%d%d", &X, &Y, &T); // NOLINT(cert-err34-c)
		const double rate = searchProperRate(X, Y, T);
		printf("%.2f%%\n", 100 * rate);
	}
	return 0;
}