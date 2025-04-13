#include "stdafx.h"
#include "entity_system.h"


namespace sample {

void EntitySystem::AddEntity(std::unique_ptr<Entity>&& entity) {
  add_table_.insert({ FindNewId(), std::move(entity) });
}

void EntitySystem::Update() {

  Merge();
  for (auto& obj : exist_table_) {
    //const Id id = obj.first;
    auto& entity = obj.second;
    entity->Do<ComponentType::Updater>();
  }

}

void EntitySystem::Render() {
  for (auto& obj : exist_table_) {
    auto& entity = obj.second;
    entity->Do<ComponentType::Render>();
  }
}


EntitySystem::Id EntitySystem::FindNewId() {
  while (true) {
    if (exist_table_.contains(current_id_)) {
      ++current_id_;
      continue;
    }
    if (add_table_.contains(current_id_)) {
      ++current_id_;
      continue;
    }
    return current_id_++;
  }
}

void EntitySystem::Merge() {
  exist_table_.merge(add_table_);
  add_table_.clear();
}

}


