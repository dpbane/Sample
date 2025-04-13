#include "stdafx.h"
#include "shape_factory.h"

namespace sample {

std::unique_ptr<Entity> ShapeFactory::MakeBall(
  const Point& position,
  const double& r,
  const ColorF& color,
  const Vec2& velocity) {
  ComponentTable ct;

  // Shape追加
  ComponentData<ComponentType::Shape> shape(Circle(position, r).asPolygon());
  ct.Add(shape);
  {  // Updater追加
    ComponentData<ComponentType::Updater> updater([velocity](ComponentTable& component_table, std::any& any_data) {
      Vec2 velocity_ = std::any_cast<Vec2>(any_data);

      auto shape_opt = component_table.Get<ComponentType::Shape>();
      if (not shape_opt) return;
      auto& shape = shape_opt->GetShape();

      // 移動
      shape.moveBy(velocity_ * Scene::DeltaTime());

      // 反射
      if (shape.boundingRect().leftX() < 0 && velocity_.x < 0) velocity_.x = -velocity_.x;
      if (shape.boundingRect().rightX() > Scene::Width() && velocity_.x > 0) velocity_.x = -velocity_.x;
      if (shape.boundingRect().topY() < 0 && velocity_.y < 0) velocity_.y = -velocity_.y;
      if (shape.boundingRect().bottomY() > Scene::Height() && velocity_.y > 0) velocity_.y = -velocity_.y;

      any_data = velocity_;
    }, velocity);
    ComponentImpl<ComponentType::Updater> ci(updater);
    ci.Do(ct);
    ct.Add(updater);
  }
  {  // Render追加
    ComponentData<ComponentType::Render> render(color);
    ct.Add(render);
  }

  return std::make_unique<Entity>(std::move(ct));
}

std::unique_ptr<Entity> ShapeFactory::MakeStar(
  const Point& position,
  const double& r,
  const ColorF& color,
  const Vec2& velocity,
  const double& rotate_velocity) {

  struct Data {
    Vec2 velocity;
    double rotate_velocity;
  };

  ComponentTable ct;

  // Shape追加
  ComponentData<ComponentType::Shape> shape(Shape2D::Star(r, position).asPolygon());
  ct.Add(shape);
  {  // Updater追加
    ComponentData<ComponentType::Updater> updater([velocity](ComponentTable& component_table, std::any& any_data) {
      Data data_ = std::any_cast<Data>(any_data);

      auto shape_opt = component_table.Get<ComponentType::Shape>();
      if (not shape_opt) return;
      auto& shape = shape_opt->GetShape();

      // 移動
      shape.moveBy(data_.velocity * Scene::DeltaTime());
      shape.rotateAt(shape.centroid(), data_.rotate_velocity * Scene::DeltaTime());

      // 反射
      if (shape.boundingRect().leftX() < 0 && data_.velocity.x < 0) data_.velocity.x = -data_.velocity.x;
      if (shape.boundingRect().rightX() > Scene::Width() && data_.velocity.x > 0) data_.velocity.x = -data_.velocity.x;
      if (shape.boundingRect().topY() < 0 && data_.velocity.y < 0) data_.velocity.y = -data_.velocity.y;
      if (shape.boundingRect().bottomY() > Scene::Height() && data_.velocity.y > 0) data_.velocity.y = -data_.velocity.y;

      any_data = data_;
        }, Data{ velocity, rotate_velocity });
    ComponentImpl<ComponentType::Updater> ci(updater);
    ci.Do(ct);
    ct.Add(updater);
  }
  {  // Render追加
    ComponentData<ComponentType::Render> render(color);
    ct.Add(render);
  }

  return std::make_unique<Entity>(std::move(ct));
}

}
