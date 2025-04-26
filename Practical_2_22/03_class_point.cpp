// 03_class_point.cpp
#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
    double x, y;

public:
    Point(double x_val = 0, double y_val = 0) : x(x_val), y(y_val) {}

    double distance_to_origin() const {
        return hypot(x, y);
    }

    double distance_to(const Point& other) const {
        return hypot(x - other.x, y - other.y);
    }

    void input() {
        cout << "x: ";
        cin >> x;
        cout << "y: ";
        cin >> y;
    }
};
