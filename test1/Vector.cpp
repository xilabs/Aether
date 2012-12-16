
#include "Vector.h"

/**
 * Constructor
 *
 * 
 */
Vector::Vector(double x, double y, double z) {

	i=x;
	j=y;
	k=z;
}
Vector::Vector() {

	i=0;
	j=0;
	k=0;
}

/**
 * Set a vector to an initial value
 *
 * Implements a 3 dimensional vector
 */
void Vector::set(double x, double y, double z) {

	i=x;
	j=y;
	k=z;
}


/**
 * Copies another vector
 *
 * @param v (Vector*) pointer to the other vector
 */
void Vector::copy(Vector* v) {

	i=v->i;
	j=v->j;
	k=v->k;
}


