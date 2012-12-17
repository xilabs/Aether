#include "VoxelSpaceManager.h"
#include <stdexcept>
#include <iostream>

/**
 * Constructor
 *
 * 
 */
VoxelSpaceManager::VoxelSpaceManager(int x_voxels, int y_voxels, int z_voxels, Vector* voxel_origin, Vector* voxel_size) : SpaceManager() {

	// Save parameters
	this->x_voxels=x_voxels;
	this->y_voxels=y_voxels;
	this->z_voxels=z_voxels;
	this->voxel_origin=voxel_origin;
	this->voxel_size=voxel_size;

	// Create the voxel array!  We do this with care, so we don't trigger tons of reallocations as the array grows.
/*
	voxels.reserve(x_voxels);
	for(int x=0; x<x_voxels; x++) {
	
			container_of_voxel_container covc=container_of_voxel_container();
			covc.reserve(y_voxels);
			voxels.push_back(covc);
			
		for(int y=0; y<y_voxels; y++) {
	
			voxel_container vc = voxel_container();
			vc.reserve(z_voxels);
			voxels[x].push_back(vc);
	
			for(int z=0; z<z_voxels; z++) {
			
				voxels[x][y].push_back(new Voxel());			
			}	

		}
	}
*/
	// This should be equivalent to the above
	voxels=container_of_container_of_voxel_container(x_voxels);
	for(int x=0; x<x_voxels; x++) {
	
		voxels[x]=container_of_voxel_container(y_voxels);
			
		for(int y=0; y<y_voxels; y++) {
	
			for(int z=0; z<z_voxels; z++) {
			
				voxels[x][y].push_back(new Voxel());			
			}	
		}
	}


}

VoxelSpaceManager::~VoxelSpaceManager() {

	// Empty arrays
	voxels.clear();

	// Release owned objects
	delete voxel_size;
	delete voxel_origin;
}

/**
 * Add a moxel
 *
 * Overrides base class to add a moxel directly to the responsible voxel
 *
 * @param m (Moxel*) the moxel to add
 */
void VoxelSpaceManager::add_moxel(Moxel* m) {

	try {

		Voxel* v=voxel_for_vector(m->get_position());
		v->add_moxel(moxel_ptr(m));
	} catch (out_of_range &oor) {
	
		cerr << "Error: Moxel added at invalid location\n";
		delete m;
		return;
	}

}

/** 
 * Find Voxel for given coordinate
 *
 * @param v the location in question
 */
Voxel* VoxelSpaceManager::voxel_for_vector(Vector* v) {

	// Find probable index
	int x=(int) v->i/voxel_size->i;
	int y=(int) v->j/voxel_size->j;
	int z=(int) v->k/voxel_size->k;
	
	std::cerr << "\nMOXEL CREATED AT x=" << x << " y=" << y << " z=" << z << " \n";
	
	return &voxels.at(x).at(y).at(z);
}




