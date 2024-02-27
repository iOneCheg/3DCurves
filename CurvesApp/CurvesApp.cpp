#define _USE_MATH_DEFINES
#include <iostream>
#include "../Curves.h"
#include <vector>
#include <random>
#include <math.h>
#include <variant>
#include <algorithm>
#include <omp.h>

using namespace std;

bool compareCirclePointers(const Circle* a, const Circle* b) {
	return a->Radius < b->Radius; //Comparing values by radius
}

int main()
{
	vector<Curve*> curves;
	vector<Circle*> circles;

	int curvesCount = 10;
	srand((unsigned)time(NULL));

	//Creating Random Curves
	for (int i = 0; i < curvesCount; i++)
	{
		curves.push_back( new Circle(rand() % 1000));
		curves.push_back( new Ellipse(rand() % 1000, rand() % 1000));
		curves.push_back( new Helix(rand() % 1000, rand() % 1000));
	}

	//Output of point and derivative data
	for (auto& v : curves)
	{
		if (dynamic_cast<Circle*>(v))
		{
			cout << "Circle: " << endl;
		}
		else if (dynamic_cast<Ellipse*>(v))
		{
			cout << "Ellipse: " << endl;
		}
		else cout << "Helix: " << endl;

		cout << "Point3D: " <<
			"X = " << v->point3D(M_PI/4).x <<
			"; Y = " << v->point3D(M_PI / 4).y <<
			"; Z = " << v->point3D(M_PI / 4).z << endl;
		cout << "Derivative3D: " <<
			"X = " << v->derivative3D(M_PI / 4).x << 
			"; Y = " << v->derivative3D(M_PI / 4).y << 
			"; Z = " << v->derivative3D(M_PI / 4).z << endl;
			
	}
	//Cloning objects into a container with circles
	int counter = 0;
	for (auto& v : curves) {
		if (dynamic_cast<Circle*>(v))
		{
			counter++;
			circles.resize(counter);
			circles.at(counter - 1) = (Circle*)v;
		}
	}

	//Sorting circles
	sort(circles.begin(), circles.end(), compareCirclePointers);

	double sum = 0;
	//Calculate sum radii
#pragma omp parallel for reduction (+:sum)
	for (int i = 0; i < circles.size(); i++)
	{
		sum += circles[i]->Radius;
	}
}
