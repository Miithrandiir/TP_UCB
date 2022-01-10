//
// Created by mithrandir on 17/12/2021.
//

#include <random>
#include "Manchot.hpp"

double Manchot::tirerBras() {
    std::random_device rd{};
    std::mt19937_64 gen{rd()};

    std::normal_distribution<double> d{esperance,variance};

    return d(gen);

}
