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
class Matrix {
public:
    std::vector<std::vector<T>> data;

    Matrix(const std::initializer_list<std::initializer_list<T>>& list) : data() {
        for (const auto& row : list) {
            data.push_back(row);
        }
    }

    template<typename U>
    auto operator*(const Matrix<U>& other) const -> Matrix<decltype(multiply(*data[0].begin(), *other.data[0].begin()))> {
        static_assert(IsSame<T, U>::value, "Matrix types must be the same");
        std::vector<std::vector<decltype(multiply(*data[0].begin(), *other.data[0].begin()))>> result;
        for (size_t i = 0; i < data.size(); ++i) {
            std::vector<decltype(multiply(*data[0].begin(), *other.data[0].begin()))> row;
            for (size_t j = 0; j < other.data[0].size(); ++j) {
                decltype(multiply(*data[0].begin(), *other.data[0].begin())) sum = 0;
                for (size_t k = 0; k < data[0].size(); ++k) {
                    sum += multiply(data[i][k], other.data[k][j]);
                }
                row.push_back(sum);
            }
            result.push_back(row);
        }
        return Matrix<decltype(multiply(*data[0].begin(), *other.data[0].begin()))>(result);
    }
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    Matrix<double> mat1({{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}});
    Matrix<double> mat2({{0.1, -0.2, 0.3}, {-0.4, 0.5, -0.6}});

    auto result = mat1 * mat2;

    std::cout << "Result matrix: \n";
    for (const auto& row : result.data) {
        for (double val : row) {
            if constexpr(IsSame<decltype(val), double>::value) {
                std::cout << val << " ";
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
        std::cout << "\n";
    }
}