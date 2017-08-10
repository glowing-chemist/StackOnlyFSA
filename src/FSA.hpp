#ifndef FSA_HPP
#define FSA_HPP

#include <tuple>

#include "state.hpp"
#include "stateMachine.hpp"

/*
use of function make_state_machine ---|
auto machine = make_state_machine( <---
    zero,
    make_state(zero,
        edge(zero, one, func1),
        edge(zero, two, func2)
        ),
    make_state(one,
        edge(one, three, func1),
        edge(one, five, func3)
    )
)
*/

// function template to create function to return state from boolean function
template<typename START, typename END, typename FUNC>
std::function<START(typename Arg<FUNC>::value)> edge(START start, END end, FUNC func) {
    return [=] (typename Arg<FUNC>::value ins) {if(func(ins)) {
        return end;
    }
    return start;
    };
}

// abstract away the template parameters for constructing state machine
template<typename STATE, typename ...F>
auto make_state_machine(STATE start, F ...states) -> StateMachine<STATE, typename first<F...>::value::INPUT_TYPE, typename first<F...>::value, F...> {
    return {start, states...};
}


#endif 