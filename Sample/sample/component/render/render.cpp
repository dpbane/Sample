#include "render.h"

#include "sample/component/shape/shape.h"

namespace sample {

constexpr auto T = ComponentType::Render;

void ComponentData<T>::Do(ComponentTable& component_table) {
  auto shape = component_table.Get<ComponentType::Shape>();

  if (shape) {
    RenderShape(shape->GetShape());
  }

}


void ComponentData<T>::RenderShape(const Polygon& shape) {
  shape.draw(color_);
  shape.drawFrame(3.0, ColorF(1.0, 1.0, 1.0, 0.5));
}

}
