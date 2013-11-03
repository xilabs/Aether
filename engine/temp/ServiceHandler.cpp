#include "ServiceHandler.h"

extern shared_ptr<Voxel> voxel;


AetherHandler::AetherHandler() {
    // Your initialization goes here
}

void AetherHandler::get_moxel_snapshot(MoxelSpace& _return) {

	_return.moxels=voxel->get_moxel_representations();

}

