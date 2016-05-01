#include "vector2.h"

Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::Vector2(double xArgs, double yArgs) {
	x = xArgs;
	y = yArgs;
}

Vector2 Vector2::operator+=(Vector2 vector) {
	Vector2 newVector(x += vector.x, y += vector.y);
	return newVector;
}

Vector2 Vector2::operator-=(Vector2 vector) {
	Vector2 newVector(x -= vector.x, y -= vector.y);
	return newVector;
}

bool Vector2::operator==(Vector2 vector) {
	if (x == vector.x && y == vector.y) return true;
	return false;
}

bool Vector2::operator!=(Vector2 vector) {
	if (x != vector.x || y != vector.y) return true;
	return false;
}

std::ostream &operator<<(std::ostream &os, Vector2 const &m) {
	return os << m.x << "," << m.y;
}