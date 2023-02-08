#include <iostream>
#include <vector>
#include <cmath>

const double EPS = 1e-9;

void zamiana_wierszy(std::vector<std::vector<double>>& A, int i, int j) 
{
	std::swap(A[i], A[j]);
}

void odejmowanie_wierszy(std::vector<std::vector<double>>& A, int i, int j, double multiplier) 
{
	int n = A.size();
	int m = A[0].size();
	for (int k = 0; k < m; ++k) {
		A[j][k] -= multiplier * A[i][k];
	}
}

std::vector<double> gauss(std::vector<std::vector<double>> A) 
{
	int n = A.size();
	int m = A[0].size();
	for (int i = 0; i < n; ++i) 
	{
		int pivot = i;
		for (int j = i + 1; j < n; ++j)
		{
			if (fabs(A[j][i]) > fabs(A[pivot][i])) 
			{
				pivot = j;
			}
		}
		if (fabs(A[pivot][i]) < EPS) 
		{
			return {};
		}
		zamiana_wierszy(A, i, pivot);
		double divisor = A[i][i];
		for (int j = i + 1; j < n; ++j) 
		{
			odejmowanie_wierszy(A, i, j, A[j][i] / divisor);
		}
	}
	std::vector<double> x(n);
	for (int i = n - 1; i >= 0; --i) 
	{
		double sum = 0.0;
		for (int j = i + 1; j < n; ++j) 
		{
			sum += A[i][j] * x[j];
		}
		x[i] = (A[i][n] - sum) / A[i][i];
	}
	return x;
}

int main()
{
	struct Point
	{
		float x;
		float y;
	};
	std::vector<Point> points =
	{
	  {1, 1},
	  {1.5, 0.5},
	  {2.5, 3},
	  {3, 4},
	  {5, 0},
	  {4,3}
	};
	float T0 = 1;
	auto T1 = [](float x) { return x; };
	auto T2 = [](float x) { return 2 * pow(x, 2) - 1;  };
	auto T3 = [](float x) { return 4 * pow(x, 3) - 3 * x;  };
	auto T4 = [](float x) { return 8 * pow(x, 4) - 8 * pow(x, 2) + 1;  };
	auto T5 = [](float x) { return 16 * pow(x, 5) - 20 * pow(x, 3) + 5 * x; };

	std::vector<std::vector<double>> A = 
	{
	  {T0, T1(points[0].x),T2(points[0].x),T3(points[0].x),T4(points[0].x),T5(points[0].x),points[0].y},
	  {T0, T1(points[1].x),T2(points[1].x),T3(points[1].x),T4(points[1].x),T5(points[1].x),points[1].y},
	  {T0, T1(points[2].x),T2(points[2].x),T3(points[2].x),T4(points[2].x),T5(points[2].x),points[2].y},
	  {T0, T1(points[3].x),T2(points[3].x),T3(points[3].x),T4(points[3].x),T5(points[3].x),points[3].y},
	  {T0, T1(points[4].x),T2(points[4].x),T3(points[4].x),T4(points[4].x),T5(points[4].x),points[4].y},
	  {T0, T1(points[5].x),T2(points[5].x),T3(points[5].x),T4(points[5].x),T5(points[5].x),points[5].y}
	};


	auto x = gauss(A);

	if (x.empty()) 
	{
		std::cout << "brak rozwiazan" << std::endl;
	}
	else 
	{
		for (double value : x) 
		{
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}