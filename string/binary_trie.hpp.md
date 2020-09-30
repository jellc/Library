---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/dwacon5th-final/submissions/7200502
  bundledCode: "#line 1 \"string/binary_trie.hpp\"\n// verified at https://atcoder.jp/contests/dwacon5th-final/submissions/7200502\n\
    #ifdef Binary_trie_hpp\n#define Binary_trie_hpp\n#include <cassert>\n#include\
    \ <iterator>\n\ntemplate <size_t depth, class int_type = int_least64_t>\nclass\
    \ binary_trie\n{\n    struct node\n    {\n        bool tag;\n        node *par,\
    \ *lft, *rgt;\n        size_t digit;\n        size_t cnt, typ;\n        node()\
    \ : tag(), par(), lft(), rgt(), digit(depth), cnt(), typ() {}\n        node(bool\
    \ _tag, node *p) : tag(_tag), par(p), lft(), rgt(), digit((int)p->digit - 1),\
    \ cnt(), typ() {}\n    /*/\n        ~node() { delete lft, delete rgt; }\n    \
    \    friend node *alloc(bool _tag, node *p)\n        {\n            return new\
    \ node(_tag, p);\n        }\n    /*/\n        friend node *alloc(bool _tag, node\
    \ *p)\n        {\n            constexpr size_t nodemax = 1.5e6;\n            static\
    \ node stock[nodemax];\n            static size_t node_cnt = 0;\n            return\
    \ &(stock[node_cnt++] = node(_tag, p));\n        }\n    //*/\n        friend bool\
    \ valid(node *p) { return p and p->cnt; }\n    } *const root;\n\n    // node *root;\n\
    \    static_assert(depth != 0, \"depth must be a positive integer.\");\n    int_type\
    \ power[depth];\n    bool bit(int_type x, size_t i) const { return x & power[i];\
    \ }\n\npublic:\n    binary_trie() : root(new node) { power[depth - 1] = 1; for(size_t\
    \ i = depth - 1; i--; ) power[i] = power[i + 1] << 1; }\n    ~binary_trie() {\
    \ delete root; }\n\n    size_t size() const { return root->cnt; }\n    size_t\
    \ type() const { return root->typ; }\n\n    bool insert(int_type x)\n    {\n \
    \       node *p = root;\n        for(size_t i = 0; i < depth; ++i)\n        {\n\
    \            p->cnt++;\n            if(bit(x, i))\n            {\n           \
    \     if(not p->rgt) p->rgt = alloc(1, p);\n                p = p->rgt;\n    \
    \        }\n            else\n            {\n                if(not p->lft) p->lft\
    \ = alloc(0, p);\n                p = p->lft;\n            }\n        }\n    \
    \    if(p->cnt++) return false;\n        while(p)\n        {\n            p->typ++;\n\
    \            p = p->par;\n        }\n        return true;\n    }\n\n    size_t\
    \ erase(int_type x, size_t k = 1)\n    {\n        node *p = root;\n        for(size_t\
    \ i = 0; i < depth; ++i)\n        {\n            if(bit(x, i))\n            {\n\
    \                if(not p->rgt) return 0;\n                p = p->rgt;\n     \
    \       }\n            else\n            {\n                if(not p->lft) return\
    \ 0;\n                p = p->lft;\n            }\n        }\n        bool uni_typ\
    \ = k >= p->cnt;\n        if(uni_typ) k = p->cnt;\n        while(p)\n        {\n\
    \            p->cnt -= k;\n            p->typ -= uni_typ;\n            p = p->par;\n\
    \        }\n        return k;\n    }\n\n    size_t count(int_type x) const\n \
    \   {\n        node *p = root;\n        for(size_t i = 0; i < depth; ++i)\n  \
    \      {\n            if(bit(x, i))\n            {\n                if(not p->rgt)\
    \ return 0;\n                p = p->rgt;\n            }\n            else\n  \
    \          {\n                if(not p->lft) return 0;\n                p = p->lft;\n\
    \            }\n        }\n        return p->cnt;\n    }\n\n    int_type closest(int_type\
    \ x) const\n    {\n        assert(size());\n        node *p = root;\n        int_type\
    \ ret = 0;\n        for(size_t i = 0; i != depth; ++i)\n        {\n          \
    \  if(bit(x, i))\n            {\n                if(valid(p->rgt))\n         \
    \       {\n                    p = p->rgt;\n                    ret += power[i];\n\
    \                }\n                else\n                {\n                \
    \    p = p->lft;\n                }\n            }\n            else\n       \
    \     {\n                if(p->lft && p->lft->cnt)\n                {\n      \
    \              p = p->lft;\n                }\n                else\n        \
    \        {\n                    p = p->rgt;\n                    ret += power[i];\n\
    \                }\n            }\n        }\n        return ret;\n    }\n\n \
    \   int_type operator[](size_t idx) const\n    {\n        assert(idx < size());\n\
    \        node *p = root;\n        int_type ret = 0;\n        for(size_t i = 0;\
    \ i < depth; ++i)\n        {\n            size_t thr = p->lft ? p->lft->cnt :\
    \ 0;\n            if(idx < thr)\n            {\n                p = p->lft;\n\
    \            }\n            else\n            {\n                idx -= thr;\n\
    \                p = p->rgt;\n                ret += power[i];\n            }\n\
    \        }\n        return ret;\n    }\n\n    struct iterator_type : std::iterator<std::bidirectional_iterator_tag,\
    \ int_type, std::ptrdiff_t, node *, int_type>\n    {\n        binary_trie *const\
    \ trie_ptr;\n        node *node_ptr;\n        int_type s;\n        size_t type_idx,\
    \ size_idx;\n\n        iterator_type()\n            : trie_ptr(), node_ptr(),\
    \ s(), type_idx(-1), size_idx(-1)\n        {}\n\n        iterator_type(const iterator_type\
    \ &itr)\n            : trie_ptr(itr.trie_ptr), node_ptr(itr.node_ptr), s(itr.s),\n\
    \            type_idx(itr.type_idx), size_idx(itr.size_idx)\n        {}\n\n  \
    \      iterator_type(binary_trie *_trie_ptr, size_t _type_idx)\n            :\
    \ trie_ptr(_trie_ptr), node_ptr(), s(), type_idx(_type_idx),\n            size_idx()\n\
    \        {\n            if(_type_idx < trie_ptr->type())\n            {\n    \
    \            node *&p = (node_ptr = trie_ptr->root);\n                for(size_t\
    \ i = 0; i < depth; ++i)\n                {\n                    if(valid(p->lft))\n\
    \                    {\n                        if(_type_idx < p->lft->typ)\n\
    \                        {\n                            p = p->lft;\n        \
    \                }\n                        else\n                        {\n\
    \                            _type_idx -= p->lft->typ;\n                     \
    \       size_idx += p->lft->cnt;\n                            p = p->rgt;\n  \
    \                          s += trie_ptr->power[i];\n                        }\n\
    \                    }\n                    else\n                    {\n    \
    \                    p = p->rgt;\n                        s += trie_ptr->power[i];\n\
    \                    }\n                }\n            }\n            else\n \
    \           {\n                size_idx = trie_ptr->size();\n            }\n \
    \       }\n\n        iterator_type(binary_trie *_trie_ptr, node *_node_ptr, int_type\
    \ _s,\n                            size_t _type_idx, size_t _size_idx)\n     \
    \       : trie_ptr(_trie_ptr), node_ptr(_node_ptr), s(_s),\n            type_idx(_type_idx),\
    \ size_idx(_size_idx)\n        {}\n\n        node *operator->() const { return\
    \ node_ptr; }\n\n        int_type operator*() const { return s; }\n\n        bool\
    \ operator==(const iterator_type &itr) const\n        {\n            return trie_ptr\
    \ == itr.trie_ptr and type_idx == itr.type_idx;\n        }\n\n        bool operator!=(const\
    \ iterator_type &itr) const { return not(*this == itr); }\n\n        iterator_type\
    \ &operator++()\n        {\n            size_idx += count();\n            node\
    \ *p = node_ptr;\n            size_t i = depth;\n            while(i--)\n    \
    \        {\n                bool t = p->tag;\n                p = p->par;\n  \
    \              if(t)\n                {\n                    s -= trie_ptr->power[i];\n\
    \                }\n                else if(valid(p->rgt))\n                {\n\
    \                    s += trie_ptr->power[i];\n                    p = p->rgt;\n\
    \                    break;\n                }\n            }\n            if(p->digit\
    \ == depth)\n            {\n                node_ptr = nullptr;\n            }\n\
    \            else\n            {\n                while(++i < depth)\n       \
    \         {\n                    if(valid(p->lft))\n                    {\n  \
    \                      p = p->lft;\n                    }\n                  \
    \  else\n                    {\n                        p = p->rgt;\n        \
    \                s += trie_ptr->power[i];\n                    }\n           \
    \     }\n                node_ptr = p;\n            }\n            ++type_idx;\n\
    \            return *this;\n        }\n\n        iterator_type &operator++(int)\n\
    \        {\n            iterator_type ret = *this;\n            return ++(*this),\
    \ ret;\n        }\n\n        iterator_type &operator--()\n        {\n        \
    \    if(*this == trie_ptr->end())\n            {\n                node *p = trie_ptr->root;\n\
    \                if(valid(p))\n                {\n                    for(size_t\
    \ i = 0; i < depth; ++i)\n                    {\n                        if(valid(p->rgt))\n\
    \                        {\n                            p = p->rgt;\n        \
    \                    s += trie_ptr->power[i];\n                        }\n   \
    \                     else\n                        {\n                      \
    \      p = p->lft;\n                        }\n                    }\n       \
    \             node_ptr = p;\n                }\n            }\n            else\n\
    \            {\n                node *p = node_ptr;\n                size_t i\
    \ = depth;\n                while(i--)\n                {\n                  \
    \  bool t = p->tag;\n                    p = p->par;\n                    if(t)\n\
    \                    {\n                        s -= trie_ptr->power[i];\n   \
    \                     if(valid(p->lft))\n                        {\n         \
    \                   p = p->lft;\n                            break;\n        \
    \                }\n                    }\n                }\n\n             \
    \   if(p->digit == depth)\n                {\n                    node_ptr = nullptr;\n\
    \                }\n                else\n                {\n                \
    \    while(++i < depth)\n                    {\n                        if(valid(p->rgt))\n\
    \                        {\n                            p = p->rgt;\n        \
    \                    s += trie_ptr->power[i];\n                        }\n   \
    \                     else\n                        {\n                      \
    \      p = p->lft;\n                        }\n                    }\n       \
    \             node_ptr = p;\n                }\n            }\n            --type_idx;\n\
    \            if(node_ptr)\n                size_idx -= node_ptr->cnt;\n      \
    \      else\n                size_idx = -1;\n            return *this;\n     \
    \   }\n\n        iterator_type &operator--(int)\n        {\n            iterator_type\
    \ ret = *this;\n            return --(*this), ret;\n        }\n\n        size_t\
    \ count() const\n        {\n            return node_ptr ? node_ptr->cnt : 0;\n\
    \        }\n    }; // struct iterator_type\n\n    friend iterator_type;\n\n  \
    \  iterator_type begin() { return iterator_type(this, 0); }\n    iterator_type\
    \ end() { return iterator_type(this, type()); }\n    std::reverse_iterator<iterator_type>\
    \ rbegin() { return std::reverse_iterator<iterator_type>(end()); }\n    std::reverse_iterator<iterator_type>\
    \ rend() { return std::reverse_iterator<iterator_type>(begin()); }\n\n    iterator_type\
    \ lower_bound(int_type key)\n    {\n        size_t size_idx = 0, type_idx = 0,\
    \ i = 0;\n        node *p = root;\n        int_type s = 0;\n        bool go_back\
    \ = false;\n        for(; i < depth; ++i)\n        {\n            if(bit(key,\
    \ i))\n            {\n                if(valid(p->lft))\n                {\n \
    \                   size_idx += p->lft->cnt;\n                    type_idx +=\
    \ p->lft->typ;\n                }\n                if(valid(p->rgt))\n       \
    \         {\n                    p = p->rgt;\n                    s += power[i];\n\
    \                }\n                else\n                {\n                \
    \    go_back = true;\n                    break;\n                }\n        \
    \    }\n            else\n            {\n                if(valid(p->lft))\n \
    \               {\n                    p = p->lft;\n                }\n      \
    \          else\n                {\n                    if(valid(p->rgt))\n  \
    \                  {\n                        s += power[i];\n               \
    \         p = p->rgt;\n                        break;\n                    }\n\
    \                    else\n                    {\n                        go_back\
    \ = true;\n                        break;\n                    }\n           \
    \     }\n            }\n        }\n        if(go_back)\n        {\n          \
    \  while(i--)\n            {\n                bool t = p->tag;\n             \
    \   p = p->par;\n                if(t)\n                {\n                  \
    \  s -= power[i];\n                }\n                else if(valid(p->rgt))\n\
    \                {\n                    s += power[i];\n                    p\
    \ = p->rgt;\n                    break;\n                }\n            }\n  \
    \          if(p->digit == depth) return end();\n        }\n        while(++i <\
    \ depth)\n        {\n            if(valid(p->lft))\n            {\n          \
    \      p = p->lft;\n            }\n            else\n            {\n         \
    \       p = p->rgt;\n                s += power[i];\n            }\n        }\n\
    \        return iterator_type(this, p, s, type_idx, size_idx);\n    }\n\n    iterator_type\
    \ upper_bound(int_type key)\n    {\n        auto itr = lower_bound(key);\n   \
    \     if(*itr == key) ++itr;\n        return itr;\n    }\n}; // class binary_trie\n\
    \n#endif // Binary_trie_hpp\n"
  code: "// verified at https://atcoder.jp/contests/dwacon5th-final/submissions/7200502\n\
    #ifdef Binary_trie_hpp\n#define Binary_trie_hpp\n#include <cassert>\n#include\
    \ <iterator>\n\ntemplate <size_t depth, class int_type = int_least64_t>\nclass\
    \ binary_trie\n{\n    struct node\n    {\n        bool tag;\n        node *par,\
    \ *lft, *rgt;\n        size_t digit;\n        size_t cnt, typ;\n        node()\
    \ : tag(), par(), lft(), rgt(), digit(depth), cnt(), typ() {}\n        node(bool\
    \ _tag, node *p) : tag(_tag), par(p), lft(), rgt(), digit((int)p->digit - 1),\
    \ cnt(), typ() {}\n    /*/\n        ~node() { delete lft, delete rgt; }\n    \
    \    friend node *alloc(bool _tag, node *p)\n        {\n            return new\
    \ node(_tag, p);\n        }\n    /*/\n        friend node *alloc(bool _tag, node\
    \ *p)\n        {\n            constexpr size_t nodemax = 1.5e6;\n            static\
    \ node stock[nodemax];\n            static size_t node_cnt = 0;\n            return\
    \ &(stock[node_cnt++] = node(_tag, p));\n        }\n    //*/\n        friend bool\
    \ valid(node *p) { return p and p->cnt; }\n    } *const root;\n\n    // node *root;\n\
    \    static_assert(depth != 0, \"depth must be a positive integer.\");\n    int_type\
    \ power[depth];\n    bool bit(int_type x, size_t i) const { return x & power[i];\
    \ }\n\npublic:\n    binary_trie() : root(new node) { power[depth - 1] = 1; for(size_t\
    \ i = depth - 1; i--; ) power[i] = power[i + 1] << 1; }\n    ~binary_trie() {\
    \ delete root; }\n\n    size_t size() const { return root->cnt; }\n    size_t\
    \ type() const { return root->typ; }\n\n    bool insert(int_type x)\n    {\n \
    \       node *p = root;\n        for(size_t i = 0; i < depth; ++i)\n        {\n\
    \            p->cnt++;\n            if(bit(x, i))\n            {\n           \
    \     if(not p->rgt) p->rgt = alloc(1, p);\n                p = p->rgt;\n    \
    \        }\n            else\n            {\n                if(not p->lft) p->lft\
    \ = alloc(0, p);\n                p = p->lft;\n            }\n        }\n    \
    \    if(p->cnt++) return false;\n        while(p)\n        {\n            p->typ++;\n\
    \            p = p->par;\n        }\n        return true;\n    }\n\n    size_t\
    \ erase(int_type x, size_t k = 1)\n    {\n        node *p = root;\n        for(size_t\
    \ i = 0; i < depth; ++i)\n        {\n            if(bit(x, i))\n            {\n\
    \                if(not p->rgt) return 0;\n                p = p->rgt;\n     \
    \       }\n            else\n            {\n                if(not p->lft) return\
    \ 0;\n                p = p->lft;\n            }\n        }\n        bool uni_typ\
    \ = k >= p->cnt;\n        if(uni_typ) k = p->cnt;\n        while(p)\n        {\n\
    \            p->cnt -= k;\n            p->typ -= uni_typ;\n            p = p->par;\n\
    \        }\n        return k;\n    }\n\n    size_t count(int_type x) const\n \
    \   {\n        node *p = root;\n        for(size_t i = 0; i < depth; ++i)\n  \
    \      {\n            if(bit(x, i))\n            {\n                if(not p->rgt)\
    \ return 0;\n                p = p->rgt;\n            }\n            else\n  \
    \          {\n                if(not p->lft) return 0;\n                p = p->lft;\n\
    \            }\n        }\n        return p->cnt;\n    }\n\n    int_type closest(int_type\
    \ x) const\n    {\n        assert(size());\n        node *p = root;\n        int_type\
    \ ret = 0;\n        for(size_t i = 0; i != depth; ++i)\n        {\n          \
    \  if(bit(x, i))\n            {\n                if(valid(p->rgt))\n         \
    \       {\n                    p = p->rgt;\n                    ret += power[i];\n\
    \                }\n                else\n                {\n                \
    \    p = p->lft;\n                }\n            }\n            else\n       \
    \     {\n                if(p->lft && p->lft->cnt)\n                {\n      \
    \              p = p->lft;\n                }\n                else\n        \
    \        {\n                    p = p->rgt;\n                    ret += power[i];\n\
    \                }\n            }\n        }\n        return ret;\n    }\n\n \
    \   int_type operator[](size_t idx) const\n    {\n        assert(idx < size());\n\
    \        node *p = root;\n        int_type ret = 0;\n        for(size_t i = 0;\
    \ i < depth; ++i)\n        {\n            size_t thr = p->lft ? p->lft->cnt :\
    \ 0;\n            if(idx < thr)\n            {\n                p = p->lft;\n\
    \            }\n            else\n            {\n                idx -= thr;\n\
    \                p = p->rgt;\n                ret += power[i];\n            }\n\
    \        }\n        return ret;\n    }\n\n    struct iterator_type : std::iterator<std::bidirectional_iterator_tag,\
    \ int_type, std::ptrdiff_t, node *, int_type>\n    {\n        binary_trie *const\
    \ trie_ptr;\n        node *node_ptr;\n        int_type s;\n        size_t type_idx,\
    \ size_idx;\n\n        iterator_type()\n            : trie_ptr(), node_ptr(),\
    \ s(), type_idx(-1), size_idx(-1)\n        {}\n\n        iterator_type(const iterator_type\
    \ &itr)\n            : trie_ptr(itr.trie_ptr), node_ptr(itr.node_ptr), s(itr.s),\n\
    \            type_idx(itr.type_idx), size_idx(itr.size_idx)\n        {}\n\n  \
    \      iterator_type(binary_trie *_trie_ptr, size_t _type_idx)\n            :\
    \ trie_ptr(_trie_ptr), node_ptr(), s(), type_idx(_type_idx),\n            size_idx()\n\
    \        {\n            if(_type_idx < trie_ptr->type())\n            {\n    \
    \            node *&p = (node_ptr = trie_ptr->root);\n                for(size_t\
    \ i = 0; i < depth; ++i)\n                {\n                    if(valid(p->lft))\n\
    \                    {\n                        if(_type_idx < p->lft->typ)\n\
    \                        {\n                            p = p->lft;\n        \
    \                }\n                        else\n                        {\n\
    \                            _type_idx -= p->lft->typ;\n                     \
    \       size_idx += p->lft->cnt;\n                            p = p->rgt;\n  \
    \                          s += trie_ptr->power[i];\n                        }\n\
    \                    }\n                    else\n                    {\n    \
    \                    p = p->rgt;\n                        s += trie_ptr->power[i];\n\
    \                    }\n                }\n            }\n            else\n \
    \           {\n                size_idx = trie_ptr->size();\n            }\n \
    \       }\n\n        iterator_type(binary_trie *_trie_ptr, node *_node_ptr, int_type\
    \ _s,\n                            size_t _type_idx, size_t _size_idx)\n     \
    \       : trie_ptr(_trie_ptr), node_ptr(_node_ptr), s(_s),\n            type_idx(_type_idx),\
    \ size_idx(_size_idx)\n        {}\n\n        node *operator->() const { return\
    \ node_ptr; }\n\n        int_type operator*() const { return s; }\n\n        bool\
    \ operator==(const iterator_type &itr) const\n        {\n            return trie_ptr\
    \ == itr.trie_ptr and type_idx == itr.type_idx;\n        }\n\n        bool operator!=(const\
    \ iterator_type &itr) const { return not(*this == itr); }\n\n        iterator_type\
    \ &operator++()\n        {\n            size_idx += count();\n            node\
    \ *p = node_ptr;\n            size_t i = depth;\n            while(i--)\n    \
    \        {\n                bool t = p->tag;\n                p = p->par;\n  \
    \              if(t)\n                {\n                    s -= trie_ptr->power[i];\n\
    \                }\n                else if(valid(p->rgt))\n                {\n\
    \                    s += trie_ptr->power[i];\n                    p = p->rgt;\n\
    \                    break;\n                }\n            }\n            if(p->digit\
    \ == depth)\n            {\n                node_ptr = nullptr;\n            }\n\
    \            else\n            {\n                while(++i < depth)\n       \
    \         {\n                    if(valid(p->lft))\n                    {\n  \
    \                      p = p->lft;\n                    }\n                  \
    \  else\n                    {\n                        p = p->rgt;\n        \
    \                s += trie_ptr->power[i];\n                    }\n           \
    \     }\n                node_ptr = p;\n            }\n            ++type_idx;\n\
    \            return *this;\n        }\n\n        iterator_type &operator++(int)\n\
    \        {\n            iterator_type ret = *this;\n            return ++(*this),\
    \ ret;\n        }\n\n        iterator_type &operator--()\n        {\n        \
    \    if(*this == trie_ptr->end())\n            {\n                node *p = trie_ptr->root;\n\
    \                if(valid(p))\n                {\n                    for(size_t\
    \ i = 0; i < depth; ++i)\n                    {\n                        if(valid(p->rgt))\n\
    \                        {\n                            p = p->rgt;\n        \
    \                    s += trie_ptr->power[i];\n                        }\n   \
    \                     else\n                        {\n                      \
    \      p = p->lft;\n                        }\n                    }\n       \
    \             node_ptr = p;\n                }\n            }\n            else\n\
    \            {\n                node *p = node_ptr;\n                size_t i\
    \ = depth;\n                while(i--)\n                {\n                  \
    \  bool t = p->tag;\n                    p = p->par;\n                    if(t)\n\
    \                    {\n                        s -= trie_ptr->power[i];\n   \
    \                     if(valid(p->lft))\n                        {\n         \
    \                   p = p->lft;\n                            break;\n        \
    \                }\n                    }\n                }\n\n             \
    \   if(p->digit == depth)\n                {\n                    node_ptr = nullptr;\n\
    \                }\n                else\n                {\n                \
    \    while(++i < depth)\n                    {\n                        if(valid(p->rgt))\n\
    \                        {\n                            p = p->rgt;\n        \
    \                    s += trie_ptr->power[i];\n                        }\n   \
    \                     else\n                        {\n                      \
    \      p = p->lft;\n                        }\n                    }\n       \
    \             node_ptr = p;\n                }\n            }\n            --type_idx;\n\
    \            if(node_ptr)\n                size_idx -= node_ptr->cnt;\n      \
    \      else\n                size_idx = -1;\n            return *this;\n     \
    \   }\n\n        iterator_type &operator--(int)\n        {\n            iterator_type\
    \ ret = *this;\n            return --(*this), ret;\n        }\n\n        size_t\
    \ count() const\n        {\n            return node_ptr ? node_ptr->cnt : 0;\n\
    \        }\n    }; // struct iterator_type\n\n    friend iterator_type;\n\n  \
    \  iterator_type begin() { return iterator_type(this, 0); }\n    iterator_type\
    \ end() { return iterator_type(this, type()); }\n    std::reverse_iterator<iterator_type>\
    \ rbegin() { return std::reverse_iterator<iterator_type>(end()); }\n    std::reverse_iterator<iterator_type>\
    \ rend() { return std::reverse_iterator<iterator_type>(begin()); }\n\n    iterator_type\
    \ lower_bound(int_type key)\n    {\n        size_t size_idx = 0, type_idx = 0,\
    \ i = 0;\n        node *p = root;\n        int_type s = 0;\n        bool go_back\
    \ = false;\n        for(; i < depth; ++i)\n        {\n            if(bit(key,\
    \ i))\n            {\n                if(valid(p->lft))\n                {\n \
    \                   size_idx += p->lft->cnt;\n                    type_idx +=\
    \ p->lft->typ;\n                }\n                if(valid(p->rgt))\n       \
    \         {\n                    p = p->rgt;\n                    s += power[i];\n\
    \                }\n                else\n                {\n                \
    \    go_back = true;\n                    break;\n                }\n        \
    \    }\n            else\n            {\n                if(valid(p->lft))\n \
    \               {\n                    p = p->lft;\n                }\n      \
    \          else\n                {\n                    if(valid(p->rgt))\n  \
    \                  {\n                        s += power[i];\n               \
    \         p = p->rgt;\n                        break;\n                    }\n\
    \                    else\n                    {\n                        go_back\
    \ = true;\n                        break;\n                    }\n           \
    \     }\n            }\n        }\n        if(go_back)\n        {\n          \
    \  while(i--)\n            {\n                bool t = p->tag;\n             \
    \   p = p->par;\n                if(t)\n                {\n                  \
    \  s -= power[i];\n                }\n                else if(valid(p->rgt))\n\
    \                {\n                    s += power[i];\n                    p\
    \ = p->rgt;\n                    break;\n                }\n            }\n  \
    \          if(p->digit == depth) return end();\n        }\n        while(++i <\
    \ depth)\n        {\n            if(valid(p->lft))\n            {\n          \
    \      p = p->lft;\n            }\n            else\n            {\n         \
    \       p = p->rgt;\n                s += power[i];\n            }\n        }\n\
    \        return iterator_type(this, p, s, type_idx, size_idx);\n    }\n\n    iterator_type\
    \ upper_bound(int_type key)\n    {\n        auto itr = lower_bound(key);\n   \
    \     if(*itr == key) ++itr;\n        return itr;\n    }\n}; // class binary_trie\n\
    \n#endif // Binary_trie_hpp\n"
  dependsOn: []
  isVerificationFile: false
  path: string/binary_trie.hpp
  requiredBy: []
  timestamp: '2020-02-10 08:59:19+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: string/binary_trie.hpp
layout: document
redirect_from:
- /library/string/binary_trie.hpp
- /library/string/binary_trie.hpp.html
title: string/binary_trie.hpp
---
