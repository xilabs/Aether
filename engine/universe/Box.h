
// A box that is aligned with the coordinate system axes and is of equal size in all dimensions



#pragma once
#include "Eigen/Dense"
#include "Eigen/Geometry"
#include <boost/shared_ptr.hpp>
#include <cmath>
#include "Moxel.h"

using namespace std;
using namespace Eigen;
using boost::shared_ptr;


class Box {


public:

	Box(double half_size);
	~Box();
	bool contains(Eigen::Vector3f v);
	void bounce(shared_ptr<Moxel> m);

private:


	Vector3f center;
	float half_size;


	// Messy way to keep track of our bounding planes!  But it seems efficient.

	Vector3f* x1p;
	Vector3f* x1n;

	Vector3f* y1p;
	Vector3f* y1n;

	Vector3f* z1p;
	Vector3f* z1n;

};
