//
// Created by Michał Gutowski on 23.03.15.
//

#ifndef _SOUND_PROCESS_BASE_ANALYSER_H_
#define _SOUND_PROCESS_BASE_ANALYSER_H_
class Analyser {
    virtual void plot(unsigned long start, unsigned long samples_count) const = 0;
};

#endif //_SOUND_PROCESS_BASE_ANALYSER_H_
