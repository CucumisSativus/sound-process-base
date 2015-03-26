//
// Created by Michał Gutowski on 26.03.15.
//

#include "GnuplotPlotter.h"

GnuplotPlotter::GnuplotPlotter(std::string filename)
    : ToFilePlotter(filename)
{ }

void GnuplotPlotter::plot(PointsVector points) {
    ToFilePlotter::plot(points);
    system("gnuplot -e \"set term png; set output \'plot.png\' ; plot \'out.dat\' using 1:2 \"; qlmanage -p plot.png");
}
