#pragma once
class Vector2
{
public:
	double x;
	double y;

	Vector2();
	Vector2(double xArgs, double yArgs);
	Vector2 operator+=(Vector2 vector);
	Vector2 operator-=(Vector2 vector);
	bool operator==(Vector2 vector);
	bool operator!=(Vector2 vector);
};