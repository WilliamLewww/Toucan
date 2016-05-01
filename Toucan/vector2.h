#pragma once
#include <iostream>
class Vector2
{
public:
	double x, y;

	Vector2();
	Vector2(double xArgs, double yArgs);
	Vector2 operator+=(Vector2 vector);
	Vector2 operator-=(Vector2 vector);
	bool operator==(Vector2 vector);
	bool operator!=(Vector2 vector);
	friend std::ostream &operator<<(std::ostream &os, Vector2 const &m);
};