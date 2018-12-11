#include "Vector2D.h"
#include <math.h>


#define PI 3.14159265

Vector2D::Vector2D(double angle)
{
	x = sin(angle*PI / 180);
	y = -cos(angle*PI / 180);
}

Vector2D& Vector2D::add(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D& Vector2D::minus(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D& Vector2D::multiply(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D& Vector2D::divide(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector2D& operator+(Vector2D & v1, const Vector2D& v2)
{
	return v1.add(v2);
}

Vector2D& operator-(Vector2D & v1, const Vector2D& v2)
{
	return v1.minus(v2);
}

Vector2D& operator*(Vector2D & v1, const Vector2D& v2)
{
	return v1.multiply(v2);
}

Vector2D& operator/(Vector2D & v1, const Vector2D& v2)
{
	return v1.divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->minus(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->divide(vec);
}

Vector2D& Vector2D::operator*(const float& i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}

float Vector2D::magnitude() const
{
	return sqrt(x * x + y * y);
}

Vector2D Vector2D::unitVector()
{
	float mag = magnitude();
	return Vector2D(x / mag, y / mag);
}

Vector2D& Vector2D::scaleToMagnitude(float newMag)
{
	float ratio = newMag / magnitude();
	x = x * ratio;
	y = y * ratio;
	return *this;
}

float Vector2D::dotProduct(const Vector2D& vec2) const
{
	return (x * vec2.x)  + (y * vec2.y);
}
	
float Vector2D::productOfMagnitudes(const Vector2D& vec2) const
{
	return (magnitude() * vec2.magnitude());
}

double Vector2D::angleBetweenVectors(const Vector2D& vec2)
{
	return acos(double(dotProduct(vec2) / productOfMagnitudes(vec2)))* 180.0 / PI;
}

double Vector2D::angleRelativeToVertical()
{
	/*if (x < 0)
	{
		return 360 - (acos(double(dotProduct(Vector2D(0.0f, -1.0f)) / productOfMagnitudes(Vector2D(0.0f, -1.0f)))* 180.0 / PI));
	}*/
	double angle =  (acos(double(dotProduct(Vector2D(0.0f, -1.0f)) / productOfMagnitudes(Vector2D(0.0f, -1.0f))))* 180.0 / PI);
	if (x < 0) { angle *= -1; }
	return angle;
}



Vector2D& Vector2D::Zero()
{
	this->x = 0;
	this->y = 0;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	stream << "( " << vec.getx() << " , " << vec.gety() << " ) ";
	return stream;
}