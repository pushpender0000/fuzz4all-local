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

template<typename T, size_t N>
class StaticVector {
public:
    constexpr T& operator[](size_t index) {
        if (index >= N) throw std::out_of_range("Index out of range");
        return data[index];
    }
private:
    T data[N];
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    StaticVector<double, 3> vec1{{1.1, 2.2, 3.3}};
    StaticVector<double, 3> vec2{{4.4, 5.5, 6.6}};

    int result = 0;
    auto multiply_sum = [&](const std::vector<double>& v) {
        for (auto val : v) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return;
            }
        }
    };

    multiply_sum(vec1);
    multiply_sum(vec2);

    std::cout << result << std::endl;
}