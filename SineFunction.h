//
// Created by Michał Gutowski on 01.04.15.
//

#ifndef SOUND_PROCESS_BASE_SINEFUNCTION_H
#define SOUND_PROCESS_BASE_SINEFUNCTION_H

#include "WaveFunction.h"
#include <cmath>
class SineFunction : public WaveFunction{

public:
    virtual double compute(double x);
};


#endif //SOUND_PROCESS_BASE_SINEFUNCTION_H
