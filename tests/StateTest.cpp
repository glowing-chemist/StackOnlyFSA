
#include "../src/FSA.hpp"

#include <functional>
#include <string>
#include <cassert>

enum class states {
    start,
    A, 
    B, 
    Z
};

//create state machine for regex [ab]*z
int main() {
    using LINK = std::function<bool(char&)>;

    LINK SA = [] (char& c) {return c == 'a';};
    LINK AB = [] (char& c) {return c == 'b';};
    LINK BZ = [] (char& c) {return c == 'z';};

    auto regex = make_state_machine(
        states::start,
        make_state(
            states::start,
            edge(states::start, states::A, SA)
        ),
        make_state(
            states::A,
            edge(states::A, states::B, AB)
        ),
        make_state(
            states::B,
            edge(states::B, states::A, SA),
            edge(states::B, states::Z, BZ)
        )
    );
    std::string expr = "abababz";
    for(auto& c : expr) {
        auto b = regex.advance(c);
        assert(b == true);
    }
    assert(regex.currentState() == states::Z);
}