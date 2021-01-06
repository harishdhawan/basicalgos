#include "instrumented.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

double instrumented_base::counts[];
const char* instrumented_base::counter_names[number_ops] = {
    "n",
    "copy",
    "assign",
    "destruct",
    "default",
    "equal",
    "less",
    "construction"
};

void instrumented_base::initialize(size_t m) {
    std::fill(counts, counts + number_ops, 0.0);
    counts[n] = double(m);
}

void instrumented_base::print_counts() {
    for(auto x : counts) {
        std::cout << std::setw(column_width) << x;
    }
    std::cout << std::endl;
}

void instrumented_base::print_header() {
    for(auto x : counter_names) {
        std::cout << std::setw(column_width) << x;
    }
    std::cout << std::endl;
}