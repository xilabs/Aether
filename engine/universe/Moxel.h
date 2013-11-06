#pragma once

#include "Eigen/Dense"
#include <boost/shared_ptr.hpp>
#include <deque>
using namespace std;
using namespace Eigen;
using boost::shared_ptr;

class Moxel {

public:
	Moxel(Vector3f position) {

		this->position=position;

	};

	void bind(shared_ptr<Moxel>brother) {

		this->bonds.push_back(brother);		/* TODO - make sure we don't do this twice for the same brother! */
	};



	Vector3f position;
	Vector3f velocity;
	deque<shared_ptr<Moxel> > bonds;
};