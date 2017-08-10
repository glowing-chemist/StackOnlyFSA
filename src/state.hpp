#ifndef STATE_HPP
#define STATE_HPP

#include <array>
#include <type_traits>
#include <functional>

#include "forEach.hpp"
#include "reduceConnections.hpp"

template<typename STATE, typename INPUT>
class state {
    public:
    using INPUT_TYPE = INPUT;

    state(STATE state, std::function<STATE(STATE, INPUT)> connections);

    STATE changeState(INPUT input) const;

    STATE getState() const;

    private:
    std::function<STATE(STATE, INPUT)> funcs;
    STATE myState;
};

template<typename STATE, typename INPUT>
state<STATE, INPUT>::state(STATE state, std::function<STATE(STATE, INPUT)> connections) :
    funcs{std::function<STATE(STATE, INPUT)>{connections}}, myState{state} {}

template<typename STATE, typename INPUT>
STATE state<STATE, INPUT>::changeState(INPUT input) const {
    return funcs(myState, input);
}

template<typename STATE, typename INPUT, template<typename F> typename ...func>
auto make_state(STATE myState, func<STATE(INPUT)> ...Fs) -> state<STATE, INPUT> {
    return {myState, reduceConnections<STATE, INPUT, decltype(Fs)...>(Fs...)};
}

template<typename STATE, typename ...Fs>
auto make_state(STATE myState, Fs ...funcs) -> state<STATE, typename ArgFromFirst<Fs...>::value> {
    return {myState, reduceConnections<STATE, typename ArgFromFirst<Fs...>::value, Fs...>(funcs...)};
}

template<typename STATE, typename INPUT>
STATE state<STATE, INPUT>::getState() const {
    return myState;
}

#endif