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
    Matrix() : data_(N, std::vector<T>(N)) {}

    const std::vector<T>& operator[](std::size_t i) const {
        return data_[i];
    }

    std::vector<T>& operator[](std::size_t i) {
        return data_[i];
    }

private:
    std::vector<std::vector<T>> data_;
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    Matrix<double, 3> matrix;
    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            if constexpr(IsSame<T, double>::value) {
                matrix[i][j] = static_cast<double>(multiply(sum, i + j));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    double result = 0.0;
    for (const auto& row : matrix) {
        for (double val : row) {
            result += val;
        }
    }

    std::cout << static_cast<int>(result) << std::endl;
}