export module age_engine:world;

import :types_list;

namespace age
{

export class World
{
    friend class Engine;

public:
    template <ComponentsList Components>
    void RegisterComponents();

private:
    World() = default;

private:
};

} // namespace age
