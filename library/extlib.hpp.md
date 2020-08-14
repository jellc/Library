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
<script type="text/javascript" src="../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../assets/css/copy-button.css" />


# :warning: extlib.hpp

<a href="../index.html">Back to top page</a>

* category: <a href="../index.html#5058f1af8388633f609cadb75a75dc9d">.</a>
* <a href="{{ site.github.repository_url }}/blob/master/extlib.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-14 18:10:27+09:00




## Required by

* :warning: <a href="template.cpp.html">template.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <ext/algorithm>
#include <ext/array_allocator.h>
#include <ext/atomicity.h>
#include <ext/bitmap_allocator.h>
#include <ext/cast.h>
#include <ext/concurrence.h>
#include <ext/debug_allocator.h>
#include <ext/extptr_allocator.h>
#include <ext/functional>
#include <ext/iterator>
#include <ext/malloc_allocator.h>
#include <ext/memory>
#include <ext/mt_allocator.h>
#include <ext/new_allocator.h>
#include <ext/numeric>
#include <ext/pod_char_traits.h>
#include <ext/pointer.h>
#include <ext/pool_allocator.h>
#include <ext/rb_tree>
#include <ext/rope>
#include <ext/slist>
#include <ext/stdio_filebuf.h>
#include <ext/stdio_sync_filebuf.h>
#include <ext/throw_allocator.h>
#include <ext/typelist.h>
#include <ext/type_traits.h>
#include <ext/vstring.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "extlib.hpp"
#include <ext/algorithm>
#include <ext/array_allocator.h>
#include <ext/atomicity.h>
#include <ext/bitmap_allocator.h>
#include <ext/cast.h>
#include <ext/concurrence.h>
#include <ext/debug_allocator.h>
#include <ext/extptr_allocator.h>
#include <ext/functional>
#include <ext/iterator>
#include <ext/malloc_allocator.h>
#include <ext/memory>
#include <ext/mt_allocator.h>
#include <ext/new_allocator.h>
#include <ext/numeric>
#include <ext/pod_char_traits.h>
#include <ext/pointer.h>
#include <ext/pool_allocator.h>
#include <ext/rb_tree>
#include <ext/rope>
#include <ext/slist>
#include <ext/stdio_filebuf.h>
#include <ext/stdio_sync_filebuf.h>
#include <ext/throw_allocator.h>
#include <ext/typelist.h>
#include <ext/type_traits.h>
#include <ext/vstring.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>

```
{% endraw %}

<a href="../index.html">Back to top page</a>

