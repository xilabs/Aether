#pragma once
#include "Vector.h"


/**
 * Moxel
 *
 * The atomic unit of simulated mater!
 */
class Moxel {

	private:
		Vector position;
	
	public:
		Moxel();
		void set_position(Vector* v);
		
};



