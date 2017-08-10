#ifndef REDUCECONNECTIONS_HPP
#define REDUCECONNECTIONS_HPP

#include <array>

#include "forEach.hpp"

template<typename STATE, typename INPUT, typename ...Fs>
auto reduceConnections(Fs ...funcs) {
    return [=] (STATE state, INPUT input) {
        std::array<STATE, sizeof...(Fs)> funcArray = {funcs(input)...};
        for(auto i = 0; i < sizeof...(Fs);i++) {
            if(funcArray[i] != state) {
                return funcArray[i];
            }
        }
        return state;
    };
}

#endif