/**
 * Vector
 *
 * Implements a 3 dimensional vector
 */
class Vector {

	private:
	
	public:
		double i;
		double j; 
		double k;
	
		Vector();
		Vector(double x, double y, double z);
		void set(double x, double y, double z);
		void copy(Vector* v);
};



