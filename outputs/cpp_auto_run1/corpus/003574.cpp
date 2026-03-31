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

template<typename T, std::size_t N>
class StaticVector {
public:
    constexpr T& operator[](std::size_t index) noexcept {
        if (index >= N) throw std::out_of_range("Index out of range");
        return data[index];
    }

    constexpr const T& operator[](std::size_t index) const noexcept {
        if (index >= N) throw std::out_of_range("Index out of range");
        return data[index];
    }

private:
    T data[N];
};

template<typename T, typename F>
constexpr auto transform(const StaticVector<T, 3>& vec, F f) -> std::vector<std::invoke_result_t<F, T>> {
    std::vector<std::invoke_result_t<F, T>> result;
    for (std::size_t i = 0; i < 3; ++i) {
        result.push_back(f(vec[i]));
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    StaticVector<double, 3> vec{{1.1, 2.2, 3.3}};
    auto transformed = transform(vec, [](auto x) { return multiply(x, sum); });

    int result = 0;
    for (const auto& val : transformed) {
        if constexpr(IsSame<decltype(val), double>::value) {
            result += static_cast<int>(val);
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << result << std::endl;
}