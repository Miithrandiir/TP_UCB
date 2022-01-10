#include <iostream>
#include <random>
#include "src/Manchot.hpp"
#include <memory>
#include <map>
#include <algorithm>

double K = 1;

double rechercheAleatoire(int nbIterations, std::vector<std::shared_ptr<Manchot>> manchots) {
    double sum = 0;
    for (int i = 0; i < nbIterations; i++) {
        std::random_device rd{};
        std::mt19937_64 gen{rd()};
        std::uniform_int_distribution<int> d(0, manchots.size() - 1);
        int rand = d(gen);
        sum += manchots[rand]->tirerBras();
    }
    return sum;
}


double rechercheGloutonne(int nbIterations, std::vector<std::shared_ptr<Manchot>> manchots) {
    std::shared_ptr<Manchot> meilleur_manchot;
    double gain = 0.0;
    double best_gain = std::numeric_limits<double>::min();
    for (std::shared_ptr<Manchot> manchot: manchots) {

        if (nbIterations <= 0)
            return gain;

        double tmp_gain = manchot->tirerBras();
        if (best_gain < tmp_gain) {
            best_gain = tmp_gain;
            meilleur_manchot = manchot;
            gain += tmp_gain;
        }

        nbIterations--;
    }

    for (int i = 0; i < nbIterations; i++) {
        double tmp_gain = meilleur_manchot->tirerBras();
        gain += tmp_gain;
    }

    return gain;
}

double
UCB_formula(std::map<std::shared_ptr<Manchot>, std::pair<int, double>> partie, std::shared_ptr<Manchot> manchot) {
    double xi = partie[manchot].second / partie[manchot].first;
    double nb_tirage_machine = partie[manchot].first;
    double nb_tirage = 0;
    for (std::pair<std::shared_ptr<Manchot>, std::pair<int, double>> item: partie) nb_tirage += item.second.first;

    return xi + K * sqrt((2*log(nb_tirage)) / nb_tirage_machine);
}

double rechercherUCB(int nbIterations, std::vector<std::shared_ptr<Manchot>> manchots) {
    std::map<std::shared_ptr<Manchot>, std::pair<int, double>> map;
    double gain = 0.0;
    for (const std::shared_ptr<Manchot> &manchot: manchots) {

        if (nbIterations <= 0)
            return gain;

        double tmp_gain = manchot->tirerBras();
        gain += tmp_gain;
        map.insert(std::make_pair(manchot, std::make_pair(1, tmp_gain)));

        nbIterations--;
    }

    for (int i = 0; i < nbIterations; i++) {

        std::pair<std::shared_ptr<Manchot>, std::pair<int, double>> best_manchot = *std::max_element(map.begin(),
                                                                                                     map.end(),
                                                                                                     [&](const std::pair<std::shared_ptr<Manchot>, std::pair<int, double>> &manchot1,
                                                                                                         const std::pair<std::shared_ptr<Manchot>, std::pair<int, double>> &manchot2) {
                                                                                                         return UCB_formula(
                                                                                                                 map,
                                                                                                                 manchot1.first) <
                                                                                                                UCB_formula(
                                                                                                                        map,
                                                                                                                        manchot2.first);
                                                                                                     });

        double tmp_gain = best_manchot.first->tirerBras();
        gain += tmp_gain;
        map[best_manchot.first].first++;
        map[best_manchot.first].second += tmp_gain;
    }
    std::cout << "Répartition des essais UCB: ";
    for(const auto& item : map) {
        std::cout << item.second.first << " ";
    }
    std::cout << std::endl;
    return gain;
}

std::vector<std::shared_ptr<Manchot>> creerManchots(int nb) {
    std::vector<std::shared_ptr<Manchot>> manchots;
    for (int i = 0; i < nb; i++) {
        std::random_device rd{};
        std::mt19937_64 gen{rd()};
        std::uniform_int_distribution<int> esperance(-10, 10);
        std::uniform_int_distribution<int> variance(0, 10);
        std::shared_ptr<Manchot> manchot = std::make_shared<Manchot>(esperance(gen), variance(gen));
        manchots.push_back(manchot);
    }
    return manchots;
}

int main() {

    K = 1000;
    for (int i = 0; i < 10; i++) {
        K = K /10;
        std::cout << "K = " << std::to_string(K) << std::endl;
        std::vector<std::shared_ptr<Manchot>> manchots = creerManchots(15);
        std::cout << "score random : " << rechercheAleatoire(15000, manchots) << " " << std::endl;
        std::cout << "score glouton : " << rechercheGloutonne(15000, manchots) << " " << std::endl;
        double gain = rechercherUCB(15000, manchots);
        std::cout << "score UCB : " << gain << " " << std::endl;
    }
    return 0;

}
