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
class Matrix {
public:
    std::vector<std::vector<T>> data;

    constexpr Matrix() : data(N, std::vector<T>(N)) {}

    auto operator()(std::size_t i, std::size_t j) -> T& {
        return data[i][j];
    }
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    Matrix<double, 3> matrix;
    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            if constexpr(IsSame<decltype(sum), double>::value) {
                matrix(i, j) = multiply(static_cast<double>(i + j), sum);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    double result = 0.0;
    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            result += matrix(i, j);
        }
    }

    std::cout << static_cast<int>(result) << std::endl;
}