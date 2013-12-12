#pragma once

#include "Eigen/Dense"
#include "Eigen/Geometry"
#include <boost/shared_ptr.hpp>
#include <deque>
#include <vector>
#include <cmath>
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

	Voxel (Vector3f position);
	~Voxel();

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
	static const double half_size;

private:
	AlignedBox3f *box;
	MoxelManager moxel_manager;

};

