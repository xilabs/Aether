#include "../Eigen/Dense"
#include <boost/shared_ptr.hpp>
#include <deque>
#include <boost/thread/mutex.hpp>
#include "Moxel.h"
#include "MoxelManager.h"
using namespace std;
using namespace Eigen;
using boost::shared_ptr;
using boost::mutex;


class Voxel {

public:

	Voxel (Vector3d position) {

		this->position=position;

	};

	void add_moxel(shared_ptr<Moxel> m){

		{	// Scope for lock
			mutex::scoped_lock lock(this->guard);

			// add
			this->moxels.push_back(m);
		}

	};


private:

	MoxelManager moxel_manager;
	mutex guard;
	Vector3d position;
	Vector3d velocity;
	deque<shared_ptr<Moxel> > moxels;

};