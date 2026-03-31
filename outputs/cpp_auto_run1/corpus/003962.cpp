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

    auto operator[](std::size_t idx) const {
        return data[idx];
    }

    auto& operator[](std::size_t idx) {
        return data[idx];
    }
};

template<typename T, std::size_t N>
auto sumMatrixElements(const Matrix<T, N>& mat) {
    T result = 0;
    for (const auto& row : mat.data) {
        for (const auto& elem : row) {
            result += elem;
        }
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    Matrix<double, 3> mat;
    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            if constexpr(IsSame<decltype(mat[i][j]), double>::value) {
                mat[i][j] = static_cast<double>(i + j);
            } else {
                std::cout << "Error: Incorrect type used in matrix initialization." << std::endl;
                return 1;
            }
        }
    }

    auto totalSum = sumMatrixElements(mat);
    constexpr int expectedSum = (0+1+2) + (1+2+3) + (2+3+4); // Sum of diagonal elements in a 3x3 matrix
    if (std::abs(totalSum - static_cast<double>(expectedSum)) > 1e-6) {
        std::cout << "Error: Matrix sum calculation is incorrect." << std::endl;
        return 1;
    }

    std::cout << totalSum << std::endl;
}