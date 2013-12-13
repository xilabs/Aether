#include "Box.h"



Box::Box(double half_size) {

	this->half_size=half_size;

	// x1p=new Vector3f(half_size,0,0);
	// x1n=new Vector3f(1,0,0);

	// y1p=new Vector3f(0,half_size,0);
	// y1n=new Vector3f(0,1,0);

	// z1p=new Vector3f(0,0,half_size);
	// z1n=new Vector3f(0,0,1);

};

Box::~Box() {

	// delete x1p;
	// delete x1n;

	// delete y1p;
	// delete y1n;

	// delete z1p;
	// delete z1n;


};


bool Box::contains(Eigen::Vector3f v){


	// TODO -- we are asuming that the center of this box is at the origin.  This may not be true.

	if(v(0) > half_size || v(0) < -half_size ||v(1) > half_size || v(1) < -half_size || v(2) > half_size || v(2) < -half_size ) {

		return false;
	}

	return true;
};


void Box::bounce(shared_ptr<Moxel> m){

	Vector3f* normal;

	if(m->position(0) > half_size) {

		normal=new Vector3f(1,0,0);
		m->position(0)=half_size;
	}

	if(m->position(0) < -half_size) {

		normal=new Vector3f(-1,0,0);
		m->position(0)=-half_size;
	}

	if(m->position(1) > half_size) {

		normal=new Vector3f(0,1,0);
		m->position(1)=half_size;
	}

	if(m->position(1) < -half_size) {

		normal=new Vector3f(0,-1,0);
		m->position(1)=-half_size;
	}

	if(m->position(2) > half_size) {

		normal=new Vector3f(0,0,1);
		m->position(2)=half_size;
	}

	if(m->position(2) < -half_size) {

		normal=new Vector3f(0,0,-1);
		m->position(2)=-half_size;
	}


	double prod=(-2.0d)*m->velocity.dot(*normal);
	(*normal)*=prod;

	m->velocity+=(*normal);

};

