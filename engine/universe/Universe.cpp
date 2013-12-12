#include "Universe.h"
#include <cmath>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#define PI 3.14159265

Universe::Universe() {

	// Create the voxel
	voxel=shared_ptr<Voxel>(new Voxel(Vector3f(0,0,0)));


	// Create 3 moxels, and add them to the Voxel
/*
	shared_ptr<Moxel> m1=shared_ptr<Moxel>(new Moxel(Vector3f(10,0,0)));
	shared_ptr<Moxel> m2=shared_ptr<Moxel>(new Moxel(Vector3f(0,10,0)));
	shared_ptr<Moxel> m3=shared_ptr<Moxel>(new Moxel(Vector3f(0,0,10)));
	voxel->add_moxel(m1);
	voxel->add_moxel(m2);
	voxel->add_moxel(m3);

	// Add bonds: m1<->m2
	m1->bind(m2);
	m2->bind(m1);

	// Add bonds: m2<->m3
	m2->bind(m3);
	m3->bind(m2);

*/
	// Now generate 97 more random moxels

	boost::mt19937 rng;
	boost::uniform_int<> dist(-200,200);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(rng, dist);
	for (int n=0; n<97; n++){

		// Create a moxel
		shared_ptr<Moxel> m=shared_ptr<Moxel>(new Moxel(Vector3f(die(),die(),die())));
		voxel->add_moxel(m);

		// Give it a random velocity
		m->velocity=Vector3f(0.1*die(),0.1*die(),0.1*die());

	}


};

void Universe::run(){

	// Start up the manager thread
	this->manager_run=shared_ptr<atomic_count>(new atomic_count(1));
	this->manager=shared_ptr<boost::thread>(new boost::thread(&Universe::manage, this));


};

void Universe::stop(){

	// Retire the manager
	--(*this->manager_run);
	this->manager->interrupt();
	this->manager->join();

};
/**
 * We are the manager thread
 *
 * Literally run the universe!
 */
void Universe::manage(){

	static float t=0;	// Global time counter

	while(*this->manager_run) {

		try {

			// Snooze a little
			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
			t+=0.010;
			this->voxel->animate(0.010);

			// Move some moxels
			// t+=.01;
			// if(t>2*PI){
	
			// 	t=0;
			// }

			// { // Scope for lock 
			// 	mutex::scoped_lock lock(this->voxel->guard);
			// 	// for(deque<shared_ptr<Moxel> >::iterator it=voxel->moxels.begin(); it!=voxel->moxels.end(); ++it){	

			// 	// 	//double x=(*it)->position(0);
			// 	// }				
			// 	shared_ptr<Moxel> m1=this->voxel->moxels.at(0);
			// 	shared_ptr<Moxel> m2=this->voxel->moxels.at(1);
			// 	shared_ptr<Moxel> m3=this->voxel->moxels.at(2);

			// 	m1->position(0)=10*sin(t);
			// 	m2->position(1)=10*sin(t+1);
			// 	m3->position(2)=10*sin(t+2);
			// }



		} catch(boost::thread_interrupted& e) {

			// We were asked to leave?
			return;

		} catch(std::exception& e) {

			// TODO... something bad happened in the curator thread
		}
	}
};
