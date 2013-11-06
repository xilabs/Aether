#include "classes/Moxel.h"
#include "classes/Voxel.h"
#include "classes/MoxelManager.h"
#include "gen-cpp/Aether.h"
#include <boost/shared_ptr.hpp>
#include <vector>


using boost::shared_ptr;


class AetherHandler : virtual public AetherIf {
 public:
  AetherHandler();
  void get_moxel_snapshot(MoxelSpace& _return);

};
