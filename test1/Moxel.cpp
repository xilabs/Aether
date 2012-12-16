#include "Moxel.h"

/**
 * Constructor
 *
 * 
 */
Moxel::Moxel() {


}


/**
 * Set moxel location in 3d space
 *
 * @param position (Vector*) 
 */
void Moxel::set_position(Vector* v) {

	position.copy(v);
	
}


