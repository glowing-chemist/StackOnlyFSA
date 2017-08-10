#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <array>
#include <map>
#include <iostream>

#include "state.hpp"

template<typename STATE, typename INPUT, typename T, typename ...F>
class StateMachine {
    public:

    StateMachine(STATE, F...);

    bool advance(INPUT input);

    STATE currentState() const;

    private:
    STATE _currentState;
    std::map<STATE, T*> stateMap;
    std::tuple<F...> states;
};

template<typename STATE, typename INPUT, typename T, typename ...F>
StateMachine<STATE, INPUT, T, F...>::StateMachine(STATE startingState, F... ss) :
    _currentState{startingState}, stateMap{std::map<STATE, T*>{}}
    , states{std::make_tuple(ss...)} 
    {
        auto mapper = [this] (auto& stat) {stateMap[stat.getState()] = &stat;};
        for_each(states, mapper);
    }

template<typename STATE, typename INPUT, typename T, typename ...F>
bool StateMachine<STATE, INPUT, T, F...>::advance(INPUT input) {
    auto oldState = _currentState;
    _currentState = stateMap[_currentState] -> changeState(input);
    return oldState != _currentState;
}

template<typename STATE, typename INPUT, typename T, typename ...F>
STATE StateMachine<STATE, INPUT, T, F...>::currentState() const {
    return _currentState;
}

#endif