module age_engine:concepts;

namespace age
{
    template<typename T>
    concept System = requires(T sys, float dt)
    {
        { sys.Update(dt) };
    };
} // namespace age
