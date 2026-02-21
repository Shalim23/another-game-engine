#pragma once
#include "SystemManager.hpp"
#include "World.hpp"

namespace age 
{

class Engine 
{

public:
  Engine();
  void Initialize();

  SystemManager& GetSystemManager() { return mSystemManager; }
  const SystemManager& GetSystemManager() const { return mSystemManager; }

private:
  SystemManager mSystemManager{};
  World mWorld{};

};

} // namespace age
