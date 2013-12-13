
#include "Voxel.h"
using namespace Eigen;

const double Voxel::half_size=200.0d;


Voxel::Voxel (Vector3f position) {

	// Get box corners
	Vector3f v2(half_size, half_size, half_size);
	Vector3f v1(-half_size, -half_size, -half_size);

	this->box= new AlignedBox3f(v1, v2);

};

Voxel::~Voxel () {

	delete this->box;
}


void Voxel::animate(double delta_t) {

		// Lock
		mutex::scoped_lock lock(guard);

		// Iterate
		for(deque<shared_ptr<Moxel> >::iterator it=moxels.begin(); it!=moxels.end(); ++it){	

			// Move the moxel 
			shared_ptr<Moxel> m=(*it);
			m->position+=(delta_t * m->velocity);

			// Is the moxel outside the bounding box?
			if(double protrusion=this->box->squaredExteriorDistance(m->position)){

				// Bounce off the wall
				m->velocity*=-1;

				// Move to inside the box
				double length=m->position.norm();
				m->position*=0; //*=(length/(length-sqrt(protrusion)));

			}

		}				

//		shared_ptr<Moxel> m3=this->voxel->moxels.at(2);

		// m1->position(0)=10*sin(t);



}

