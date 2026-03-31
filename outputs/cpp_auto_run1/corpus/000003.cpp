#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
constexpr auto multiply(T a, U b) {
    return a * b;
}

template<typename T, typename U>
struct MultiplyContainer {
    std::vector<T> data_;
    MultiplyContainer(const std::vector<T>& values) : data_(values) {}

    template<typename V, typename = std::enable_if_t<!std::is_same_v<V, void>>>
    auto multiplyElements() const {
        T product = 1;
        for (const auto& item : data_) {
            if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) {
                product *= static_cast<V>(item);
            }
        }
        return product;
    }
};

int main() {
    constexpr int a = 5;
    volatile double b = 3.14;

    auto lambda = [](auto x) {
        return x * x;
    };

    std::vector<int> vec = {1, 2, 3, 4, 5};
    MultiplyContainer container(vec);
    auto result = container.multiplyElements<double>();
    std::cout << "Product of elements: " << result << "\n";

    return static_cast<int>(lambda(result));
}