//
// Created by Michał Gutowski on 26.03.15.
//

#include "GnuplotPlotter.h"

GnuplotPlotter::GnuplotPlotter(std::string filename)
    : ToFilePlotter(filename)
{ }

void GnuplotPlotter::plot(PointsVector points) {
    ToFilePlotter::plot(points);
    system("gnuplot -e \"set term png; set output \'plot.png\' ; splot \'out.dat\' using 1:2:3 with lines\" ; qlmanage -p plot.png");
}
