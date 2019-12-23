#ifndef SKEWHEAP_HPP
#define SKEWHEAP_HPP

template <class T>
class Skewheap
{
    const std::function<bool(const T&, const T&)> comp;

  public:
    struct node
    {
        node *lft, *rgt; T key;
        ~node() { delete lft; delete rgt; }
      private:
        friend Skewheap;
        void clear() { lft = rgt = nullptr; }
    }; // struct node

    Skewheap(const std::function<bool(const T&, const T&)> &f = std::less<T>()) : comp(f) {}

    node *make() const { return nullptr; }

    node *push(node *root, const T &key) const
    {
        return meld(root, new node{ nullptr, nullptr, key });
    }

    node* pop(node *root) const
    {
        node *nroot = meld(root->lft, root->rgt);
        return root->clear(), nroot;
    }

    node *meld(node *x, node *y) const
    {
        if(!x) return y;
        if(!y) return x;
        if(comp(x->key, y->key)) std::swap(x, y);
        x->rgt = meld(y, x->rgt);
        std::swap(x->lft, x->rgt);
        return x;
    }

    bool empty(node *root) const { return !root; }
}; // class Skewheap

#endif