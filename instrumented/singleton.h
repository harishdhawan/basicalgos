// singleton is a class which wraps any class and maps all the 
// operations.
// It's called singleton because it wraps one single type.
// Purpose is to be used as template for creating other classes.
template <typename T>
struct singleton {
    T value;

    // Conversions
    explicit singleton(const T& x): value(x) {}
    explicit operator T() const { return value; }

    // semi-regular
    // .. assignment, default constructor, copy constructor
    singleton() {}
    ~singleton() {}

    singleton& operator=(const singleton& x) {
        value = x.value;
        return *this;
    }

    singleton(const singleton& x): value(x.value) {}

    // regular
    // .. equality, inequality
    friend
    bool operator==(const singleton& a, const singleton& b){
        return a.value == b.value;
    }

    friend
    bool operator!=(const singleton& a, const singleton& b){
        return !(a==b);
    }

    // totally-ordered
    // .. less, greater, less or equal, greater or equal
    friend
    bool operator<(const singleton& a, const singleton& b){
        return a.value < b.value;
    }

    friend
    bool operator>(const singleton& a, const singleton& b){
        return b < a;
    }

    friend
    bool operator<=(const singleton& a, const singleton& b){
        return !(b < a);
    }

    friend
    bool operator>=(const singleton& a, const singleton& b){
        return !(a < b);
    }
};