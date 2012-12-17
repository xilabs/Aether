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
		~Moxel();
		Moxel(double x, double y, double z);
		void set_position(Vector* v);
		Vector* get_position();		
};



