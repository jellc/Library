// binary search on discrete range.
template <class iter_type, class pred_type>
iter_type binary(iter_type ok, iter_type ng, pred_type pred)
{
    assert(ok != ng);
    long long dist(ng - ok);
    while(std::abs(dist) > 1)
    {
        iter_type mid(ok + dist / 2);
        if(pred(mid)) ok = mid, dist -= dist / 2;
        else ng = mid, dist /= 2;
    }
    return ok;
}
// binary search on real numbers.
template <class pred_type>
long double binary(long double ok, long double ng, const long double eps, pred_type pred)
{
    assert(ok != ng);
    while(std::abs(ok - ng) > eps)
    {
        long double mid{(ok + ng) / 2};
        (pred(mid) ? ok : ng) = mid;
    }
    return ok;
}
