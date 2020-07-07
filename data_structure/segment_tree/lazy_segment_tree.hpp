#include <cassert>
#include <vector>

template <class monoid, class homomorphism>
class lazy_segment_tree
{
    using size_type = typename std::vector<monoid>::size_type;

    size_type size_orig, height, size_ext;
    std::vector<monoid> data;
    std::vector<homomorphism> lazy;

    void recalc(const size_type node) { data[node] = data[node << 1] + data[node << 1 | 1]; }

    void apply(size_type index, const homomorphism &homo)
    {
        homo.apply(data[index]);
        if(index < size_ext) lazy[index] *= homo;
    }

    void push(size_type index)
    {
        if(index >= size_ext) return;
        apply(index << 1, lazy[index]);
        apply(index << 1 | 1, lazy[index]);
        lazy[index] = homomorphism{};
    }

    template <class pred_type>
    size_type left_search_subtree(size_type index, const pred_type pred, monoid mono)
    {
        assert(index);
        while(index < size_ext)
        {
            push(index);
            const monoid tmp = data[(index <<= 1) | 1] + mono;
            if(pred(tmp)) mono = tmp;
            else ++index;
        }
        return ++index -= size_ext;
    }

    template <class pred_type>
    size_type right_search_subtree(size_type index, const pred_type pred, monoid mono)
    {
        assert(index);
        while(index < size_ext)
        {
            push(index);
            const monoid tmp = mono + data[index <<= 1];
            if(pred(tmp)) ++index, mono = tmp;
        }
        return (index -= size_ext) < size_orig ? index : size_orig;
    }

public:
    lazy_segment_tree(const size_type n = 0) : size_orig{n}, height(n > 1 ? 32 - __builtin_clz(n - 1) : 0), size_ext{1u << height}, data(size_ext << 1), lazy(size_ext) {}

    lazy_segment_tree(const size_type n, const monoid &init) : lazy_segment_tree(n)
    {
        std::fill(std::next(std::begin(data), size_ext), std::end(data), init);
        for(size_type i{size_ext}; --i; ) recalc(i);
    }

    template <class iter_type, class value_type = typename std::iterator_traits<iter_type>::value_type>
    lazy_segment_tree(iter_type first, iter_type last)
        : size_orig(std::distance(first, last)), height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0), size_ext{1u << height}, data(size_ext << 1), lazy(size_ext)
    {
        static_assert(std::is_constructible<monoid, value_type>::value, "monoid(iter_type::value_type) is not constructible.");
        for(auto iter{std::next(std::begin(data), size_ext)}; iter != std::end(data) && first != last; ++iter, ++first) *iter = monoid(*first);
        for(size_type i{size_ext}; --i; ) recalc(i);
    }

    template <class container_type, typename = typename container_type::value_type>
    lazy_segment_tree(const container_type &cont) : lazy_segment_tree(std::begin(cont), std::end(cont)) {}

    size_type size() const { return size_orig; }
    size_type capacity() const { return size_ext; }

    monoid operator[](size_type index) { return fold(index, index + 1); }

    void update(const size_type index, const homomorphism &homo) { update(index, index + 1, homo); }

    void update(size_type first, size_type last, const homomorphism &homo)
    {
        assert(last <= size_orig);
        if(first >= last) return;
        first += size_ext, last += size_ext - 1;
        for(size_type i = height; i; --i) push(first >> i), push(last >> i);
        for(size_type l = first, r = last + 1; last; l >>= 1, r >>= 1)
        {
            if(l < r)
            {
                if(l & 1) apply(l++, homo);
                if(r & 1) apply(--r, homo);
            }
            if(first >>= 1, last >>= 1)
            {
                recalc(first), recalc(last);
            }
        }
    }

    monoid fold() { return fold(0, size_orig); }

    monoid fold(size_type first, size_type last)
    {
        assert(last <= size_orig);
        if(first >= last) return monoid{};
        first += size_ext, last += size_ext - 1;
        monoid left_val{}, right_val{};
        for(size_type l = first, r = last + 1; last; l >>= 1, r >>= 1)
        {
            if(l < r)
            {
                if(l & 1) left_val = left_val + data[l++];
                if(r & 1) right_val = data[--r] + right_val;
            }
            if(first >>= 1, last >>= 1)
            {
                lazy[first].apply(left_val);
                lazy[last].apply(right_val);
            }
        }
        return left_val + right_val;
    }

    template <class pred_type>
    size_type left_search(size_type right, const pred_type pred)
    {
        assert(right <= size_orig);
        right += size_ext - 1;
        for(size_type i{height}; i; --i) push(right >> i);
        ++right;
        monoid mono{};
        for(size_type left{size_ext}; left != right; left >>= 1, right >>= 1)
        {
            if((left & 1) != (right & 1))
            {
                const monoid tmp = data[--right] + mono;
                if(!pred(tmp)) return left_search_subtree(right, pred, mono);
                mono = tmp;
            }
        }
        return 0;
    }

    template <class pred_type>
    size_type right_search(size_type left, const pred_type pred)
    {
        assert(left <= size_orig);
        left += size_ext;
        for(size_type i{height}; i; --i) push(left >> i);
        monoid mono{};
        for(size_type right{size_ext << 1}; left != right; left >>= 1, right >>= 1)
        {
            if((left & 1) != (right & 1))
            {
                const monoid tmp = mono + data[left];
                if(!pred(tmp)) return right_search_subtree(left, pred, mono);
                mono = tmp;
                ++left;
            }
        }
        return size_orig;
    }
}; //class lazy_segment_tree
