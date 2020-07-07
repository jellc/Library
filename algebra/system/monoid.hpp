struct mono
{
    mono() {}

    // binary operation
    mono operator+(const mono& rhs) const { return mono{*this} += rhs; }

    // operation assignment
    mono &operator+=(const mono &rhs);
};


template <class T>
struct min_mono
{
    T val;
    min_mono(T v) : val(v) {}

    // binary operation
    min_mono operator+(const min_mono& rhs) const { return min_mono{*this} += rhs; }

    // operation assignment
    min_mono &operator+=(const min_mono &rhs)
    {
        if(val > rhs.val) val = rhs.val;
        return *this;
    }
};


template <class T>
struct max_mono
{
    T val;
    max_mono(T v) : val(v) {}

    // binary operation
    max_mono operator+(const max_mono& rhs) const { return max_mono{*this} += rhs; }

    // operation assignment
    max_mono &operator+=(const max_mono &rhs)
    {
        if(val < rhs.val) val = rhs.val;
        return *this;
    }
};