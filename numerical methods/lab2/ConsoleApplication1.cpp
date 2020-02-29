// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <algorithm>
#include <iostream>
using namespace std;
#include <cmath>



void Jacobi() {
	int i, j, N, e;
	long double a[4][5] = {
	{4.003, 0.207, 0.519, 0.281, 0.425},
	{0.416, 3.273, 0.326, 0.375, 0.021},
	{0.297, 0.351, 2.997, 0.429, 0.213},
	{0.412, 0.194, 0.215, 3.628, 0.946} };
	long double B[4][4], c[10], norma[10], x[10][10], E;
	long double A[4][4], D[4][4], LandR[4][4];

	cout << "N(<11)="; //ввод количества строк
	//cin >> N;
	N = 4;
	cout << "\n10^e=E\n e=";
	//cin >> E;
	e = -3;
	E = pow(10, e);

	system("cls");
	cout << "Input matrix A \n";

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j <= N; j++)
		{
			if (j == N) {
				c[i] = a[i][j] / a[i][i];
				//cout << "c" << i << '|' << j << '=' << c[i] << endl;
				//cout << "j=M\n";
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j <= N; j++)
		{
			long double s = 0;
			if (j != N) {
				A[i][j] = a[i][j];
			}
			if (i == j) {
				D[i][j] = -1 / (A[i][j]);
			}
			else 	LandR[i][j] = A[i][j];
			if (j != N) {
				for (int k = 0; k < N; k++) {
					s += D[i][i] * LandR[k][j];
				}
				B[i][j] = s;
			}

		}
		c[i] = (-D[i][i]) * a[i][N];
	}
	for (int i = 0; i < N; i++)
	{
		long double s = 0;
		for (int j = 0; j < N; j++)
		{
			s += a[i][j];
		}
		if (a[i][0] <= s) {
			cout << "Jacobi not ok" << endl;
		}
	}
	for (i = 0; i < N; i++)
	{
		norma[i] = 0;
		for (j = 0; j < N; j++)
		{
			norma[i] -= B[i][j];
		}
	}
	long double* resulta, resultc;
	resulta = max_element(norma, norma + N);
	resultc = *max_element(c, c + N);
	
	long double k = ceil((log(E * (1 - *resulta) / resultc)) / (log(*resulta)));
	//long double y = ceil(6 / (log(10)));
	//cout << "y=" << y << endl;
	//if (!k) { cout << "bad" << endl; }
	cout << "number of iterations\n k=" << k << endl;
	//cout << "*end(norma)=" << *end(norma) << endl;
	//cout << "resulta=" << *resulta << endl;
	//cout << "resultc=" << resultc << endl;
	//copy(begin(norma), end(norma), ostream_iterator<int>(cout, " "));
	//cout << endl;
	for (int t = 1; t <= k; t++)
	{//t=столбец
		for (int i = 0; i < N; i++)
		{
			long double s = 0;
			for (j = 0; j < N; j++)
			{
				if (t == 1) { x[j][0] = 0; };
				s += B[i][j] * x[j][t - 1];
			}

			x[i][t] = (floor((s + c[i]) * pow(10, -e))) * E;
			if (t == k) {
				cout << "x[" << i << "]=" << x[i][t] << endl;
			}
		}
	}
	cout << "matrix A \n";
	for (i = 0; i < N; i++)
	{
		for (j = 0; j <= N; j++)
		{
			cout << a[i][j] << "\t";
		}
		cout << endl;
	}
	system("pause");
}

int main()
{
		Jacobi();
	}