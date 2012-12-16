#include "Vector.h"
#include "SpaceManager.h"

/**
 * Constructor
 *
 * 
 */
SpaceManager::SpaceManager() {


}

/**
 * Destructor
 *
 * 
 */
SpaceManager::~SpaceManager() {


	remove_all_moxels();
}

/**
 * Add a moxel
 *
 * @param m (Moxel*) the moxel to add
 */
void SpaceManager::add_moxel(Moxel* m) {

	moxels.push_back(m);

}



/**
 * Remove all moxels from the space
 *
 */
void SpaceManager::remove_all_moxels() {

	moxels.clear();

}

