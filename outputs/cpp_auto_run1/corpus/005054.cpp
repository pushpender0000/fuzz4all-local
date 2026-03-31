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
class StaticVector {
public:
    constexpr StaticVector(const std::initializer_list<T>& list) : data_(list) {}
    auto begin() const { return data_.begin(); }
    auto end() const { return data_.end(); }
private:
    std::vector<T> data_;
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    StaticVector<double> nestedVector{ {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6} };

    double result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += multiply(val, sum);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << static_cast<int>(result) << std::endl;
}