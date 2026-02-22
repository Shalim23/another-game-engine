export module age_engine:system_manager;

import :types_list;
import std;

namespace age
{

export class SystemManager
{
    friend class Engine;

public:
    template <SystemsList Systems>
    void RegisterSystems();

private:
    SystemManager() = default;

private:
    
};

} // namespace age
