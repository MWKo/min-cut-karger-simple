#include "random.hpp"

#include <ctime>

std::default_random_engine randomGenerator(time(0));

ull binom(ull trials, double prob, ull ciel) {
    // use inverse transform sampling
    std::uniform_real_distribution<double> urd(0.0, 1.0);
    double uniformProb = urd(randomGenerator);

    double binomProb = pow(1 - prob, trials);
    double sumBinomProb = binomProb;
    for (ull em = 0; em <= ciel; em++) {
        if (sumBinomProb > uniformProb) return em;
        binomProb *= double(trials - em)/(em + 1) * prob / (1 - prob);
        sumBinomProb += binomProb;
    }
    return ciel;
}