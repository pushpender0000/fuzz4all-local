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
class ArrayWrapper {
public:
    constexpr ArrayWrapper(const T (&arr)[N]) : data_(arr) {}
    auto begin() const { return data_.begin(); }
    auto end() const { return data_.end(); }
private:
    std::vector<T> data_;
};

int main() {
    constexpr int arr1[] = {1, 2, 3};
    ArrayWrapper aw(arr1);

    int result = 0;
    for (const auto& val : aw) {
        if constexpr(IsSame<decltype(val), int>::value) {
            result += multiply(val, add(val, 1));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << result << std::endl;
}