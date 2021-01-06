#include <iostream>
#include "instrumented.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>

template <typename Callable>
void count_operations(size_t min_count, size_t max_count, Callable op){
    instrumented<int>::print_header();
    for(size_t n = min_count; n <= max_count; n = n << 1){
        op(n);
    }
}

void count_operations_for_sort(size_t n){
    // generate a vector of size n with random ints
    std::vector<instrumented<int>> v(n);
    std::generate(v.begin(), v.end(), [](){ return std::rand() % INT_MAX; });
    instrumented<int>::initialize(n);
    std::sort(v.begin(), v.end());
    instrumented<int>::print_counts();
}

int main() {
    count_operations(16, 16 * 1024, [](size_t n){
        count_operations_for_sort(n);
    });
}

