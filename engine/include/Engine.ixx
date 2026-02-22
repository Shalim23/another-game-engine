export module age_engine;

import :system_manager;
import :world;

namespace age
{

export class Engine
{

public:
    Engine() = default;

    SystemManager& GetSystemManager() { return mSystemManager; }
    const SystemManager& GetSystemManager() const { return mSystemManager; }
    World& GetWorld() { return mWorld; }
    const World& GetWorld() const { return mWorld; }

private:
    SystemManager mSystemManager{};
    World mWorld{};

};

} // namespace age
