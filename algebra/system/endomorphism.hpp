struct endo
{
    // compose.
    void operator*=(const endo& rhs);

    // apply self to an element of X.
    template <class X>
    void apply(X &rhs) const;
};