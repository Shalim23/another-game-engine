export module engine;

import :system_manager;
import :world;

export class Engine
{

public:
    Engine() = default;
    ~Engine();

    void init();
    bool runFrame();

    // template<Systems>
    // void registerSystems();

    // template<Components>
    // void registerComponents();

    // template<T>
    // T& getSystem();

    // template<T>
    // T& getComponents();
    

private:
    SystemManager mSystemManager{};
    World mWorld{};

};
