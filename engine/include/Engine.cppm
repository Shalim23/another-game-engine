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

private:
  void Setup();

private:
  SystemManager mSystemManager{};
  World mWorld{};

};

} // namespace age
