---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: test/library-checker/static_range_inversions_query.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/static_range_inversions_query.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-04 01:52:57+09:00


* see: <a href="https://judge.yosupo.jp/problem/static_range_inversions_query">https://judge.yosupo.jp/problem/static_range_inversions_query</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/data_structure/Mo.hpp.html">data_structure/Mo.hpp</a>
* :heavy_check_mark: <a href="../../../library/data_structure/segment_tree/segment_tree.hpp.html">data_structure/segment_tree/segment_tree.hpp</a>
* :heavy_check_mark: <a href="../../../library/utils/coordinate_compression.hpp.html">utils/coordinate_compression.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"
#include "../../data_structure/Mo.hpp"
#include "../../utils/coordinate_compression.hpp"
#include "../../data_structure/segment_tree/segment_tree.hpp"
#include <cstdio>
using i64=int64_t;

int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    std::vector<int> a(n);
    for(int &x: a) scanf("%d",&x);
    coordinate_compression ccmp(a);
    std::vector<int> cnt(ccmp.count());
    segment_tree<int> seg(n);
    int nl=0,nr=0;
    i64 invs=0;
    auto add=[&](int i)
    {
        int nv=ccmp[i];
        if(i<nl) // left end
        {
            invs+=seg.fold(0,nv);
            nl--;
        }
        else // right end
        {
            invs+=seg.fold(nv+1,n);
            nr++;
        }
        seg[nv]++;
    };
    auto del=[&](int i)
    {
        int nv=ccmp[i];
        if(i==nl) // left end
        {
            invs-=seg.fold(0,nv);
            nl++;
        }
        else // right end
        {
            assert(nr==i+1);
            invs-=seg.fold(nv+1,n);
            nr--;
        }
        seg[nv]--;
    };
    Mo mo(n,add,del);
    for(int i=0; i<q; i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        mo.set(l,r);
    }
    std::vector<i64> ans(q);
    for(int i=0; i<q; i++)
    {
        int id=mo.process();
        ans[id]=invs;
    }
    for(i64 x: ans) printf("%lld\n",x);
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/static_range_inversions_query.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"
#line 1 "data_structure/Mo.hpp"
#include <cassert>
#include <cmath>
#include <functional>
#include <vector>

template <class Add, class Del>
class Mo
{
    Add add; Del del;
    std::vector<size_t> lft, rgt, ord;
    std::vector<size_t>::iterator itr;
    bool made;
    size_t width, nl, nr;

    void make()
    {
        made = true;
        ord.resize(size());
        for(size_t i = 0; i != size(); ++i) ord[i] = i;
        std::sort(ord.begin(), ord.end(),
        [&](size_t x, size_t y)
        {
            if(lft[x] / width != lft[y] / width) return lft[x] < lft[y];
            return rgt[x] < rgt[y];
        });
        itr = ord.begin();
    }

public:
    Mo(size_t n = 0, Add add = Add(), Del del = Del())
        : add(add), del(del), made(), width(sqrt(n)), nl(), nr() {}

    size_t size() const { return lft.size(); }

    void set(size_t l, size_t r)
    {
        assert(!made);
        lft.emplace_back(l), rgt.emplace_back(r);
    }

    size_t process()
    {
        if(!made) make();
        if(itr == ord.end()) return ord.size();
        const size_t id = *itr++, l = lft[id], r = rgt[id];
        while(nl > l) add(--nl);
        while(nr < r) add(nr++);
        while(nl < l) del(nl++);
        while(nr > r) del(--nr);
        return id;
    }
};
#line 1 "utils/coordinate_compression.hpp"
#include <algorithm>
#line 4 "utils/coordinate_compression.hpp"

template <class T>
class coordinate_compression
{
    std::vector<T> uniquely;
    std::vector<size_t> compressed;

public:
    coordinate_compression(const std::vector<T> &raw) : uniquely(raw), compressed(raw.size())
    {
        std::sort(uniquely.begin(), uniquely.end());
        uniquely.erase(std::unique(uniquely.begin(), uniquely.end()), uniquely.end());
        for(size_t i = 0; i != size(); ++i)
            compressed[i] = std::lower_bound(uniquely.begin(), uniquely.end(), raw[i]) - uniquely.begin();
    }

    size_t operator[](const size_t idx) const
    {
        assert(idx < size());
        return compressed[idx];
    }

    size_t size() const { return compressed.size(); }

    size_t count() const { return uniquely.size(); }

    T value_of(const size_t ord) const
    {
        assert(ord < count());
        return uniquely[ord];
    }

    size_t order_of(const T &val) const { return std::lower_bound(uniquely.begin(), uniquely.end(), val) - uniquely.begin(); }

    std::vector<size_t>::iterator begin() { return compressed.begin(); }
    std::vector<size_t>::iterator end() { return compressed.end(); }
    std::vector<size_t>::reverse_iterator rbegin() { return compressed.rbegin(); }
    std::vector<size_t>::reverse_iterator rend() { return compressed.rend(); }
};
#line 3 "data_structure/segment_tree/segment_tree.hpp"

template <class monoid>
class segment_tree
{
    using size_type = typename std::vector<monoid>::size_type;
    using container_type = std::vector<monoid>;

    class unique_queue
    {
        size_type *que, *begin, *end;
        bool *in;

