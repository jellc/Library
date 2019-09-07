template <class A>
std::vector<int> Manacher(const A &v)
{
    int n = v.size();
    std::vector<int> r(n);
    for(int i = 0, c = 0; i < n; ++i)
    {
        int l = c * 2 - i;
        if(l >= 0 && c + r[c] > i + r[l])
        {
            r[i] = r[l];
        }
        else
        {
            int j = c + r[c] - i;
            while(i - j >= 0 && i + j < n && v[i - j] == v[i + j])
                ++j;
            r[i] = j;
            c = i;
        }
    }
    return r;
}
