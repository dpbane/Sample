#pragma once

#include <memory>

#include "component_type.h"
#include "component_data.h"

namespace sample {

// 前方宣言
class ComponentTable;

class Component abstract {
public:
  virtual ~Component() = 0 {}
  virtual void Do(ComponentTable& component_array) = 0;
};


template<ComponentType T>
class ComponentImpl : public Component {
public:
  ComponentImpl(const ComponentData<T>& data) : data_(data) {}
  ~ComponentImpl() override = default;
  void Do(ComponentTable& component_array) override { data_.Do(component_array); }
  ComponentData<T>* GetData() { return &data_; }

private:
  ComponentData<T> data_;

};


class ComponentTable {
public:
  ComponentTable() = default;
  ComponentTable(ComponentTable&& obj) noexcept : table_(std::move(obj.table_)) {}

  template<ComponentType T>
  void Add(const ComponentData<T>& data) {
    table_.insert({ T, std::make_unique<ComponentImpl<T>>(data) });
  }

  template<ComponentType T>
  ComponentData<T>* Get() {
    if (table_.contains(T)) return reinterpret_cast<ComponentImpl<T>*>(table_.at(T).get())->GetData();
    return nullptr;
  }

private:
  HashTable<ComponentType, std::unique_ptr<Component>> table_;
};

}
