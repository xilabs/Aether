#pragma once
#include "Moxel.h"
#include <vector>

using namespace std;

/**
 * Voxel
 *
 * Arbitrary subdivision of space
 * Also tracks all objects that lie within it
 */
class Voxel {

	private:
		vector<Moxel*> contents;
	
	public:
		Voxel();
		void add_moxel(Moxel* m);
		
};



