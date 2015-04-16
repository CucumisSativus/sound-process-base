//
// Created by Michał Gutowski on 26.03.15.
//

#ifndef SOUND_PROCESS_BASE_GNUPLOTPLOTTER_H
#define SOUND_PROCESS_BASE_GNUPLOTPLOTTER_H

#include "ToFilePlotter.h"
class GnuplotPlotter : public ToFilePlotter{
public:
    virtual void plot(PointsVector3d points) override;

    virtual void plot2d(PointsVector2d points) override;

    GnuplotPlotter(std::string filename);
private:
    std::string filename;
};


#endif //SOUND_PROCESS_BASE_GNUPLOTPLOTTER_H
