#include <iostream>
#include <vector>
#include<cmath>
#include<string>


struct Point {
	double x;
	double y;
};

double newton_wspolczynniki(int n, int i, const std::vector<Point>& points) {
	if (n == 0) return points[i].y;
	return (newton_wspolczynniki(n - 1, i + 1, points) - newton_wspolczynniki(n - 1, i, points)) / (points[i + n].x - points[i].x);
}

std::string newton_iloczyn(int n, const std::vector<Point>& points) {
	std::string result;
	for (int i = 0; i <= n; ++i) {
		double coeff = newton_wspolczynniki(i, 0, points);
		if (coeff == 0) continue;
		if (coeff > 0 && !result.empty()) result += " + ";
		if (coeff < 0) result += " - ";
		coeff = fabs(coeff);
		if (coeff != 1 || i == n) result += std::to_string(coeff);
		for (int j = 0; j < i; ++j) {
			result += "(x - " + std::to_string(points[j].x) + ")";
		}
	}
	return result;
}

int main() {
	std::vector<Point> points = 
	{
	  {1.3, 11},
	  {1.4, 0.5},
	  {2.5, 33},
	  {3.5, 42},
	  {10000.5, 3}
	};
	int n = points.size() - 1;

	std::cout << "Dany wielomian w postaci iloczynowej: " << newton_iloczyn(n, points) << std::endl;

	return 0;
}