#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const ll inf64 = (1LL << 62) - 1;

template <class Abel = int> struct BIT {
	typedef function<Abel(const Abel&,const Abel&)> opr_t;
	const opr_t opr,invopr;
	const Abel idel;
	const int sz;
	int range = 1;
	vector<Abel> data,val;	// 1-indexed

	BIT(int sz, Abel init_val, const opr_t &f = plus<Abel>(), const opr_t &g = minus<Abel>(), Abel idel = 0) : sz(sz), opr(f),invopr(g),idel(idel)
	{
		while(sz >= range) range <<= 1;
		data.resize(range);
		init(init_val);
	}

	void init(Abel v) {
		val.assign(range,v);
		val[0] = idel;
		vector<Abel> tmp(range);
		partial_sum(begin(val),end(val),begin(tmp),opr);
		for(int i = 0; i < range; ++i) data[i] = invopr(tmp[i],tmp[i - (i & -i)]);
	}

	// for the interval [1,n]
	Abel query(int n) { return n ? opr(query(n - (n & -n)),data[n]) : idel; }

	// for the interval [l,r]
	Abel query(int l, int r) { return invopr(query(r),query(l - 1)); }

	void add(int idx, Abel diff = 1) { update(idx,val[idx] + diff); }

	void update(int idx, Abel v) {
		Abel prev = val[idx];
		for(val[idx] = v; idx < range; idx += idx & -idx) data[idx] = opr(invopr(data[idx],prev),v);
	}

	int lower_bound(Abel obj) {
		int l = 0,r = range;
		while(r - l > 1) {
			int mid = (l + r) / 2;
			if(data[mid] >= obj) r = mid;
			else obj -= data[l = mid];
		}
		return min(r,sz + 1);
	}

	int upper_bound(Abel obj) {
		int l = 0,r = range;
		while(r - l > 1) {
			int mid = (l + r) / 2;
			if(data[mid] > obj) r = mid;
			else obj -= data[l = mid];
		}
		return min(r,sz + 1);
	}
};


int main(){

}
