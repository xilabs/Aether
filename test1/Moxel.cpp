#include "Moxel.h"
#include <iostream>

/**
 * Constructor
 *
 */
Moxel::Moxel() {


}

/**
 * Constructor
 *
 * @param x coordinate of new moxel
 * @param y coordinate of new moxel
 * @param z coordinate of new moxel
 */

Moxel::Moxel(double x, double y, double z) {

	position.set(x,y,z);
	std::cerr << "\nMOXEL CREATED AT x=" << x << " y=" << y << " z=" << z << " \n";

}


/**
 * Destructor
 *
 */
Moxel::~Moxel() {

	std::cerr << "\nMOXEL DIES\n";
}

/**
 * Set moxel location in 3d space
 *
 * @param position (Vector*) 
 */
void Moxel::set_position(Vector* v) {

	position.copy(v);
	
}

/**
 * Returns moxel location in 3d space
 *
 * @return position (Vector*)  
 */
Vector* Moxel::get_position(){

	return &position;

}

