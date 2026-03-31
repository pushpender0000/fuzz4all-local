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
class Container {
public:
    std::vector<T> vec;

    void push(const T& value) {
        if constexpr (IsSame<T, int>::value) {
            for (int i = 0; i < static_cast<int>(value); ++i) {
                vec.push_back(i * 2);
            }
        } else {
            std::cout << "Error: Incorrect type used in container." << std::endl;
        }
    }
};

template<typename T, typename U>
void processData() {
    Container<T> c1;
    c1.push(static_cast<T>(5));

    Container<U> c2;
    c2.push(static_cast<U>(3));

    int result = 0;
    for (const auto& val : c1.vec) {
        if constexpr (IsSame<decltype(val), int>::value) {
            result += add(val, static_cast<int>(multiply(static_cast<T>(2), static_cast<U>(3))));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
        }
    }

    for (const auto& val : c2.vec) {
        if constexpr (IsSame<decltype(val), int>::value) {
            result += add(val, static_cast<int>(multiply(static_cast<T>(2), static_cast<U>(3))));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
        }
    }

    std::cout << result << std::endl;
}

int main() {
    processData<double, float>();
}