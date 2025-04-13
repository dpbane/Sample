#pragma once

#include "sample/component/base/component.h"

namespace sample {

template<>
class ComponentData<ComponentType::Render> {
public:
  ComponentData(const ColorF& color) : color_(color) {}
  ~ComponentData() = default;
  void Do(ComponentTable& component_table);

private:
  void RenderShape(const Polygon& shape);

private:
  ColorF color_{};

};

}
