#pragma once
#include "../Logger.h"
#include "Moxel.h"
#include "Voxel.h"
#include "MoxelManager.h"
#include "Eigen/Dense"
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/detail/atomic_count.hpp>

#include <deque>
#include <cstdlib>
#include <cstring>
using boost::mutex;
using namespace std;
using namespace Eigen;
using boost::shared_ptr;
using boost::detail::atomic_count;


extern shared_ptr<Logger> logger;

class MoxelMessage {

public:
	MoxelMessage(shared_ptr<Voxel> voxel){				// TODO - this is unsafe without locking moxels to the voxel's deque!

		// Lock the voxel
		mutex::scoped_lock lock(voxel->guard);

		// Create a new message from the passed voxel.  
		this->moxel_count=voxel->moxels.size();
		this->blob_size=16+(sizeof(double)*3*this->moxel_count);
		this->blob=malloc(this->blob_size);

		// Fill out the header
		unsigned int object_type_id=1000;
		unsigned int xheader_length=0;
		unsigned int object_size=3*sizeof(double);
		unsigned int object_count=this->moxel_count;
		unsigned char* blob_ptr=(unsigned char*) this->blob;
		memcpy(blob_ptr,&object_type_id,sizeof(unsigned int));
		blob_ptr+=sizeof(unsigned int);
		memcpy(blob_ptr,&xheader_length,sizeof(unsigned int));
		blob_ptr+=sizeof(unsigned int);
		memcpy(blob_ptr,&object_size,sizeof(unsigned int));
		blob_ptr+=sizeof(unsigned int);
		memcpy(blob_ptr,&object_count,sizeof(unsigned int));
		blob_ptr+=sizeof(unsigned int);


		for(deque<shared_ptr<Moxel> >::iterator it=voxel->moxels.begin(); it!=voxel->moxels.end(); ++it){	

			double x=(*it)->position(0);
			double y=(*it)->position(1);
			double z=(*it)->position(2);

			memcpy(blob_ptr,&x, sizeof(double));
			blob_ptr+=sizeof(double);
			memcpy(blob_ptr,&y, sizeof(double));
			blob_ptr+=sizeof(double);
			memcpy(blob_ptr,&z, sizeof(double));
			blob_ptr+=sizeof(double);
		}

	};
	~MoxelMessage() {

		free(this->blob);
	};
	size_t moxel_count;
	size_t blob_size;
	void* blob;

};

class Universe {

public:
	Universe();

	void run();
	void stop();
	void manage();

	// Start with 1 voxel! :)
	shared_ptr<Voxel> voxel;

protected:
	shared_ptr<boost::thread>manager;
	shared_ptr<atomic_count>manager_run;


};