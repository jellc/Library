// #line 2 "Random_number_generator.hpp"
#ifndef Random_number_generator_hpp
#define Random_number_generator_hpp
#include <random>

template <typename num_t>
class Random_number_generator
{
    template <bool is_int, class = void>
    struct unif_t
    {
        std::uniform_int_distribution<num_t> unif;
        unif_t(num_t lower, num_t upper) : unif(lower, upper) {}
        num_t operator()(std::mt19937 &engine) { return unif(engine); }
    };
    template <class void_t>
    struct unif_t<false, void_t>
    {
        std::uniform_real_distribution<num_t> unif;
        unif_t(num_t lower, num_t upper) : unif(lower, upper) {}
        num_t operator()(std::mt19937 &engine) { return unif(engine); }
    };
    unif_t<std::is_integral<num_t>::value> unif;
    std::mt19937 engine;
  public:
    // generate random number in [lower, upper].
    Random_number_generator(num_t lower = std::numeric_limits<num_t>::min(), num_t upper = std::numeric_limits<num_t>::max()) : unif(lower, upper), engine(std::random_device{}()) {}
    num_t operator()() { return unif(engine); }
};

#endif // Random_number_generator_hpp