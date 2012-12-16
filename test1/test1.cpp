
// 	test1.c
//
// Create a basic world, with some object in it



#include <iostream>
#include "Vector.h"
#include "Moxel.h"
#include "Voxel.h"
#include "VoxelSpaceManager.h"
using namespace std;


int main () {

	// Create space
	SpaceManager* space= (SpaceManager*) new  VoxelSpaceManager();

	// Create a moxel, add it to the space
	Moxel* m=new Moxel();
	space->add_moxel(m);
	
	// ... //
	
	delete space;
	
	
	return 0;

}

