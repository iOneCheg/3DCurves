#include "pch.h"
#include "Curves.h"
#include <math.h>

Point::Point(double X, double Y, double Z)
{
	this->x = X;
	this->y = Y;
	this->z = Z;
}

Point Circle::point3D(double t)	 const
{
	return Point(this->Radius * cos(t), this->Radius * sin(t), 0);
}

Point Circle::derivative3D(double t) const
{
	return Point(-this->Radius * sin(t), this->Radius * cos(t), 0);
}

Point Ellipse::point3D(double t) const
{
	return Point(this->XRadius * cos(t), this->YRadius * sin(t), 0);
}

Point Ellipse::derivative3D(double t) const
{
	return Point(-this->XRadius * sin(t), this->YRadius * cos(t), 0);
}

Point Helix::point3D(double t) const
{
	return Point(this->Radius * cos(t), this->Radius * sin(t), this->Step * t);
}

Point Helix::derivative3D(double t)	const
{
	return Point(-this->Radius * sin(t), this->Radius * cos(t), this->Step);
}