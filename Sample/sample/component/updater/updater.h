#pragma once

#include "sample/component/base/component.h"

#include <functional>
#include <any>

namespace sample {

template<>
class ComponentData<ComponentType::Updater> {
public:
  using Handler = std::function<void(ComponentTable&, std::any&)>;

public:
  ComponentData(const Handler& handler, const std::any& any_data) : handler_(handler), any_data_(any_data) {}
  ~ComponentData() = default;
  void Do(ComponentTable& component_table);

private:
  Handler handler_;
  std::any any_data_;

};



}
