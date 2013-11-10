#pragma once
#include <vector>
#include <string>
#include <sstream>
#include "../universe/Eigen/Dense"
#include <boost/shared_ptr.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>

using namespace std;
using namespace boost::assign;
using namespace Eigen;

// Bug names stolen from http://bijlmakers.com/insects/insects-abc/
class User {

public:
	User(){

		// Build a list of random names
		random_names+="Ant","Aphid","Assassin bug","Butterfly","Bee","Bedbug","Cricket","Cockroach","Cicada","Dung beetle","Dragonfly","Damselfly","Earwig","Elephant hawk moth","Eyed click beetle","Fly","Flea","Firefly","Grasshopper","Glowworm","Green stink bug","Horsefly","Hornet","Honey bee","Insect","Inchworm","Io moth","Jassid","Junebug","Jewel beetle","Kissing bug","Katydid","Ked","Locust","Lacewing","Ladybird beetle","Mosquito","Maggot","Mayfly","Nit","Netwing","Nymph","Orange dog","Owlfly","Orange Sulfur Butterfly","Praying mantis","Pea weevil","Planthopper","Queen bee","Question mark butterfly","Queen butterfly","Rhinoceros beetle","Rice weevil","Robber fly","Stick insect","Stink bug","Swallowtail butterfly","Termite","Thrips","Tsetse fly","Underwing","Unlined giant chafer","Uncas skipper","Viceroy butterfly","Vine borer","Velvet ant","Wasp","Water bug","Webspinner","Xerces blue butterfly","Xylophagous insect","Xylodromus","Yellow jacket","Yellow mealworm","Yellow plant bug","Zebra butterfly","Zorapteran","Zimmerman pine moth";

		username=get_random_username();
	}

	void apply_force(Vector3f force){

		//TODO
		velocity=force;
	};

	string get_velocity(){

		stringstream s;
		s << velocity;
		return s.str();

	};

	string username;

private:

	string get_random_username(){

		boost::mt19937 rng;
		rng.seed(static_cast<unsigned int>(std::time(0)));
		boost::uniform_int<> dist(0,random_names.size());
		boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(rng, dist);

		string name=random_names.at(die());

		return name; 
	};

	vector<string>random_names;
	Vector3f position;
	Vector3f velocity;
	Vector3f orientation;


};
