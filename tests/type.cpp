#include <typeinfo>
#include <iostream>
#include <functional>

struct test {
    int operator()(bool b) {
        return 1;
    }
};


template<typename F>
struct Arg {
    using value = typename Arg<decltype(&F::operator())>::value;
};

template<typename RET, typename ARG>
struct Arg<RET (*)(ARG)> {
    using value = ARG;
};

template<typename RET, typename ARG>
struct Arg<std::function<RET(ARG)>> {
    using value = ARG;
};

template<typename RET, typename ARG, typename F>
struct Arg<RET (F::*)(ARG) const> {
    using value = ARG;
};

int main() {
    auto a = [] (int a) {return 2.0;};
    using ta = Arg<decltype(a)>::value;
}