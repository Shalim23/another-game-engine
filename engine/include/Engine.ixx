export module engine;

import :system_manager;
import :world;

export class Engine
{

public:
    Engine() = default;

private:
    SystemManager mSystemManager{};
    World mWorld{};

};
