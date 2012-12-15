
// 	test1.c
//
// Create a basic world, with some object in it



#include <iostream>
#include "Vector.h"
#include "Moxel.h"
using namespace std;


int main () {

	Moxel* m=new Moxel();
	Vector* v= new Vector(1,2,3);
	m->set_position(v);

	// ... //
	
	delete v;
	delete m;
	
	return 0;

}

