template<typename ... Trest>
struct AreUniqueTypes;

template<typename T1, typename T2, typename... Trest>
struct AreUniqueTypes<T1, T2, Trest ...>
 : AreUniqueTypes<T1, T2>, AreUniqueTypes<T1, Trest ...>, AreUniqueTypes<T2, Trest ...> {};

template <typename T1, typename T2>
struct AreUniqueTypes<T1, T2>
{
    static_assert(!std::is_same<T1, T2>::value, "Types must be unique");
};
