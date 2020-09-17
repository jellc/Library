---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links:
    - https://codeforces.com/contest/1202/submission/69079919
  bundledCode: "#line 1 \"deprecated/trie.hpp\"\n// verified at https://codeforces.com/contest/1202/submission/69079919\n\
    #ifndef Trie_hpp\n#define Trie_hpp\n#include <map>\n#include <queue>\n\ntemplate\
    \ <class str_type>\nstruct trie\n{\n    struct Aho_Corasick;\n    struct node;\n\
    \    using char_type = typename str_type::value_type;\n    using dict_type = std::map<char_type,\
    \ node*>;\n\n    struct node\n    {\n        const char_type tag;\n        const\
    \ bool is_ter;\n        node *const par, *ter;\n        dict_type child;\n   \
    \     size_t cnt, type;\n\n        node() : tag(), is_ter(), par(), ter(), child(),\
    \ cnt(), type() {}\n\n        node(node *const p) : tag(), is_ter(true), par(p),\
    \ ter(), child(), cnt(), type() {}\n\n        node(const char_type &_tag, node\
    \ *const p) : tag(_tag), is_ter(), par(p), ter(), child(), cnt(), type() {}\n\n\
    \        ~node() { delete ter; for(auto &e : child) delete e.second; }\n\n   \
    \     node *add(const char_type &x)\n        {\n            node *&p = child[x];\n\
    \            return p ? p : p = new node(x, this);\n        }\n\n        node\
    \ *add()\n        {\n            return sfx_wrd++, ter ? ter : ter = new node(this);\n\
    \        }\n\n        friend bool valid(const node *const p)\n        {\n    \
    \        return p and p->cnt and p->type;\n        }\n\n        friend Aho_Corasick;\n\
    \n        node *failure = nullptr;\n\n        size_t sfx_wrd = 0;\n    }; // struct\
    \ node\n\n    node *const root;\n\n    trie() : root(new node) {}\n    ~trie()\
    \ { delete root; }\n\n    size_t size() const { return root->cnt; }\n    size_t\
    \ type() const { return root->type; }\n\n    node *insert(const str_type &s)\n\
    \    {\n        node *p = root;\n        p->cnt++;\n        for(const char_type\
    \ &x : s)\n        {\n            (p = p->add(x))->cnt++;\n        }\n       \
    \ node *ret = p = p->add();\n        if(not p->cnt++)\n        {\n           \
    \ while(p)\n            {\n                p->type++;\n                p = p->par;\n\
    \            }\n        }\n        return ret;\n    }\n\n    size_t erase(const\
    \ str_type &s, size_t k = 1)\n    {\n        node *p = root;\n        for(const\
    \ char_type &x : s)\n        {\n            p = p->child[x];\n            if(not\
    \ p) return 0;\n        }\n        p = p->ter;\n        if(not p) return 0;\n\
    \        bool ext = k >= p->cnt;\n        if(ext)\n        {\n            k =\
    \ p->cnt;\n            p->par->suf_wrd--;\n        }\n        while(p)\n     \
    \   {\n            p->cnt -= k;\n            p->type -= ext;\n            p =\
    \ p->par;\n        }\n        return k;\n    }\n\n    size_t erase(size_t idx)\n\
    \    {\n        if(idx >= size()) return 0;\n        node *p = root;\n       \
    \ while(true)\n        {\n            if(p->ter)\n            {\n            \
    \    size_t here = p->ter->cnt;\n                if(idx < here)\n            \
    \    {\n                    p = p->ter;\n                    break;\n        \
    \        }\n                idx -= here;\n            }\n            node *nx\
    \ = nullptr;\n            for(const auto &e : p->child)\n            {\n     \
    \           char_type x;\n                node *t;\n                tie(x, t)\
    \ = e;\n                size_t here = t ? t->cnt : 0;\n                if(idx\
    \ < here)\n                {\n                    nx = t;\n                  \
    \  break;\n                }\n                else\n                {\n      \
    \              idx -= here;\n                }\n            }\n            p =\
    \ nx;\n        }\n        bool ext = not--p->ter->cnt;\n        while(p)\n   \
    \     {\n            p->cnt--;\n            p->type -= ext;\n            p = p->par;\n\
    \        }\n        return 1;\n    }\n\n    size_t count(const str_type &s) const\n\
    \    {\n        node *p = root;\n        for(const char_type &x : s)\n       \
    \ {\n            p = p->child[x];\n            if(!p->child[x]) return 0;\n  \
    \      }\n        p = p->ter;\n        return p ? p->cnt : 0;\n    }\n\n    /*\n\
    \    size_t lower_bound(const str_type &s) const\n    {\n        size_t ret =\
    \ 0;\n        node *p = root;\n        for(const char_type &x : s)\n        {\n\
    \            if(not p) break;\n            if(p->ter) ret += p->ter->cnt;\n  \
    \          for(const auto &e : p->child)\n            {\n                if(e.first\
    \ == x) break;\n                node *t = e.second;\n                if(t) ret\
    \ += t->cnt;\n            }\n            p = p->child[x];\n        }\n       \
    \ return ret;\n    }\n\n    size_t upper_bound(const str_type &s) const\n    {\n\
    \        size_t ret = 0;\n        node *p = root;\n        for(const char_type\
    \ &x : s)\n        {\n            if(not p) break;\n            if(p->ter) ret\
    \ += p->ter->cnt;\n            for(const auto &e : p->child)\n            {\n\
    \                if(e.first == x) break;\n                node *t = e.second;\n\
    \                if(t) ret += t->cnt;\n            }\n            p = p->child[x];\n\
    \        }\n        if(p and p->ter) ret += p->ter->cnt;\n        return ret;\n\
    \    }\n    //*/\n\n    str_type operator[](size_t idx) const\n    {\n       \
    \ assert(idx < size());\n        node *p = root;\n        str_type ret = str_type();\n\
    \        while(true)\n        {\n            if(p->ter)\n            {\n     \
    \           size_t here = p->ter->cnt;\n                if(idx < here) break;\n\
    \                idx -= here;\n            }\n            node *nx = nullptr;\n\
    \            for(const auto &e : p->child)\n            {\n                char_type\
    \ x;\n                node *t;\n                std::tie(x, t) = e;\n        \
    \        size_t here = t ? t->cnt : 0;\n                if(idx < here)\n     \
    \           {\n                    ret.push_back(x);\n                    nx =\
    \ t;\n                    break;\n                }\n                idx -= here;\n\
    \            }\n            p = nx;\n        }\n        return ret;\n    }\n\n\
    \    struct iterator_type : std::iterator<std::bidirectional_iterator_tag, str_type,\
    \ std::ptrdiff_t, node *, str_type>\n    {\n        trie *const trie_ptr;\n  \
    \      node *node_ptr;\n        str_type s;\n        size_t type_idx, size_idx;\n\
    \n        iterator_type() : trie_ptr(), node_ptr(), s(), type_idx(-1), size_idx(-1)\
    \ {}\n        iterator_type(const iterator_type &itr) : trie_ptr(itr.trie_ptr),\
    \ node_ptr(itr.node_ptr), s(itr.s), type_idx(itr.type_idx), size_idx(itr.size_idx)\
    \ {}\n        iterator_type(trie *_trie_ptr, size_t _type_idx) : trie_ptr(_trie_ptr),\
    \ node_ptr(), s(), type_idx(_type_idx), size_idx()\n        {\n            if(_type_idx\
    \ < trie_ptr->type())\n            {\n                node *&p = (node_ptr = trie_ptr->root);\n\
    \                while(p)\n                {\n                    size_t here_typ\
    \ = p->ter ? p->ter->type : 0;\n                    size_t here_cnt = p->ter ?\
    \ p->ter->cnt : 0;\n                    if(_type_idx < here_typ)\n           \
    \         {\n                        p = p->ter;\n                        break;\n\
    \                    }\n                    _type_idx -= here_typ;\n         \
    \           size_idx += here_cnt;\n                    node *nx = nullptr;\n \
    \                   for(const auto &e : p->child)\n                    {\n   \
    \                     char_type x;\n                        node *t;\n       \
    \                 std::tie(x, t) = e;\n                        here_typ = t ?\
    \ t->type : 0;\n                        here_cnt = t ? t->cnt : 0;\n         \
    \               if(_type_idx < here_typ)\n                        {\n        \
    \                    s.push_back(x);\n                            nx = t;\n  \
    \                          break;\n                        }\n               \
    \         _type_idx -= here_typ;\n                        size_idx += here_cnt;\n\
    \                    }\n                    p = nx;\n                }\n     \
    \       }\n            else\n            {\n                size_idx = trie_ptr->size();\n\
    \            }\n        }\n\n        iterator_type(trie *_trie_ptr, node *_node_ptr,\
    \ const str_type &_s, size_t _type_idx, size_t _size_idx) : trie_ptr(_trie_ptr),\
    \ node_ptr(_node_ptr), s(_s), type_idx(_type_idx), size_idx(_size_idx) {}\n\n\
    \        node *operator->() const { return node_ptr; }\n\n        str_type operator*()\
    \ const { return s; }\n\n        bool operator==(const iterator_type &itr) const\
    \ { return trie_ptr == itr.trie_ptr and type_idx == itr.type_idx; }\n\n      \
    \  bool operator!=(const iterator_type &itr) const { return not(*this == itr);\
    \ }\n\n        iterator_type &operator++()\n        {\n            size_idx +=\
    \ count();\n            node *p = node_ptr;\n            while(p->par)\n     \
    \       {\n                auto dict_itr = p->par->child.begin();\n          \
    \      if(not p->is_ter)\n                {\n                    dict_itr = p->par->child.upper_bound(p->tag);\n\
    \                    s.pop_back();\n                }\n                p = p->par;\n\
    \                while(dict_itr != p->child.end() and not valid(dict_itr->second))\
    \ ++dict_itr;\n                if(dict_itr != p->child.end())\n              \
    \  {\n                    p = dict_itr->second;\n                    s.push_back(p->tag);\n\
    \                    break;\n                }\n            }\n            if(!p->par)\n\
    \            {\n                node_ptr = nullptr;\n            }\n         \
    \   else\n            {\n                while(not valid(p->ter))\n          \
    \      {\n                    node *nx = nullptr;\n                    for(const\
    \ auto &e : p->child)\n                    {\n                        char_type\
    \ x;\n                        node *t;\n                        std::tie(x, t)\
    \ = e;\n                        if(valid(t))\n                        {\n    \
    \                        s.push_back(x);\n                            nx = t;\n\
    \                            break;\n                        }\n             \
    \       }\n                    p = nx;\n                }\n                node_ptr\
    \ = p->ter;\n            }\n            ++type_idx;\n            return *this;\n\
    \        }\n\n        iterator_type operator++(int)\n        {\n            iterator_type\
    \ ret = *this;\n            return ++(*this), ret;\n        }\n\n        iterator_type\
    \ &operator--()\n        {\n            if(*this == trie_ptr->end())\n       \
    \     {\n                node *p = trie_ptr->root;\n                if(p->type)\n\
    \                {\n                    while(not p->is_ter)\n               \
    \     {\n                        auto dict_itr = p->child.rbegin();\n        \
    \                while(dict_itr != p->child.rend() and not valid(dict_itr->second))\
    \ ++dict_itr;\n                        if(dict_itr != p->child.rend())\n     \
    \                   {\n                            p = dict_itr->second;\n   \
    \                         s.push_back(p->tag);\n                        }\n  \
    \                      else\n                        {\n                     \
    \       p = p->ter;\n                        }\n                    }\n      \
    \              node_ptr = p;\n                }\n            }\n            else\n\
    \            {\n                bool is_prefix = false;\n                node\
    \ *p = node_ptr->par;\n                while(p->par)\n                {\n    \
    \                auto map_ritr = p->par->child.rend();\n                    map_ritr\
    \ = std::reverse_iterator<typename dict_type::iterator>(p->par->child.lower_bound(p->tag));\n\
    \                    s.pop_back();\n                    p = p->par;\n        \
    \            while(map_ritr != p->child.rend() and not valid(map_ritr->second))\
    \ ++map_ritr;\n                    if(map_ritr != p->child.rend())\n         \
    \           {\n                        p = map_ritr->second;\n               \
    \         s.push_back(map_ritr->first);\n                        break;\n    \
    \                }\n                    else if(p->ter and p->ter->type)\n   \
    \                 {\n                        is_prefix = true;\n             \
    \           break;\n                    }\n                }\n               \
    \ if(is_prefix)\n                {\n                    node_ptr = p->ter;\n \
    \               }\n                else\n                {\n                 \
    \   if(!p->par)\n                    {\n                        node_ptr = nullptr;\n\
    \                    }\n                    else\n                    {\n    \
    \                    while(not p->is_ter)\n                        {\n       \
    \                     auto map_ritr = p->child.rbegin();\n                   \
    \         while(map_ritr != p->child.rend() and not valid(map_ritr->second)) ++map_ritr;\n\
    \                            if(map_ritr != p->child.rend())\n               \
    \             {\n                                s.push_back(map_ritr->first);\n\
    \                                p = map_ritr->second;\n                     \
    \       }\n                            else\n                            {\n \
    \                               p = p->ter;\n                            }\n \
    \                       }\n                        node_ptr = p;\n           \
    \         }\n                }\n            }\n            --type_idx;\n     \
    \       if(node_ptr) size_idx -= node_ptr->cnt;\n            else size_idx = -1;\n\
    \            return *this;\n        }\n\n        iterator_type operator--(int)\n\
    \        {\n            iterator_type ret = *this;\n            return --(*this),\
    \ ret;\n        }\n\n        size_t count() const\n        {\n            return\
    \ node_ptr ? node_ptr->cnt : 0;\n        }\n    }; // class iterator_type\n  \
    \  friend iterator_type;\n\n    iterator_type begin() { return iterator_type(this,\
    \ 0); }\n    iterator_type end() { return iterator_type(this, type()); }\n   \
    \ std::reverse_iterator<iterator_type> rbegin() { return std::reverse_iterator<iterator_type>(end());\
    \ }\n    std::reverse_iterator<iterator_type> rend() { return std::reverse_iterator<iterator_type>(begin());\
    \ }\n\n    iterator_type lower_bound(const str_type &key)\n    {\n        size_t\
    \ size_idx = 0, type_idx = 0;\n        str_type s;\n        node *p = root;\n\
    \        bool go_back = false;\n        for(const char_type &x : key)\n      \
    \  {\n            if(p->ter)\n            {\n                size_idx += p->ter->cnt;\n\
    \                type_idx += p->ter->type;\n            }\n            node *nx\
    \ = nullptr;\n            for(const auto &e : p->child)\n            {\n     \
    \           char_type y;\n                node *t;\n                std::tie(y,\
    \ t) = e;\n                if(valid(t))\n                {\n                 \
    \   if(y < x)\n                    {\n                        size_idx += t->cnt;\n\
    \                        type_idx += t->type;\n                    }\n       \
    \             else if(t->type)\n                    {\n                      \
    \  s.push_back(y);\n                        nx = t;\n                        break;\n\
    \                    }\n                }\n            }\n            if(not nx)\n\
    \            {\n                go_back = true;\n                break;\n    \
    \        }\n            p = nx;\n            if(p->tag > x) break;\n        }\n\
    \        if(go_back)\n        {\n            while(!p->par)\n            {\n \
    \               p = p->par;\n                auto dict_itr = p->child.upper_bound(s.back());\n\
    \                s.pop_back();\n                while(dict_itr != p->child.end()\
    \ and not valid(dict_itr->second)) ++dict_itr;\n                if(dict_itr !=\
    \ p->child.end())\n                {\n                    p = dict_itr->second;\n\
    \                    s.push_back(dict_itr->first);\n                    break;\n\
    \                }\n            }\n            if(!p->par) return end();\n   \
    \     }\n        while(not p->is_ter)\n        {\n            if(valid(p->ter))\n\
    \            {\n                p = p->ter;\n            }\n            else\n\
    \            {\n                auto dict_itr = p->child.begin();\n          \
    \      while(dict_itr != p->child.end() and not valid(dict_itr->second)) ++dict_itr;\n\
    \                p = dict_itr->second;\n                s.push_back(dict_itr->first);\n\
    \            }\n        }\n        return iterator_type(this, p, s, type_idx,\
    \ size_idx);\n    }\n\n    iterator_type upper_bound(const str_type &key)\n  \
    \  {\n        auto itr = lower_bound(key);\n        if(*itr == key) ++itr;\n \
    \       return itr;\n    }\n\n    struct Aho_Corasick\n    {\n        node *root;\n\
    \n        Aho_Corasick() : root() {}\n        Aho_Corasick(const trie &trie) {\
    \ build(trie); }\n\n        node *build(const trie<str_type> &trie)\n        {\n\
    \            root = trie.root;\n            std::queue<node*> que;\n         \
    \   que.emplace(root);\n            while(!que.empty())\n            {\n     \
    \           node *const now = que.front();\n                que.pop();\n     \
    \           for(const auto &e : now->child)\n                {\n             \
    \       char_type x;\n                    node *t, *p = now;\n               \
    \     std::tie(x, t) = e;\n                    do\n                    {\n   \
    \                     p = p->failure;\n                    } while(p and not p->child[x]);\n\
    \                    t->failure = p ? p->child[x] : root;\n                  \
    \  t->sfx_wrd += t->failure->sfx_wrd;\n                    que.emplace(t);\n \
    \               }\n            }\n            return root;\n        }\n\n    \
    \    node *next(node *now, const char_type &x)\n        {\n            while(now\
    \ and not now->child[x])\n            {\n                now = now->failure;\n\
    \            }\n            return now = now ? now->child[x] : root;\n       \
    \ }\n\n        size_t query(node *now) { return now->sfx_wrd; }\n    }; // struct\
    \ Aho_Corasick\n}; // struct trie\n\n#endif // Trie_hpp\n"
  code: "// verified at https://codeforces.com/contest/1202/submission/69079919\n\
    #ifndef Trie_hpp\n#define Trie_hpp\n#include <map>\n#include <queue>\n\ntemplate\
    \ <class str_type>\nstruct trie\n{\n    struct Aho_Corasick;\n    struct node;\n\
    \    using char_type = typename str_type::value_type;\n    using dict_type = std::map<char_type,\
    \ node*>;\n\n    struct node\n    {\n        const char_type tag;\n        const\
    \ bool is_ter;\n        node *const par, *ter;\n        dict_type child;\n   \
    \     size_t cnt, type;\n\n        node() : tag(), is_ter(), par(), ter(), child(),\
    \ cnt(), type() {}\n\n        node(node *const p) : tag(), is_ter(true), par(p),\
    \ ter(), child(), cnt(), type() {}\n\n        node(const char_type &_tag, node\
    \ *const p) : tag(_tag), is_ter(), par(p), ter(), child(), cnt(), type() {}\n\n\
    \        ~node() { delete ter; for(auto &e : child) delete e.second; }\n\n   \
    \     node *add(const char_type &x)\n        {\n            node *&p = child[x];\n\
    \            return p ? p : p = new node(x, this);\n        }\n\n        node\
    \ *add()\n        {\n            return sfx_wrd++, ter ? ter : ter = new node(this);\n\
    \        }\n\n        friend bool valid(const node *const p)\n        {\n    \
    \        return p and p->cnt and p->type;\n        }\n\n        friend Aho_Corasick;\n\
    \n        node *failure = nullptr;\n\n        size_t sfx_wrd = 0;\n    }; // struct\
    \ node\n\n    node *const root;\n\n    trie() : root(new node) {}\n    ~trie()\
    \ { delete root; }\n\n    size_t size() const { return root->cnt; }\n    size_t\
    \ type() const { return root->type; }\n\n    node *insert(const str_type &s)\n\
    \    {\n        node *p = root;\n        p->cnt++;\n        for(const char_type\
    \ &x : s)\n        {\n            (p = p->add(x))->cnt++;\n        }\n       \
    \ node *ret = p = p->add();\n        if(not p->cnt++)\n        {\n           \
    \ while(p)\n            {\n                p->type++;\n                p = p->par;\n\
    \            }\n        }\n        return ret;\n    }\n\n    size_t erase(const\
    \ str_type &s, size_t k = 1)\n    {\n        node *p = root;\n        for(const\
    \ char_type &x : s)\n        {\n            p = p->child[x];\n            if(not\
    \ p) return 0;\n        }\n        p = p->ter;\n        if(not p) return 0;\n\
    \        bool ext = k >= p->cnt;\n        if(ext)\n        {\n            k =\
    \ p->cnt;\n            p->par->suf_wrd--;\n        }\n        while(p)\n     \
    \   {\n            p->cnt -= k;\n            p->type -= ext;\n            p =\
    \ p->par;\n        }\n        return k;\n    }\n\n    size_t erase(size_t idx)\n\
    \    {\n        if(idx >= size()) return 0;\n        node *p = root;\n       \
    \ while(true)\n        {\n            if(p->ter)\n            {\n            \
    \    size_t here = p->ter->cnt;\n                if(idx < here)\n            \
    \    {\n                    p = p->ter;\n                    break;\n        \
    \        }\n                idx -= here;\n            }\n            node *nx\
    \ = nullptr;\n            for(const auto &e : p->child)\n            {\n     \
    \           char_type x;\n                node *t;\n                tie(x, t)\
    \ = e;\n                size_t here = t ? t->cnt : 0;\n                if(idx\
    \ < here)\n                {\n                    nx = t;\n                  \
    \  break;\n                }\n                else\n                {\n      \
    \              idx -= here;\n                }\n            }\n            p =\
    \ nx;\n        }\n        bool ext = not--p->ter->cnt;\n        while(p)\n   \
    \     {\n            p->cnt--;\n            p->type -= ext;\n            p = p->par;\n\
    \        }\n        return 1;\n    }\n\n    size_t count(const str_type &s) const\n\
    \    {\n        node *p = root;\n        for(const char_type &x : s)\n       \
    \ {\n            p = p->child[x];\n            if(!p->child[x]) return 0;\n  \
    \      }\n        p = p->ter;\n        return p ? p->cnt : 0;\n    }\n\n    /*\n\
    \    size_t lower_bound(const str_type &s) const\n    {\n        size_t ret =\
    \ 0;\n        node *p = root;\n        for(const char_type &x : s)\n        {\n\
    \            if(not p) break;\n            if(p->ter) ret += p->ter->cnt;\n  \
    \          for(const auto &e : p->child)\n            {\n                if(e.first\
    \ == x) break;\n                node *t = e.second;\n                if(t) ret\
    \ += t->cnt;\n            }\n            p = p->child[x];\n        }\n       \
    \ return ret;\n    }\n\n    size_t upper_bound(const str_type &s) const\n    {\n\
    \        size_t ret = 0;\n        node *p = root;\n        for(const char_type\
    \ &x : s)\n        {\n            if(not p) break;\n            if(p->ter) ret\
    \ += p->ter->cnt;\n            for(const auto &e : p->child)\n            {\n\
    \                if(e.first == x) break;\n                node *t = e.second;\n\
    \                if(t) ret += t->cnt;\n            }\n            p = p->child[x];\n\
    \        }\n        if(p and p->ter) ret += p->ter->cnt;\n        return ret;\n\
    \    }\n    //*/\n\n    str_type operator[](size_t idx) const\n    {\n       \
    \ assert(idx < size());\n        node *p = root;\n        str_type ret = str_type();\n\
    \        while(true)\n        {\n            if(p->ter)\n            {\n     \
    \           size_t here = p->ter->cnt;\n                if(idx < here) break;\n\
    \                idx -= here;\n            }\n            node *nx = nullptr;\n\
    \            for(const auto &e : p->child)\n            {\n                char_type\
    \ x;\n                node *t;\n                std::tie(x, t) = e;\n        \
    \        size_t here = t ? t->cnt : 0;\n                if(idx < here)\n     \
    \           {\n                    ret.push_back(x);\n                    nx =\
    \ t;\n                    break;\n                }\n                idx -= here;\n\
    \            }\n            p = nx;\n        }\n        return ret;\n    }\n\n\
    \    struct iterator_type : std::iterator<std::bidirectional_iterator_tag, str_type,\
    \ std::ptrdiff_t, node *, str_type>\n    {\n        trie *const trie_ptr;\n  \
    \      node *node_ptr;\n        str_type s;\n        size_t type_idx, size_idx;\n\
    \n        iterator_type() : trie_ptr(), node_ptr(), s(), type_idx(-1), size_idx(-1)\
    \ {}\n        iterator_type(const iterator_type &itr) : trie_ptr(itr.trie_ptr),\
    \ node_ptr(itr.node_ptr), s(itr.s), type_idx(itr.type_idx), size_idx(itr.size_idx)\
    \ {}\n        iterator_type(trie *_trie_ptr, size_t _type_idx) : trie_ptr(_trie_ptr),\
    \ node_ptr(), s(), type_idx(_type_idx), size_idx()\n        {\n            if(_type_idx\
    \ < trie_ptr->type())\n            {\n                node *&p = (node_ptr = trie_ptr->root);\n\
    \                while(p)\n                {\n                    size_t here_typ\
    \ = p->ter ? p->ter->type : 0;\n                    size_t here_cnt = p->ter ?\
    \ p->ter->cnt : 0;\n                    if(_type_idx < here_typ)\n           \
    \         {\n                        p = p->ter;\n                        break;\n\
    \                    }\n                    _type_idx -= here_typ;\n         \
    \           size_idx += here_cnt;\n                    node *nx = nullptr;\n \
    \                   for(const auto &e : p->child)\n                    {\n   \
    \                     char_type x;\n                        node *t;\n       \
    \                 std::tie(x, t) = e;\n                        here_typ = t ?\
    \ t->type : 0;\n                        here_cnt = t ? t->cnt : 0;\n         \
    \               if(_type_idx < here_typ)\n                        {\n        \
    \                    s.push_back(x);\n                            nx = t;\n  \
    \                          break;\n                        }\n               \
    \         _type_idx -= here_typ;\n                        size_idx += here_cnt;\n\
    \                    }\n                    p = nx;\n                }\n     \
    \       }\n            else\n            {\n                size_idx = trie_ptr->size();\n\
    \            }\n        }\n\n        iterator_type(trie *_trie_ptr, node *_node_ptr,\
    \ const str_type &_s, size_t _type_idx, size_t _size_idx) : trie_ptr(_trie_ptr),\
    \ node_ptr(_node_ptr), s(_s), type_idx(_type_idx), size_idx(_size_idx) {}\n\n\
    \        node *operator->() const { return node_ptr; }\n\n        str_type operator*()\
    \ const { return s; }\n\n        bool operator==(const iterator_type &itr) const\
    \ { return trie_ptr == itr.trie_ptr and type_idx == itr.type_idx; }\n\n      \
    \  bool operator!=(const iterator_type &itr) const { return not(*this == itr);\
    \ }\n\n        iterator_type &operator++()\n        {\n            size_idx +=\
    \ count();\n            node *p = node_ptr;\n            while(p->par)\n     \
    \       {\n                auto dict_itr = p->par->child.begin();\n          \
    \      if(not p->is_ter)\n                {\n                    dict_itr = p->par->child.upper_bound(p->tag);\n\
    \                    s.pop_back();\n                }\n                p = p->par;\n\
    \                while(dict_itr != p->child.end() and not valid(dict_itr->second))\
    \ ++dict_itr;\n                if(dict_itr != p->child.end())\n              \
    \  {\n                    p = dict_itr->second;\n                    s.push_back(p->tag);\n\
    \                    break;\n                }\n            }\n            if(!p->par)\n\
    \            {\n                node_ptr = nullptr;\n            }\n         \
    \   else\n            {\n                while(not valid(p->ter))\n          \
    \      {\n                    node *nx = nullptr;\n                    for(const\
    \ auto &e : p->child)\n                    {\n                        char_type\
    \ x;\n                        node *t;\n                        std::tie(x, t)\
    \ = e;\n                        if(valid(t))\n                        {\n    \
    \                        s.push_back(x);\n                            nx = t;\n\
    \                            break;\n                        }\n             \
    \       }\n                    p = nx;\n                }\n                node_ptr\
    \ = p->ter;\n            }\n            ++type_idx;\n            return *this;\n\
    \        }\n\n        iterator_type operator++(int)\n        {\n            iterator_type\
    \ ret = *this;\n            return ++(*this), ret;\n        }\n\n        iterator_type\
    \ &operator--()\n        {\n            if(*this == trie_ptr->end())\n       \
    \     {\n                node *p = trie_ptr->root;\n                if(p->type)\n\
    \                {\n                    while(not p->is_ter)\n               \
    \     {\n                        auto dict_itr = p->child.rbegin();\n        \
    \                while(dict_itr != p->child.rend() and not valid(dict_itr->second))\
    \ ++dict_itr;\n                        if(dict_itr != p->child.rend())\n     \
    \                   {\n                            p = dict_itr->second;\n   \
    \                         s.push_back(p->tag);\n                        }\n  \
    \                      else\n                        {\n                     \
    \       p = p->ter;\n                        }\n                    }\n      \
    \              node_ptr = p;\n                }\n            }\n            else\n\
    \            {\n                bool is_prefix = false;\n                node\
    \ *p = node_ptr->par;\n                while(p->par)\n                {\n    \
    \                auto map_ritr = p->par->child.rend();\n                    map_ritr\
    \ = std::reverse_iterator<typename dict_type::iterator>(p->par->child.lower_bound(p->tag));\n\
    \                    s.pop_back();\n                    p = p->par;\n        \
    \            while(map_ritr != p->child.rend() and not valid(map_ritr->second))\
    \ ++map_ritr;\n                    if(map_ritr != p->child.rend())\n         \
    \           {\n                        p = map_ritr->second;\n               \
    \         s.push_back(map_ritr->first);\n                        break;\n    \
    \                }\n                    else if(p->ter and p->ter->type)\n   \
    \                 {\n                        is_prefix = true;\n             \
    \           break;\n                    }\n                }\n               \
    \ if(is_prefix)\n                {\n                    node_ptr = p->ter;\n \
    \               }\n                else\n                {\n                 \
    \   if(!p->par)\n                    {\n                        node_ptr = nullptr;\n\
    \                    }\n                    else\n                    {\n    \
    \                    while(not p->is_ter)\n                        {\n       \
    \                     auto map_ritr = p->child.rbegin();\n                   \
    \         while(map_ritr != p->child.rend() and not valid(map_ritr->second)) ++map_ritr;\n\
    \                            if(map_ritr != p->child.rend())\n               \
    \             {\n                                s.push_back(map_ritr->first);\n\
    \                                p = map_ritr->second;\n                     \
    \       }\n                            else\n                            {\n \
    \                               p = p->ter;\n                            }\n \
    \                       }\n                        node_ptr = p;\n           \
    \         }\n                }\n            }\n            --type_idx;\n     \
    \       if(node_ptr) size_idx -= node_ptr->cnt;\n            else size_idx = -1;\n\
    \            return *this;\n        }\n\n        iterator_type operator--(int)\n\
    \        {\n            iterator_type ret = *this;\n            return --(*this),\
    \ ret;\n        }\n\n        size_t count() const\n        {\n            return\
    \ node_ptr ? node_ptr->cnt : 0;\n        }\n    }; // class iterator_type\n  \
    \  friend iterator_type;\n\n    iterator_type begin() { return iterator_type(this,\
    \ 0); }\n    iterator_type end() { return iterator_type(this, type()); }\n   \
    \ std::reverse_iterator<iterator_type> rbegin() { return std::reverse_iterator<iterator_type>(end());\
    \ }\n    std::reverse_iterator<iterator_type> rend() { return std::reverse_iterator<iterator_type>(begin());\
    \ }\n\n    iterator_type lower_bound(const str_type &key)\n    {\n        size_t\
    \ size_idx = 0, type_idx = 0;\n        str_type s;\n        node *p = root;\n\
    \        bool go_back = false;\n        for(const char_type &x : key)\n      \
    \  {\n            if(p->ter)\n            {\n                size_idx += p->ter->cnt;\n\
    \                type_idx += p->ter->type;\n            }\n            node *nx\
    \ = nullptr;\n            for(const auto &e : p->child)\n            {\n     \
    \           char_type y;\n                node *t;\n                std::tie(y,\
    \ t) = e;\n                if(valid(t))\n                {\n                 \
    \   if(y < x)\n                    {\n                        size_idx += t->cnt;\n\
    \                        type_idx += t->type;\n                    }\n       \
    \             else if(t->type)\n                    {\n                      \
    \  s.push_back(y);\n                        nx = t;\n                        break;\n\
    \                    }\n                }\n            }\n            if(not nx)\n\
    \            {\n                go_back = true;\n                break;\n    \
    \        }\n            p = nx;\n            if(p->tag > x) break;\n        }\n\
    \        if(go_back)\n        {\n            while(!p->par)\n            {\n \
    \               p = p->par;\n                auto dict_itr = p->child.upper_bound(s.back());\n\
    \                s.pop_back();\n                while(dict_itr != p->child.end()\
    \ and not valid(dict_itr->second)) ++dict_itr;\n                if(dict_itr !=\
    \ p->child.end())\n                {\n                    p = dict_itr->second;\n\
    \                    s.push_back(dict_itr->first);\n                    break;\n\
    \                }\n            }\n            if(!p->par) return end();\n   \
    \     }\n        while(not p->is_ter)\n        {\n            if(valid(p->ter))\n\
    \            {\n                p = p->ter;\n            }\n            else\n\
    \            {\n                auto dict_itr = p->child.begin();\n          \
    \      while(dict_itr != p->child.end() and not valid(dict_itr->second)) ++dict_itr;\n\
    \                p = dict_itr->second;\n                s.push_back(dict_itr->first);\n\
    \            }\n        }\n        return iterator_type(this, p, s, type_idx,\
    \ size_idx);\n    }\n\n    iterator_type upper_bound(const str_type &key)\n  \
    \  {\n        auto itr = lower_bound(key);\n        if(*itr == key) ++itr;\n \
    \       return itr;\n    }\n\n    struct Aho_Corasick\n    {\n        node *root;\n\
    \n        Aho_Corasick() : root() {}\n        Aho_Corasick(const trie &trie) {\
    \ build(trie); }\n\n        node *build(const trie<str_type> &trie)\n        {\n\
    \            root = trie.root;\n            std::queue<node*> que;\n         \
    \   que.emplace(root);\n            while(!que.empty())\n            {\n     \
    \           node *const now = que.front();\n                que.pop();\n     \
    \           for(const auto &e : now->child)\n                {\n             \
    \       char_type x;\n                    node *t, *p = now;\n               \
    \     std::tie(x, t) = e;\n                    do\n                    {\n   \
    \                     p = p->failure;\n                    } while(p and not p->child[x]);\n\
    \                    t->failure = p ? p->child[x] : root;\n                  \
    \  t->sfx_wrd += t->failure->sfx_wrd;\n                    que.emplace(t);\n \
    \               }\n            }\n            return root;\n        }\n\n    \
    \    node *next(node *now, const char_type &x)\n        {\n            while(now\
    \ and not now->child[x])\n            {\n                now = now->failure;\n\
    \            }\n            return now = now ? now->child[x] : root;\n       \
    \ }\n\n        size_t query(node *now) { return now->sfx_wrd; }\n    }; // struct\
    \ Aho_Corasick\n}; // struct trie\n\n#endif // Trie_hpp\n"
  dependsOn: []
  isVerificationFile: false
  path: deprecated/trie.hpp
  requiredBy: []
  timestamp: '2020-08-10 20:33:17+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: deprecated/trie.hpp
layout: document
redirect_from:
- /library/deprecated/trie.hpp
- /library/deprecated/trie.hpp.html
title: deprecated/trie.hpp
---
