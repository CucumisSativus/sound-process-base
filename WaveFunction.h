//
// Created by Michał Gutowski on 01.04.15.
//

#ifndef SOUND_PROCESS_BASE_WAVEFUNCTION_H
#define SOUND_PROCESS_BASE_WAVEFUNCTION_H
class WaveFunction {
public:
    virtual double compute(int x, int frequency, int resolution) = 0;
    virtual ~WaveFunction() {};
};
#endif //SOUND_PROCESS_BASE_WAVEFUNCTION_H
