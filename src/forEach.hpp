#ifndef FOREACH_HPP
#define FOREACH_HPP

#include <tuple>
#include <array>

template <typename Tuple, typename F, std::size_t ...Indices>
void for_each_impl(Tuple&& tuple, F&& f, std::index_sequence<Indices...>) {
    using swallow = int[];
    (void)swallow{1,
        (f(std::get<Indices>(std::forward<Tuple>(tuple))), void(), int{})...
    };
}

template <typename Tuple, typename F>
void for_each(Tuple&& tuple, F&& f) {
    constexpr std::size_t N = std::tuple_size<std::remove_reference_t<Tuple>>::value;
    for_each_impl(std::forward<Tuple>(tuple), std::forward<F>(f),
                  std::make_index_sequence<N>{});
}

//###############################################################

template<typename N1, typename ...Nth> //helper meta function
struct first {
    using value = N1;
};

//#################################################################

template<typename F>
struct Arg {
    using value = typename Arg<decltype(&F::operator())>::value;
};

template<typename RET, typename ARG>
struct Arg<std::function<RET(ARG)>> {
    using value = ARG;
};

template<typename RET, typename ARG, typename F>
struct Arg<RET (F::*)(ARG) const> {
    using value = ARG;
};

template<typename RET, typename ARG, typename F>
struct Arg<RET (F::*)(ARG)> {
    using value = ARG;
};

template<typename RET, typename ARG>
struct Arg<RET (*)(ARG)> {
    using value = ARG;
};


template<typename ...F>
struct ArgFromFirst {
    using value = typename Arg<typename first<F...>::value>::value;
};

//#################################################################

template<typename F>
struct Ret;

template<typename RET, typename ARG>
struct Ret<std::function<RET(ARG)>> {
    using value = Ret;
};

template<typename RET, typename ARG, typename F>
struct Ret<RET (F::*)(ARG)> {
    using value = RET;
};

template<typename RET, typename ARG, typename F>
struct Ret<RET (F::*)(ARG) const> {
    using value = RET;
};

#endif