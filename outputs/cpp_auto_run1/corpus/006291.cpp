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
    void addElement(const T& element) {
        elements.push_back(element);
    }

    auto sumElements() const {
        T total = T();
        for (const auto& elem : elements) {
            if constexpr(IsSame<T, double>::value) {
                total += static_cast<int>(multiply(elem, 2.0));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                exit(1);
            }
        }
        return total;
    }

private:
    std::vector<T> elements;
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    Container<double> doubleContainer;
    doubleContainer.addElement(1.1);
    doubleContainer.addElement(2.2);
    doubleContainer.addElement(3.3);

    int result = doubleContainer.sumElements();

    std::cout << result << std::endl;
}