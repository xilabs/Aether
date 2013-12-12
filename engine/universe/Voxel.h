#pragma once

#include "Eigen/Dense"
#include <boost/shared_ptr.hpp>
#include <deque>
#include <vector>
#include <boost/thread/mutex.hpp>
#include "Moxel.h"
#include "MoxelManager.h"
//#include "../gen-cpp/Aether.h"			// Should not be here!!!!! We should be ignorant of this!
using namespace std;
using namespace Eigen;
using boost::shared_ptr;
using boost::mutex;


class Voxel {

public:

	Voxel (Vector3f position) {

		this->position=position;

	};

	void add_moxel(shared_ptr<Moxel> m){

		{	// Scope for lock
			mutex::scoped_lock lock(this->guard);

			// add
			this->moxels.push_back(m);
		}

	};

	void animate(double delta_t);


	/* 
	 * TODO - this function should not exist - Voxels should not be aware of how they are viewed!
	 * we really need to implement some kind of view connector class!
	 */
	 /*
	vector<MoxelRepresentation> get_moxel_representations() {

		// A place for some results
		vector<MoxelRepresentation> result;
		result.reserve(this->moxels.size());


		{	// Scope for lock
			mutex::scoped_lock lock(this->guard);

			// Iterate, creating representations
			for(deque<shared_ptr<Moxel> >::iterator it=this->moxels.begin(); it != this->moxels.end(); ++it){

				MoxelRepresentation m;
				m.x=(*it)->position(0);
				m.y=(*it)->position(1);
				m.z=(*it)->position(2);

				result.push_back(m);
			}
		}

		return result;
	};
*/
	deque<shared_ptr<Moxel> > moxels;		
	mutex guard;

private:

	MoxelManager moxel_manager;
	Vector3f position;
	Vector3f velocity;

};