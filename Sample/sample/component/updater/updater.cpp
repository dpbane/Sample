#include "updater.h"

#include "sample/component/shape/shape.h"

namespace sample {

constexpr auto T = ComponentType::Updater;

void ComponentData<T>::Do(ComponentTable& component_table) {
  if (handler_) handler_(component_table, any_data_);
}


}
