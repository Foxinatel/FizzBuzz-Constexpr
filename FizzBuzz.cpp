#include <iostream>
#include <utility>

#define Fizz(n) (n%3==0)
#define Buzz(n) (n%5==0)

template <char... Cs>
struct string_literal {
    constexpr static char value[] = {(Cs)...,0};
};

template<char... digits>
struct to_chars { constexpr static auto value = string_literal<(digits+'0')..., '\n'>{};};

template<char rem, char... digits>
struct explode : explode<rem / 10, rem % 10, digits...> {};

template<char... digits>
struct explode<0, digits...> : to_chars<digits...> {};

template <char... Cs1, char... Cs2>
constexpr auto operator+(string_literal<Cs1...> a, string_literal<Cs2...> b) {
    return string_literal<Cs1..., Cs2...>{};
}

template <class charT = char, charT... Cs>
constexpr auto operator""_S(){
    return string_literal<Cs..., '\n'>{};
};

template<size_t n>
constexpr auto FizzBuzz() {
    if constexpr (Fizz(n) && Buzz(n)) return "FizzBuzz"_S;
    else if constexpr (Fizz(n)) return "Fizz"_S;
    else if constexpr (Buzz(n)) return "Buzz"_S;
    else {
        return explode<n>::value;
    }
}

int main() {
    []<size_t... Vs>(std::index_sequence<Vs...>){
        std::cout << (FizzBuzz<Vs+1>() + ...).value;
    }(std::make_index_sequence<100>{});
}