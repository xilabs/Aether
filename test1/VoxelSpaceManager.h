#include "SpaceManager.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>
#include "Vector.h"
#include "Voxel.h"
#include "Moxel.h"

using namespace std;

typedef boost::ptr_vector<Voxel> voxel_container;
typedef vector<voxel_container> container_of_voxel_container;
typedef vector<container_of_voxel_container> container_of_container_of_voxel_container;

/**
 * VoxelSpaceManager
 *
 * Manages space using voxels.
 * Moxels will actually be stored and dealloced by Voxel contents rather than the global SpaceManager vector.
 * This will allow for better data partitioning
 *
 */
class VoxelSpaceManager : public SpaceManager {

	private:
		int x_voxels;
		int y_voxels;
		int z_voxels;
		Vector* voxel_origin;
		Vector* voxel_size;
		container_of_container_of_voxel_container voxels;
		
		Voxel* voxel_for_vector(Vector* v);
		
	public:
		VoxelSpaceManager(int x_voxels, int y_voxels, int z_voxels, Vector* voxel_origin, Vector* voxel_size);
		~VoxelSpaceManager();
		void add_moxel(Moxel* m);
		
		
};



