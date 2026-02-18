export module age_engine;
import :system_manager;
import :world;

namespace age 
{

export class Engine 
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
