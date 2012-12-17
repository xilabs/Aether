#include "Vector.h"
#include "Voxel.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <iostream>

/**
 * Constructor
 *
 * 
 */
Voxel::Voxel() {

	std::cerr << "V";
}


/**
 * Destructor
 *
 * 
 */
Voxel::~Voxel() {

	std::cerr << "X";
}

/**
 * Add a Moxel to the contents
 *
 * @param m pointer to the moxel to be added 
 */
void Voxel::add_moxel(moxel_ptr m) {

	moxels.push_back(m);
}


/**
 * Remove a Moxel from the contents
 *
 * @param m pointer to the moxel to be removed 
 */
 
void Voxel::remove_moxel(moxel_ptr m) {

	moxels.erase(std::find(moxels.begin(),moxels.end(),m));
}


/**
 * Empty all moxels
 *
 */
 
void Voxel::remove_all_moxels() {

	moxels.clear();
}
