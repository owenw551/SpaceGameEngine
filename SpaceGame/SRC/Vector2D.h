#pragma once
#include <iostream>

class Vector2D
{
private:
	float x;
	float y;

public:
	Vector2D(float newx = 0.0f, float newy= 0.0f) :
		x(newx), y(newy)
	{}

	//Creates a unit vector from an angle(in degrees) from the vertical
	Vector2D(double angle);

	Vector2D& add(const Vector2D& vec);
	Vector2D& minus(const Vector2D& vec);
	Vector2D& multiply(const Vector2D& vec);
	Vector2D& divide(const Vector2D& vec);

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator +=(const Vector2D& vec);
	Vector2D& operator -=(const Vector2D& vec);
	Vector2D& operator *=(const Vector2D& vec);
	Vector2D& operator /=(const Vector2D& vec);

	Vector2D& operator*(const float& i);
	Vector2D& Zero();
	Vector2D& scaleToMagnitude(float newMag);

	float magnitude() const;
	Vector2D unitVector();
	
	float dotProduct(const Vector2D& vec2) const ;
	float productOfMagnitudes(const Vector2D& vec2) const ;
	double angleBetweenVectors(const Vector2D& vec2);
	double angleRelativeToVertical();


	void setx(const float newx) { x = newx; }
	void sety(const float newy) { y = newy; }
	void setVec(const float newx, const float newy) { x = newx; y = newy; }

	float getx() const { return  x; }
	float gety() const { return  y; }

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
	
};