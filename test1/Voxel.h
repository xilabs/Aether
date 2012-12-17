#pragma once
#include "Moxel.h"
#include <boost/smart_ptr/shared_ptr.hpp>
#include <vector>


/**
 * Voxel
 *
 * Arbitrary subdivision of space
 * Also tracks all objects that lie within it
 */
 
 //typedef boost::ptr_vector<Moxel*> moxel_container;
 typedef boost::shared_ptr<Moxel> moxel_ptr;
 
 
class Voxel {

	protected:
		std::vector<moxel_ptr> moxels;
	
	public:
		Voxel();
		~Voxel();
		void add_moxel(moxel_ptr m);
		void remove_moxel(moxel_ptr m);
		void remove_all_moxels();
};


 

