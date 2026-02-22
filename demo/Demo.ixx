export module demo;

import age_engine;

export class Demo
{

public:
    Demo();
    void Initialize();
    void Run();

private:
    age::Engine mEngine;

};
