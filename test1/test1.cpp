
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

	VoxelSpaceManager* space= new VoxelSpaceManager();


//	Moxel* m=new Moxel();
//	Vector* v= new Vector(1,2,3);
//	m->set_position(v);

	// ... //
	
//	delete v;
//	delete m;
	delete space;
	
	
	return 0;

}

