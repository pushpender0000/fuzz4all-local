#include <iostream>
#include <vector>
#include <type_traits>

template<typename T>
struct is_container {
    static constexpr bool value = false;
};

template<typename T, typename A>
struct is_container<std::vector<T, A>> {
    static constexpr bool value = true;
};

template<typename T>
void print_if_container(const T& obj) {
    if constexpr (is_container<T>::value) {
        for (const auto& item : obj) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    } else {
        std::cout << "Not a container\n";
    }
}

template<typename T>
struct has_size_method {
    template<typename U>
    static constexpr auto test(U* p) -> decltype(p->size(), std::true_type());

    template<typename>
    static constexpr std::false_type test(...);

    static constexpr bool value = decltype(test<T>(nullptr))::value;
};

template<typename T>
void print_if_has_size(const T& obj) {
    if constexpr (has_size_method<T>::value) {
        std::cout << "Size: " << obj.size() << "\n";
    } else {
        std::cout << "No size method\n";
    }
}

template<typename T>
constexpr bool is_even(const T& value) {
    return (value % 2 == 0);
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    print_if_container(vec);
    print_if_has_size(vec);

    int num = 6;
    if (is_even(num)) {
        std::cout << "Even number: " << num << "\n";
    } else {
        std::cout << "Odd number: " << num << "\n";
    }

    return 0;
}