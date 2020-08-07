#include <cassert>
#include <vector>
// compute the maximum flow.
template <class cap_t = int>
struct Dinic
{
    struct edge_t
    {
        size_t src, dst;
        cap_t cap; size_t rev;
        edge_t(size_t src, size_t dst, cap_t cap, size_t rev) : src(src), dst(dst), cap(cap), rev(rev) {}
    };

    using adj_type = std::vector<edge_t>;

    Dinic(size_t n = 0) : adjs(n), level(n), itr(n) {}

    size_t size() const { return adjs.size(); }

    adj_type &operator[](size_t node) { assert(node < size()); return adjs[node]; }
    const adj_type &operator[](size_t node) const { assert(node < size()); return adjs[node]; }

    void add_edge(size_t src, size_t dst, cap_t cap)
    {
        assert(src < size()); assert(dst < size());
        if(!(cap > 0) || src == dst) return;
        adjs[src].emplace_back(src, dst, cap, adjs[dst].size());
        adjs[dst].emplace_back(dst, src, 0, adjs[src].size() - 1);
    }

    void add_undirected_edge(size_t src, size_t dst, cap_t cap)
    {
        assert(src < size()); assert(dst < size());
        if(!(cap > 0) || src == dst) return;
        adjs[src].emplace_back(src, dst, cap, adjs[dst].size());
        adjs[dst].emplace_back(dst, src, cap, adjs[src].size() - 1);
    }

    cap_t max_flow(size_t src, size_t dst)
    {
        assert(src < size()); assert(dst < size());
        cap_t flow(0), bound(0);
        for(const edge_t &e : adjs[src]) bound += e.cap;
        for(std::vector<size_t> que(size()); ; std::fill(itr.begin(), itr.end(), 0))
        {
            std::fill(level.begin(), level.end(), level_infty);
            level[que.front() = src] = 0;
            for(auto ql{que.begin()}, qr{std::next(ql)}; level[dst] == level_infty && ql != qr; ++ql)
            {
                for(const edge_t &e : adjs[*ql])
                    if(e.cap > 0 && level[e.dst] == level_infty)
                        level[*qr++ = e.dst] = level[*ql] + 1;
            }
            if(level[dst] == level_infty) break;
            flow += dfs(src, dst, bound);
        }
        return flow;
    }

protected:
    std::vector<adj_type> adjs;
    std::vector<size_t> level, itr;
    constexpr static size_t level_infty = -1;

    cap_t dfs(const size_t &src, const size_t &dst, cap_t bound)
    {
        if(src == dst || bound == 0) return bound;
        cap_t flow(0);
        for(size_t &i{itr[dst]}; i != adjs[dst].size(); ++i)
        {
            auto &e = adjs[dst][i], &re = adjs[e.dst][e.rev];
            if(re.cap > 0 && level[e.dst] < level[dst])
            {
                if(cap_t achv = dfs(src, e.dst, std::min(bound, re.cap)); achv > 0)
                {
                    e.cap += achv, re.cap -= achv;
                    flow += achv, bound -= achv;
                    if(bound == 0) break;
                }
            }
        }
        return flow;
    }
}; // struct Dinic
