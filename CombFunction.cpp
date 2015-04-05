//
// Created by Michał Gutowski on 01.04.15.
//

#include "CombFunction.h"

double CombFunction::compute(double x, double frequency) {
    double halfPeriod = 0.5 * (1/frequency);
    double sum = 0;
    for(int n =1; n < 21; n+=2){
        double numerator = std::pow(-1, (n-1)/2);
        double denominator = n*n;
        double sinus = std::sin((n*M_PI*x)/halfPeriod);

        sum += (numerator/denominator)*sinus;
    }
    return (8/(M_PI*M_PI)) * sum;
}
