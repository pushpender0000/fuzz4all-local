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
class Container {
public:
    void push_back(const std::vector<T>& vec) {
        data.push_back(vec);
    }

    void print() const {
        for (const auto& vec : data) {
            for (const auto& val : vec) {
                if constexpr(IsSame<decltype(val), T>::value) {
                    std::cout << multiply(val, add(T{1}, T{2})) << " ";
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    std::exit(1);
                }
            }
        }
    }

private:
    std::vector<std::vector<T>> data;
};

int main() {
    Container<double> container;
    container.push_back({1.1, 2.2, 3.3});
    container.push_back({4.4, 5.5, 6.6});
    container.print();
}