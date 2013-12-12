
#include "Voxel.h"


void Voxel::animate(double delta_t) {

		// Lock
		mutex::scoped_lock lock(guard);

		// Iterate
		for(deque<shared_ptr<Moxel> >::iterator it=moxels.begin(); it!=moxels.end(); ++it){	

			// Move the moxel 
			shared_ptr<Moxel> m=(*it);
			m->position+=(delta_t * m->velocity);
		}				

//		shared_ptr<Moxel> m3=this->voxel->moxels.at(2);

		// m1->position(0)=10*sin(t);



}
