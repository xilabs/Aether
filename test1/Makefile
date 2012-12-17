BOOST_ROOT=/usr/local/boost_1_52_0

all:
	 g++ -I$(BOOST_ROOT) -L$(BOOST_ROOT)/stage/lib -Wall test1.cpp Vector.cpp Moxel.cpp Voxel.cpp SpaceManager.cpp VoxelSpaceManager.cpp -o test1
	 
clean:
	rm test1