#include "Universe.h"


Universe::Universe() {

	// Create the voxel
	voxel=shared_ptr<Voxel>(new Voxel(Vector3f(0,0,0)));


	// Create 3 moxels, and add them to the Voxel
	shared_ptr<Moxel> m1=shared_ptr<Moxel>(new Moxel(Vector3f(1,1,0)));
	shared_ptr<Moxel> m2=shared_ptr<Moxel>(new Moxel(Vector3f(2,1,0)));
	shared_ptr<Moxel> m3=shared_ptr<Moxel>(new Moxel(Vector3f(3,1,0)));
	voxel->add_moxel(m1);
	voxel->add_moxel(m2);
	voxel->add_moxel(m3);

	// Add bonds: m1<->m2
	m1->bind(m2);
	m2->bind(m1);

	// Add bonds: m2<->m3
	m2->bind(m3);
	m3->bind(m2);


};
