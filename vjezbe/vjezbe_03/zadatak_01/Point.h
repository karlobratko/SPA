#pragma once

#include <ostream>

class Point {
public:
	Point(int = 0, int = 0);

	void SetX(const int&);
	void SetY(const int&);
	void Initialize(const int&, const int&);

	int GetX() const;
	int GetY() const;
	double Distance() const;

	friend std::ostream& operator<<(std::ostream&, const Point&);

private:
	int x_;
	int y_;

};

typedef Point* PointPtr;
