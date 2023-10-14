#pragma once
/// <summary>
/// Point representation structure
/// </summary>
struct __declspec(dllexport) Point
{
public:
	Point(double, double, double);
	double x, y, z;
};
/// <summary>
/// Abstract curve class
/// </summary>
class __declspec(dllexport) Curve
{
public:
	virtual Point point3D(double t) const = 0;
	virtual Point derivative3D(double t) const = 0;
};

class __declspec(dllexport) Circle : public Curve
{
public:
	Circle()
	{ }
	Circle(double r) : Radius(r)
	{ }
	Point point3D(double t) const override;
	Point derivative3D(double t) const override;
	double Radius;
};
class _declspec(dllexport) Ellipse : public Curve
{
public:
	Ellipse(double XR, double YR) : XRadius(XR), YRadius(YR)
	{ }
	Point point3D(double t) const override;
	Point derivative3D(double t) const override;
private:
	double XRadius, YRadius;
};
class _declspec(dllexport) Helix : public Curve
{
public:
	Helix(double r, double a) : Radius(r), Step(a)
	{ }
	Point point3D(double t) const override;
	Point derivative3D(double t) const override;
private:
	double Radius, Step;
};