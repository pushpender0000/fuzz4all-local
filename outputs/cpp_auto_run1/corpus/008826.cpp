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

template<typename T, template<typename> class Container>
void processContainer(const Container<T>& container, T value) {
    for (const auto& item : container) {
        if constexpr(IsSame<decltype(item), T>::value) {
            std::cout << multiply(item, value) << " ";
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            exit(1);
        }
    }
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    processContainer(nestedVector, sum);
}