    public:
        unique_queue() : que(), begin(), end(), in() {}
        unique_queue(size_type n) : que(new size_type[n]), begin(que), end(que), in(new bool[n]{}) {}
        ~unique_queue() { delete[] que; delete[] in; }

        void clear() { begin = end = que; }
        bool empty() const { return begin == end; }
        bool push(size_type index)
        {
            if(in[index]) return false;
            return in[*end++ = index] = true;
        }
        size_type pop() { return in[*begin] = false, *begin++; }
    }; // struct unique_queue

    size_type size_orig, height, size_ext;
    container_type data;
    unique_queue que;

    void recalc(const size_type node) { data[node] = data[node << 1] + data[node << 1 | 1]; }

    void rebuild()
    {
        while(!que.empty())
        {
            const size_type index = que.pop() >> 1;
            if(index && que.push(index)) recalc(index);
        }
        que.clear();
    }

    template <class pred_type>
    size_type left_search_subtree(size_type index, const pred_type pred, monoid mono) const
    {
        assert(index);
        while(index < size_ext)
        {
            const monoid tmp = data[(index <<= 1) | 1] + mono;
            if(pred(tmp)) mono = tmp;
            else ++index;
        }
        return ++index -= size_ext;
    }

    template <class pred_type>
    size_type right_search_subtree(size_type index, const pred_type pred, monoid mono) const
    {
        assert(index);
        while(index < size_ext)
        {
            const monoid tmp = mono + data[index <<= 1];
            if(pred(tmp)) ++index, mono = tmp;
        }
        return (index -= size_ext) < size_orig ? index : size_orig;
    }

public:
    segment_tree(const size_type n = 0) : size_orig{n}, height(n > 1 ? 32 - __builtin_clz(n - 1) : 0), size_ext{1u << height}, data(size_ext << 1), que(size_ext << 1) {}

    segment_tree(const size_type n, const monoid &init) : segment_tree(n)
    {
        std::fill(std::next(std::begin(data), size_ext), std::end(data), init);
        for(size_type i{size_ext}; --i; ) recalc(i);
    }

    template <class iter_type, class value_type = typename std::iterator_traits<iter_type>::value_type>
    segment_tree(iter_type first, iter_type last)
        : size_orig(std::distance(first, last)), height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0), size_ext{1u << height}, data(size_ext << 1), que(size_ext << 1)
    {
        static_assert(std::is_constructible<monoid, value_type>::value, "monoid(iter_type::value_type) is not constructible.");
        for(auto iter{std::next(std::begin(data), size_ext)}; iter != std::end(data) && first != last; ++iter, ++first) *iter = monoid{*first};
        for(size_type i{size_ext}; --i; ) recalc(i);
    }

    template <class container_type, typename = typename container_type::value_type>
    segment_tree(const container_type &cont) : segment_tree(std::begin(cont), std::end(cont)) {}

    size_type size() const { return size_orig; }
    size_type capacity() const { return size_ext; }

    // reference to the element at the index.
    monoid &operator[](size_type index)
    {
        assert(index < size_orig);
        que.push(index |= size_ext);
        return data[index];
    }

    // const reference to the element at the index.
    const monoid &operator[](size_type index) const
    {
        assert(index < size_orig);
        return data[index |= size_orig];
    }

    monoid fold(size_type first, size_type last)
    {
        assert(last <= size_orig);
        rebuild();
        monoid leftval{}, rightval{};
        first += size_ext, last += size_ext;
        while(first < last)
        {
            if(first & 1) leftval = leftval + data[first++];
            if(last & 1) rightval = data[--last] + rightval;
            first >>= 1, last >>= 1;
        }
        return leftval + rightval;
    }

    monoid fold() { return fold(0, size_orig); }

    template <class pred_type>
    size_type left_search(size_type right, const pred_type pred)
    {
        assert(right <= size_orig);
        rebuild();
        right += size_ext;
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
        rebuild();
        left += size_ext;
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
}; // class segment_tree
#line 5 "test/library-checker/static_range_inversions_query.test.cpp"
#include <cstdio>
using i64=int64_t;

int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    std::vector<int> a(n);
    for(int &x: a) scanf("%d",&x);
    coordinate_compression ccmp(a);
    std::vector<int> cnt(ccmp.count());
    segment_tree<int> seg(n);
    int nl=0,nr=0;
    i64 invs=0;
    auto add=[&](int i)
    {
        int nv=ccmp[i];
        if(i<nl) // left end
        {
            invs+=seg.fold(0,nv);
            nl--;
        }
        else // right end
        {
            invs+=seg.fold(nv+1,n);
            nr++;
        }
        seg[nv]++;
    };
    auto del=[&](int i)
    {
        int nv=ccmp[i];
        if(i==nl) // left end
        {
            invs-=seg.fold(0,nv);
            nl++;
        }
        else // right end
        {
            assert(nr==i+1);
            invs-=seg.fold(nv+1,n);
            nr--;
        }
        seg[nv]--;
    };
    Mo mo(n,add,del);
    for(int i=0; i<q; i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        mo.set(l,r);
    }
    std::vector<i64> ans(q);
    for(int i=0; i<q; i++)
    {
        int id=mo.process();
        ans[id]=invs;
    }
    for(i64 x: ans) printf("%lld\n",x);
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

