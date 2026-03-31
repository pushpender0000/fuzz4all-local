#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
constexpr auto multiply(T a, U b) {
    return a * b;
}

template<typename T>
class Container {
public:
    Container(const std::vector<T>& values) : data_(values) {}

    template<typename U>
    void printProduct() const {
        if constexpr (std::is_arithmetic_v<U>) {
            T product = 1;
            for (const auto& item : data_) {
                product *= static_cast<T>(item);
            }
            std::cout << static_cast<int>(product) << "\n";
        } else {
            std::cout << "Unsupported type\n";
        }
    }

private:
    std::vector<T> data_;
};

template<typename T, typename U>
struct is_valid : std::true_type {};

int main() {
    constexpr int a = 5;
    volatile double b = 3.14;

    auto lambda = [](auto x) {
        return x * x;
    };

    std::vector<int> vec = {1, 2, 3, 4, 5};
    Container<int> container(vec);
    container.printProduct();

    auto result = multiply(a, static_cast<int>(b));
    std::cout << "Result of multiplication: " << result << "\n";

    return lambda(result) + 10;
}