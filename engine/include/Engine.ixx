export module age_engine;

export import :system_manager;
import :world;

export namespace age
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
