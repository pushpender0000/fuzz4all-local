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

template<typename T, typename U>
class NestedTemplate {
public:
    NestedTemplate(const std::vector<U>& data) : data_(data) {}

    auto calculate() const {
        if constexpr (IsSame<T, int>::value) {
            return std::accumulate(data_.begin(), data_.end(), 0, [](int sum, U val) {
                return sum + static_cast<int>(multiply(val, T{2}));
            });
        } else if constexpr (IsSame<T, double>::value) {
            return std::accumulate(data_.begin(), data_.end(), 0.0, [](double sum, U val) {
                return sum + multiply(val, T{1.5});
            });
        } else {
            throw std::invalid_argument("Unsupported type");
        }
    }

private:
    const std::vector<U>& data_;
};

int main() {
    constexpr int a = 5;
    constexpr double b = 7.1;
    auto sum = add(a, static_cast<decltype(a)>(b));

    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2}, {3.3, 4.4}};
    NestedTemplate<double, double> nt(nestedVector[0]);
    auto result = nt.calculate();

    std::cout << static_cast<int>(result) << std::endl;
}