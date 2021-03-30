#pragma once
#include <iostream>
#include <string>

class Point
{
private:
	unsigned _x;
	unsigned _y;

	auto _TestValues(unsigned, unsigned) const->bool;
	auto _InitVariables(unsigned, unsigned)->void;
	auto _InitDefault()->void;
	auto _Print(std::ostream&) const->void;

public:
	Point(unsigned = 0, unsigned = 0);

	auto SetX(unsigned)->void;
	auto SetY(unsigned)->void;

	auto GetX() const->unsigned;
	auto GetY() const->unsigned;
	auto to_string() const->std::string;
	auto Display() const->void;
	auto Distance() const->double;

	friend auto operator<<(std::ostream&, const Point&)->std::ostream&;
};

