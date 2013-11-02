#pragma once

#include "../Eigen/Dense"
#include <boost/shared_ptr.hpp>
#include <deque>
using namespace std;
using namespace Eigen;
using boost::shared_ptr;

class Moxel {

public:
	Vector3d position;
	Vector3d velocity;
	deque<shared_ptr<Moxel> > bonds;
};