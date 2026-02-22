export module age_engine;

export import :system_manager;
export import :world;

namespace age
{

export class Engine
{

public:
    Engine();
    void Initialize();

    SystemManager& GetSystemManager() { return mSystemManager; }
    const SystemManager& GetSystemManager() const { return mSystemManager; }
    World& GetWorld() { return mWorld; }
    const World& GetWorld() const { return mWorld; }

private:
    SystemManager mSystemManager{};
    World mWorld{};

};

} // namespace age
