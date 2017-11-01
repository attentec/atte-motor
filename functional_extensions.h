#ifndef FUNCTIONAL_EXTENSIONS_H
#define FUNCTIONAL_EXTENSIONS_H

#include <experimental/optional>
#include <functional>

template <class T, class F, class R = typename std::result_of<F(T)>::type>
std::experimental::optional<R> fmap(std::experimental::optional<T> value, F f)
{
    if (value) {
        return std::experimental::make_optional(f(*value));
    }
    return std::experimental::nullopt;
}

#endif
