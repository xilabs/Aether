#include "Moxel.h"
#include <vector>

using namespace std;
/**
 * SpaceManager
 *
 * Generic superclass for space management
 */
class SpaceManager {

	protected:
		vector<Moxel*> moxels;
	
	public:
		SpaceManager();
		~SpaceManager();
		void add_moxel(Moxel* m);
		void remove_all_moxels();
	
		
		
};



