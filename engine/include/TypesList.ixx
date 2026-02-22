export module age_engine:types_list;

import std;

namespace age
{
    export template <typename... Types>
	struct TypesList
	{
        static constexpr std::size_t size = sizeof...(Types);
	};
    
    template <typename T>
    concept Component = std::is_class_v<T> && std::is_trivial_v<T> && std::is_standard_layout_v<T>;

	template <typename T>
	inline constexpr bool is_components_list_v = false;

	template <typename... Types>
	inline constexpr bool is_components_list_v<TypesList<Types...>> = (Component<Types> && ...);

	export template <typename T>
	concept ComponentsList = is_components_list_v<T>;

    template <typename T>
    concept System = requires(T t) { t.Update(); };

    template <typename T>
    inline constexpr bool is_systems_list_v = false;

    template <typename... Systems>
    inline constexpr bool is_systems_list_v<TypesList<Systems...>> = (System<Systems> && ...);

    export template <typename T>
    concept SystemsList = is_systems_list_v<T>;
}
