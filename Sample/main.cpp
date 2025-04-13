// プリコンパイル済みヘッダーにより、Siv3Dはインクルード指定しなくても常にインクルードされた状態となる
//#include <Siv3D.hpp>  // Siv3D v0.6.16

#include "sample/entity/base/entity_system.h"
#include "sample/entity/impl/shape_factory.h"


void Main() {

  Scene::SetBackground(ColorF{ 0.1, 0.1, 0.1 });

  sample::EntitySystem system;
  sample::ShapeFactory shape_factory;

  for (int k = 0; k < 100; ++k) {
    const Point position(Random(0, Scene::Width()), Random(0, Scene::Height()));
    const double r = Random(2.0, 20.0);
    const ColorF color = HSV(Random(0.0, 360.0), 1.0, 1.0);
    const Vec2 velocity = Vec2(Random(-80.0, 80.0), Random(-80.0, 80.0));
    const double rotate_velocity = Random(-5.0, 5.0);
    if (k & 1) system.AddEntity(shape_factory.MakeBall(position, r, color, velocity));
    else system.AddEntity(shape_factory.MakeStar(position, r, color, velocity, rotate_velocity));
  }


  while (System::Update()) {
    system.Update();
    system.Render();
  }
}
