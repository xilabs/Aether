#include "SpaceManager.h"
#include <vector>
#include "Voxel.h"
#include "Moxel.h"

using namespace std;


/**
 * VoxelSpaceManager
 *
 * Manages space using voxels
 */
class VoxelSpaceManager : public SpaceManager {

	protected:
		vector<Moxel*> contents;
		
	public:
		VoxelSpaceManager();
		
};



