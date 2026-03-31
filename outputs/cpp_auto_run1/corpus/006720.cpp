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
    void push_back(const T& value) {
        data.push_back(value);
    }

    auto begin() const {
        return data.begin();
    }

    auto end() const {
        return data.end();
    }

private:
    std::vector<T> data;
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    Container<double> nestedContainer;
    nestedContainer.push_back(1.1);
    nestedContainer.push_back(2.2);
    nestedContainer.push_back(3.3);

    int result = 0;
    for (const auto& val : nestedContainer) {
        if constexpr(IsSame<decltype(val), double>::value) {
            result += static_cast<int>(multiply(val, sum));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << result << std::endl;
}