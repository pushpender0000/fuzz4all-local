#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T>
constexpr auto add(T a, T b) -> T {
    return a + b;
}

template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

template<typename T>
struct Container {
    std::vector<T> data;
};

template<typename T, typename U>
void processData(const Container<T>& container, const U& value) {
    if constexpr (IsSame<T, int>::value) {
        for (const auto& item : container.data) {
            std::cout << multiply(item, value) << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Error: Incorrect type used in calculation." << std::endl;
    }
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    Container<double> doubleContainer{std::vector<double>{1.1, 2.2, 3.3}};
    Container<int> intContainer{std::vector<int>{4, 5, 6}};

    processData(doubleContainer, sum);
    processData(intContainer, sum);
}