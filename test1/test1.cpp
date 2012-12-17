
// 	test1.c
//
// Create a basic world, with some object in it



#include <iostream>
#include "Vector.h"
#include "Moxel.h"
#include "Voxel.h"
#include "VoxelSpaceManager.h"
#include <iostream>


int main () {

	// Create space
	std::cout << "Creating space...\n";
	VoxelSpaceManager* space= new  VoxelSpaceManager(5,5,5,new Vector(-2.5,-2.5,-2.5), new Vector(1,1,1));
	std::cout << "Adding moxel...\n";

	// Create a moxel, add it to the space
	space->add_moxel(new Moxel(1.5,1.5,1.5));
	
	// ... //
	std::cout << "Deleting space...\n";
	delete space;
	
	
	return 0;

}

