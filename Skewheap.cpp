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
    };

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
};


// template <class T>
// class Skewheap
// {
//     const std::function<bool(const T&, const T&)> comp;

//   public:
//     struct node
//     {
//         node *lft, *rgt; T key;
//         void clear()
//         {
//             if(lft) lft->clear();
//             if(rgt) rgt->clear();
//             delete lft, rgt;
//         }
//     };

//     node *root;

//     ~Skewheap()
//     {
//         if(root)
//         {
//             root->clear(); delete root;
//         }
//     }

//     node *alloc() const
//     {
//         return nullptr;
//     }

//     node *meld(node *x, node *y) const
//     {
//         if(!x) return y;
//         if(!y) return x;
//         if(comp(x->key, y->key)) swap(x, y);
//         x->rgt = meld(y, x->rgt);
//         swap(x->lft, x->rgt);
//         return x;
//     }

//     T top() const
//     {
//         return root->key;
//     }

//     void push(const T &key)
//     {
//         return root = meld(root, new node{ nullptr, nullptr, key });
//     }

//     void pop()
//     {
//         return root = meld(root->lft, root->rgt);
//     }

//     bool empty() const
//     {
//         return !root;
//     }

//     void meld(Skewheap &other)
//     {
//         root = meld(root, other->root);
//     }
// };