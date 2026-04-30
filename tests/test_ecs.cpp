#include <iostream>
#include <string>
#include <vector>

#include "dengine/ecs/ecs.hpp"
#include "test_helpers.hpp"

struct TestRunner {
  int failures = 0;

  void expect_true(bool cond, const std::string &msg) {
    if (!cond) {
      std::cerr << "FAIL: " << msg << "\n";
      failures++;
    } else {
      std::cout << "PASS: " << msg << "\n";
    }
  }

  void expect_eq(int a, int b, const std::string &msg) {
    if (a != b) {
      std::cerr << "FAIL: " << msg << " (" << a << " != " << b << ")\n";
      failures++;
    } else {
      std::cout << "PASS: " << msg << "\n";
    }
  }

  void expect_ne(int a, int b, const std::string &msg) {
    if (a == b) {
      std::cerr << "FAIL: " << msg << " (" << a << " == " << b << ")\n";
      failures++;
    } else {
      std::cout << "PASS: " << msg << "\n";
    }
  }
};

int main() {
  TestRunner t;

  // Test GetId uniqueness
  {
    int idA1 = de::ecs::GetId<Position>();
    int idA2 = de::ecs::GetId<Position>();
    int idB = de::ecs::GetId<Velocity>();

    t.expect_eq(idA1, idA2, "GetId returns same id for same type");
    t.expect_ne(idA1, idB, "GetId returns different ids for different types");
  }

  // Test entity creation and destruction
  {
    de::ecs::Scene scene;
    auto e = scene.NewEntity();
    t.expect_true(de::ecs::IsEntityValid(e), "NewEntity creates a valid entity");

    scene.DestroyEntity(e);
    // After destruction, the entity slot should be invalid
    bool valid_after = de::ecs::IsEntityValid(scene.entities[e.index].id);
    t.expect_true(!valid_after, "Entity is invalid after DestroyEntity");
  }

  // Assign/Get/Remove component test
  {
    de::ecs::Scene scene;
    auto e = scene.NewEntity();

    auto p = scene.Assign<Position>(e);
    t.expect_true(p != nullptr, "Assign returns non-null pointer");
    if (p) {
      p->x = 42;
      p->y = 7;
    }

    auto fetched = scene.Get<Position>(e);
    t.expect_true(fetched != nullptr, "Get returns non-null after Assign");
    if (fetched) {
      t.expect_eq(fetched->x, 42, "Fetched component has correct x");
      t.expect_eq(fetched->y, 7, "Fetched component has correct y");
    }

    scene.Remove<Position>(e);
    t.expect_true(scene.Get<Position>(e) == nullptr, "Get returns nullptr after Remove");
  }

  // SceneView iteration
  {
    de::ecs::Scene scene;

    auto e1 = scene.NewEntity();
    auto e2 = scene.NewEntity();
    auto e3 = scene.NewEntity();

    scene.Assign<Position>(e1);
    scene.Assign<Position>(e3);

    de::ecs::SceneView<Position> view(scene);
    int count = 0;
    for (auto id : view) {
      t.expect_true(de::ecs::IsEntityValid(id), "SceneView yields valid entity ids");
      count++;
    }
    t.expect_eq(count, 2, "SceneView returns two entities with Position");

    de::ecs::SceneView<> allView(scene);
    int total = 0;
    for (auto id : allView) {
      t.expect_true(de::ecs::IsEntityValid(id), "AllView yields valid entity ids");
      total++;
    }
    t.expect_eq(total, 3, "SceneView<> returns all 3 entities");
  }

  if (t.failures == 0) {
    std::cout << "All tests passed\n";
    return 0;
  } else {
    std::cerr << t.failures << " test(s) failed\n";
    return 1;
  }
}
