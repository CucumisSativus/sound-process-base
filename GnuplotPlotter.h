//
// Created by Michał Gutowski on 26.03.15.
//

#ifndef SOUND_PROCESS_BASE_GNUPLOTPLOTTER_H
#define SOUND_PROCESS_BASE_GNUPLOTPLOTTER_H

#include "ToFilePlotter.h"
class GnuplotPlotter : public ToFilePlotter{
public:
    virtual void plot(PointsVector points) override;

    GnuplotPlotter(std::string filename);
};


#endif //SOUND_PROCESS_BASE_GNUPLOTPLOTTER_H
