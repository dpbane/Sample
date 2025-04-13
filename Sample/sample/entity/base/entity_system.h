#pragma once

#include "entity.h"

namespace sample {

class EntitySystem {
private:
  using Id = size_t;

public:
  void AddEntity(std::unique_ptr<Entity>&& entity);
  void Update();
  void Render();

private:
  Id FindNewId();
  void Merge();

private:
  HashTable<Id, std::unique_ptr<Entity>> exist_table_;
  HashTable<Id, std::unique_ptr<Entity>> add_table_;
  HashSet<Id> delete_set_;
  Id current_id_{ 0 };

};

}
