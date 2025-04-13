#include "shape.h"


namespace sample {

constexpr auto T = ComponentType::Shape;

#pragma warning(suppress: 4100)
void ComponentData<T>::Do(ComponentTable& component_table) {
  // 特に何もしない
}


}
