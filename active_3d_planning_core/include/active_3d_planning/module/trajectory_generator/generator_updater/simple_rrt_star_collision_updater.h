#ifndef ACTIVE_3D_PLANNING_GENERATOR_UPDATER_SIMPLE_RRT_STAR_COLLISION_UPDATER_H
#define ACTIVE_3D_PLANNING_GENERATOR_UPDATER_SIMPLE_RRT_STAR_COLLISION_UPDATER_H

#include "active_3d_planning/module/trajectory_generator/rrt_star.h"

namespace active_3d_planning {
namespace generator_updater {

// Recursively check wether the trajectories are still collision free, if not
// try to rewire them
class SimpleRRTStarCollisionUpdater : public GeneratorUpdater {
public:
  SimpleRRTStarCollisionUpdater(PlannerI &planner);
  // override virtual functions
  bool updateSegments(TrajectorySegment *root) override;

  void setupFromParamMap(Module::ParamMap *param_map) override;

protected:
  static ModuleFactoryRegistry::Registration<SimpleRRTStarCollisionUpdater>
      registration;

  // reference to Generator for rewiring
  trajectory_generator::RRTStar *generator_;

  // members
  std::unique_ptr<GeneratorUpdater> following_updater_;

  // methods
  bool isCollided(const EigenTrajectoryPointVector &trajectory);

  void checkSingle(TrajectorySegment *segment,
                   std::vector<TrajectorySegment *> *to_rewire,
                   std::vector<TrajectorySegment *> *safe_segments);
};

} // namespace generator_updater
} // namespace active_3d_planning
#endif // ACTIVE_3D_PLANNING_GENERATOR_UPDATER_SIMPLE_RRT_STAR_COLLISION_UPDATER_H