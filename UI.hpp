#ifndef _UI_HPP_
#define _UI_HPP_

#include <tuple>
#include <cstring>
#include "AreUniqueTypes.hpp"
using std::tuple;
using std::get;

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
// It should be a callable object with a GetTrigger() method
template<Callable SelfType>
concept Command = requires(SelfType a, Trigger t)
{
    { a.GetTrigger() } -> const char *;
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


#endif