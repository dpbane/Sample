#pragma once

#include "sample/component/base/component.h"

namespace sample {

template<>
class ComponentData<ComponentType::Shape> {
public:
  ComponentData(const Polygon& shape) : shape_(shape) {}
  ~ComponentData() = default;
  void Do(ComponentTable& component_table);

  Polygon& GetShape() { return shape_; }

private:
  Polygon shape_;

};



}
