#include <bits/stdc++.h>
using namespace std;

namespace Z_algorithm {
    vector<int> prefix(const string &str) {
        vector<int> pref(str.size());
        for(int i = 1, j = 0; i < (int)str.size(); ++i) {
            if(pref[i - j] + i < pref[j] + j) {
                pref[i] = pref[i - j];
            } else {
                int k = max(0, pref[j] + j - i);
                while(k + i < (int)str.size() && str[k] == str[k + i]) ++k;
                pref[i] = k;
                j = i;
            }
        }
        pref[0] = str.size();
        return pref;
    }

    vector<int> prefix(const string &str, const string &key) {
        vector<int> pref = prefix(key + str);
        for(int &i : pref) i = min(i,(int)key.size());
        return vector<int>(begin(pref) + key.size(), end(pref));
    }
}

