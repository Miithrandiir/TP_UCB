//
// Created by mithrandir on 17/12/2021.
//

#ifndef TP_UCB_MANCHOT_HPP
#define TP_UCB_MANCHOT_HPP


class Manchot {
private:
    double esperance;
    double variance;
public:
    Manchot(double esperance, double variance) : esperance(esperance), variance(variance)  {
    }

    double tirerBras();
};


#endif //TP_UCB_MANCHOT_HPP
