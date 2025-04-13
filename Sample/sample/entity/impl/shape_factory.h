#pragma once

#include <memory>

#include "sample/entity/base/entity.h"
#include "sample/component/components.h"

namespace sample {

class ShapeFactory {
public:
  static std::unique_ptr<Entity> MakeBall(const Point& position,
                                          const double& r,
                                          const ColorF& color,
                                          const Vec2& velocity);

  static std::unique_ptr<Entity> MakeStar(const Point& position,
                                          const double& r,
                                          const ColorF& color,
                                          const Vec2& velocity,
                                          const double& rotate_velocity);
};


}
