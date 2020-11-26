#include <chrono>
#include <iostream>
#include <string>

class
{
    std::chrono::system_clock::time_point built_pt, last_pt;
    int built_ln, last_ln;
    std::string built_func, last_func;
    bool is_built = false;

public:
    void build(int crt_ln, const std::string &crt_func)
    {
        is_built = true, last_pt = built_pt = std::chrono::system_clock::now(), last_ln = built_ln = crt_ln, last_func = built_func = crt_func;
    }

    void set(int crt_ln, const std::string &crt_func)
    {
        if(is_built) last_pt = std::chrono::system_clock::now(), last_ln = crt_ln, last_func = crt_func;
        else std::cerr << "[ " << crt_ln << " : " << crt_func << " ] " << "myclock_t::set failed (yet to be built!)\n";
    }

    void get(int crt_ln, const std::string &crt_func)
    {
        if(is_built)
        {
            std::chrono::system_clock::time_point crt_pt(std::chrono::system_clock::now());
            long long diff = std::chrono::duration_cast<std::chrono::milliseconds>(crt_pt - last_pt).count();
            std::cerr << diff << " ms elapsed from" << " [ " << last_ln << " : " << last_func << " ]";
            if(last_ln == built_ln) std::cerr << " (when built)";
            std::cerr << " to" << " [ " << crt_ln << " : " << crt_func << " ]" << "\n";
            last_pt = built_pt, last_ln = built_ln, last_func = built_func;
        }
        else
        {
            std::cerr << "[ " << crt_ln << " : " << crt_func << " ] " << "myclock_t::get failed (yet to be built!)\n";
        }
    }
} myclock; // unnamed class

#define build_clock() myclock.build(__LINE__, __func__)
#define set_clock() myclock.set(__LINE__, __func__)
#define get_clock() myclock.get(__LINE__, __func__)
