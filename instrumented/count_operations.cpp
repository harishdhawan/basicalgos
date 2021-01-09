/**
 * Use instrumented<> template to measure the common operations of 
 * semi-regular, regular and totally-ordered types.
 * I should be able to use code like below:
 * // Assuming I have a generic function..
 * // size_t MyBinarySearch(vector<T> v, T val);
 * // which I want to measure.
 * instrumented<T>::initialize(); // this resets the numbers.
 * count_operations(v1.size(), [](){MyBinarySearch(vector<instrumented<T>> v1, instrumented<T> val1);});
 * count_operations(v2.size(), [](){MyBinarySearch(vector<instrumented<T>> v2, instrumented<T> val2);});
 * count_operations(v3.size(), [](){MyBinarySearch(vector<instrumented<T>> v3, instrumented<T> val3);});
 * ...
 * 
 * And then I can use instrumented<T> to get the measured numbers..
 * instrumented<T>::print_results();
 * 
 * The print_results() method will print to stdout, number of all common operations
 * which occurred on type T since last call to instrumented<T>::initialize().
 * There is 1 unique row for each value of first param to count_operations().
 * Duplicate value will override last data.
 * 
 * */
#include <iostream>
#include "instrumented.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <sstream>

template <typename T, typename Callable>
void for_doubling_sizes(size_t min_input_size, size_t max_input_size, Callable task){
    for(size_t input_size = min_input_size; input_size <= max_input_size; input_size = input_size << 1){
        task(input_size);
    }
}

template <typename T, typename Callable>
void measure_vector_sort(Callable random_element_generator) {
    using InstrumentedType = instrumented<T>;
    InstrumentedType::print_header();
    for_doubling_sizes<InstrumentedType>(2, 16 * 1024, [&](const size_t n){
        std::vector<InstrumentedType> v(n);
        std::generate(v.begin(), v.end(), random_element_generator);
        InstrumentedType::reset_counts(n);
        std::sort(v.begin(), v.end());
        InstrumentedType::print_counts();
    });
}

int main() {
    measure_vector_sort<int>([](){
        return std::rand() % INT_MAX;
    });
    measure_vector_sort<double>([](){
        return (std::rand() % INT_MAX) * 1.0;
    });
    measure_vector_sort<std::string>([](){
        std::stringstream ss;
        ss << std::rand() % INT_MAX; 
        return ss.str();
    });
}

