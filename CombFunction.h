//
// Created by Michał Gutowski on 01.04.15.
//

#ifndef SOUND_PROCESS_BASE_SINEFUNCTION_H
#define SOUND_PROCESS_BASE_SINEFUNCTION_H

#include "WaveFunction.h"
#include <cmath>
class CombFunction : public WaveFunction{

public:
    virtual double compute(int x, int frequency, int resolution);
private:
    int roundToNearestValue(int x, int resolution);

};


#endif //SOUND_PROCESS_BASE_SINEFUNCTION_H
