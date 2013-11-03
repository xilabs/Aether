#pragma once
#include "../Logger.h"
#include "Moxel.h"
#include "Voxel.h"
#include "MoxelManager.h"
#include "Eigen/Dense"
#include <boost/shared_ptr.hpp>
#include <deque>
using namespace std;
using namespace Eigen;
using boost::shared_ptr;

extern shared_ptr<Logger> logger;

class Universe {

public:
	Universe();

	// Start with 1 voxel! :)
	shared_ptr<Voxel> voxel;

};