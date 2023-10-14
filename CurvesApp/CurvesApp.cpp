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
	vector<variant<Circle, Ellipse, Helix>> curves;
	vector<Circle*> circles;

	int curvesCount = 10;
	srand((unsigned)time(NULL));

	//Creating Random Curves
	for (int i = 0; i < curvesCount; i++)
	{
		curves.push_back(Circle(rand() % 1000));
		curves.push_back(Ellipse(rand() % 1000, rand() % 1000));
		curves.push_back(Helix(rand() % 1000, rand() % 1000));
	}

	//Output of point and derivative data
	for (auto& v : curves)
	{
		std::visit([](auto&& arg)
			{
				using T = std::decay_t<decltype(arg)>;
				if constexpr (std::is_same_v<T, Circle>)
					cout << "Circle: " << endl; 
				else if constexpr (std::is_same_v<T, Ellipse>)
					cout << "Ellipse: " << endl;
				else  cout << "Helix: " << endl;

				Point pt3D = arg.point3D(M_PI / 4);
				Point dv3D = arg.derivative3D(M_PI / 4);

				cout << "Point3D: " << 
					"X = " << pt3D.x << "; Y = " << pt3D.y << "; Z = " << pt3D.z << endl;
				cout << "Derivative3D: " <<
					"X = " << dv3D.x << "; Y = " << dv3D.y << "; Z = " << dv3D.z << endl;
			}, v);
	}
	//Cloning objects into a container with circles
	int counter = 0;
	for (auto& variant : curves) {
		if (auto ptr = std::get_if<Circle>(&variant)) {
			counter++;
			circles.resize(counter);
			circles.at(counter - 1) = ptr;
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
