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

    StaticVector<double, 3> vec1 = {{1.1, 2.2, 3.3}};
    StaticVector<double, 3> vec2 = {{4.4, 5.5, 6.6}};

    int result = 0;
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if constexpr(IsSame<decltype((vec1[j])), double>::value && IsSame<decltype((vec2[j])), double>::value) {
                result += static_cast<int>(multiply(vec1[j], vec2[j]));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result << std::endl;
}