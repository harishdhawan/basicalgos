// instrumented<MyClass> will give a wraped class which will have all the
// functionality which MyClass has, but it will count the number of all operations
// for a totally-ordered type.
//
// This can be used to measure the performance of an algorithm.
//
// example usage:
// vector<instrumented<int>> instrumented_int_vector;
// std::sort(instrumented_int_vector);
// display_stats(instrumented_int_vector)
//

#include <cstddef>

// struct to collect stats
struct instrumented_base {
    enum operations {
        n,
        copy,
        assignment,
        destructor,
        default_constructor,
        equality,
        comparison,
        construction
    };
    static constexpr size_t number_ops = 8;
    static const char* counter_names[number_ops];
    static double counts[number_ops];

    static void initialize(size_t);
    static void print_counts();
    static void print_header();
    static const size_t column_width = 15;
};

template <typename T>
struct instrumented : public instrumented_base {
    T value;

    // Conversions
    instrumented(const T& x): value(x) {}
    explicit operator T() const { return value; }

    // semi-regular
    // .. assignment, default constructor, copy constructor
    instrumented() {
        ++counts[default_constructor];
    }
    ~instrumented() {
        ++counts[destructor];
    }

    instrumented& operator=(const instrumented& x) {
        ++counts[assignment];
        value = x.value;
        return *this;
    }

    instrumented(const instrumented& x): value(x.value) {
        ++counts[copy];
    }

    // regular
    // .. equality, inequality
    friend
    bool operator==(const instrumented& a, const instrumented& b){
        ++counts[equality];
        return a.value == b.value;
    }

    friend
    bool operator!=(const instrumented& a, const instrumented& b){
        return !(a==b);
    }

    // totally-ordered
    // .. less, greater, less or equal, greater or equal
    friend
    bool operator<(const instrumented& a, const instrumented& b){
        ++counts[comparison];
        return a.value < b.value;
    }

    friend
    bool operator>(const instrumented& a, const instrumented& b){
        return b < a;
    }

    friend
    bool operator<=(const instrumented& a, const instrumented& b){
        return !(b < a);
    }

    friend
    bool operator>=(const instrumented& a, const instrumented& b){
        return !(a < b);
    }
};