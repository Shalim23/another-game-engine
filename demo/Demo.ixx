module;

#include <age_engine/Engine.hpp>

export module demo;

export class Demo
{

public:
    Demo();
    void Initialize();
    void Run();

private:
    age::Engine mEngine;

};
