#pragma once

#include <memory>

#include "sample/component/components.h"

// クラスや関数は常に何らかの名前空間に含めるのが望ましいが、1dayなので省略してもいいような気もする
namespace sample {

class Entity {
public:
  Entity() {}
  Entity(ComponentTable&& component_table) : component_table_(std::move(component_table)) {}

  template<ComponentType T>
  void Do() {
    Optional<ComponentData<T>*> component = component_table_.Get<T>();
    if (not component) return;
    component.value()->Do(component_table_);
  }

protected:
  ComponentTable component_table_;

};

}
