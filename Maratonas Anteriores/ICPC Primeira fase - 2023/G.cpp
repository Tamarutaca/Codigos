#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

typedef std::pair<double, double> Point;
typedef std::pair<double, double> Vector;


bool ccw(Point& p1, Point& p2, Point& p3) {
	Vector v1(p2.first - p1.first, p2.second - p1.second);
	Vector v2(p3.first - p2.first, p3.second - p2.second);

	double cross = v1.first * v2.second - v1.second * v2.first;
	return cross >= 0;
}

std::vector<Point> convex_hull(std::vector<Point>& points) {
	int n = points.size(), k = 0;
	std::vector<Point> hull(2*n);
	std::sort(points.begin(), points.end());

	for (int i = 0; i < n; i++) {
		while ((k >= 2) && !ccw(hull[k-2], hull[k-1], points[i]))
			--k;
		hull[k++] = points[i];
	}

	for (int i = n-2, t = k+1; i >= 0; --i) {
		while((k >= t) && !ccw(hull[k-2], hull[k-1], points[i]))
			--k;
		hull[k++] = points[i];
	}

	hull.resize(k-1);
	return hull;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, x, y;
	std::vector<Point> points, hull;
	std::map<Point, int> point_index;

	std::cin >> n;
	points.reserve(n);
	for (int i = 0; i < n; i++) {
		std::cin >> x >> y;
		points.emplace_back(x, y);
		point_index[points[i]] = i + 1;
	}

	hull = convex_hull(points);
	std::set<int> ans;

	for (int i = 0; i < hull.size(); i++)
		ans.insert(point_index[hull[i]]);

	std::cout << *ans.begin();
	for (auto it = std::next(ans.begin()); it != ans.end(); it++)
		std::cout << " " << *it;
	std::cout << std::endl;

	return 0;
}
