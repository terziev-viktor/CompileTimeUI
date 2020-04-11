#include <tuple>
#include <cstring>
#include <string>
#include <iostream>

using std::tuple;
using std::get;

typedef const char * Trigger;

template<const int index, typename... Types>
constexpr void foreach_tuple(std::tuple<Types...> t, auto callable)
{
    if constexpr (index < 0)
    {
        throw std::exception("Invalid index in iterate<index, Component...>");
    }
    else if constexpr (index < sizeof...(Types))
    {
        callable(std::get<index>(t));
        foreach_tuple<index + 1, Types...>(t, callable);
    }
    else
    {
        return; // Bottom of recursion
    }
}

// Iterate a tuple with a lambda.
template<typename... Types>
constexpr void foreach(std::tuple<Types...> t, auto callable)
{
    foreach_tuple<0, Types...>(t, callable);
}

template<typename SelfType>
concept Callable = requires(SelfType x, char ** args, int argscount)
{
    { x(args, argscount) } -> void;
};

// A command should satisfy this concept:
// It should be a callable obect with a GetTrigger() method
template<Callable SelfType>
concept Command = requires(SelfType a, Trigger t)
{
    { a.GetTrigger() } -> const char *;
};

struct Print
{
    Trigger GetTrigger() { return "Print"; }

    void operator()(char **, int)
    {
        puts("Print Command");
    }
};

struct Calc
{
    Trigger GetTrigger() { return "Calc"; }

    void operator()(char **, int)
    {
        puts("Calc Command");
    }
};

struct SayHello
{
    Trigger GetTrigger() { return "Say"; }

    void operator()(char **, int)
    {
        puts("Say Command");
    }
};

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

template<Command... CommandTypes>
struct UI : AreUniqueTypes<CommandTypes...>
{
    std::tuple<CommandTypes...> Commands;

    constexpr void CallByTrigger(char t[50], char ** a, int b)
    {
        foreach(Commands, [a, b, t](auto C) 
        {
            if (strcmp(t, C.GetTrigger()) == 0)
            {
                C(a, b);
            }
        });
    }
};

int main(char ** args, int argc)
{
    UI<Print, Calc, SayHello> ui;
    ui.CallByTrigger("Calc", nullptr, 0);

    char c[50];
    std::cout << "Enter the command:";
    std::cin >> c;

    ui.CallByTrigger(c, nullptr, 0);
    return 0;
}