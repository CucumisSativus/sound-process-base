//
// Created by Michał Gutowski on 26.03.15.
//

#include "GnuplotPlotter.h"

GnuplotPlotter::GnuplotPlotter(std::string filename)
    : ToFilePlotter(filename), filename(filename)
{ }

void GnuplotPlotter::plot(PointsVector3d points) {
    ToFilePlotter::plot(points);
    system("gnuplot -e \"set term png; set output \'plot.png\' ; splot \'out.dat\' using 1:2:3 \" ; qlmanage -p plot.png");
}

void GnuplotPlotter::plot2d(PointsVector2d points) {
    ToFilePlotter::plot2d(points);

    std::string setTerminal = std::string("gnuplot -e \"set term png; set output \'plot.png\' ;");
    std::string setPlot1 = std::string(std::string("plot '") + filename + std::string("' using 1 with lines title 'Function',"));
    std::string setPlot2 = std::string(std::string("'") + filename + std::string("' using 2 with lines title 'Samples'\";"));
    std::string qlmanage = std::string(" qlmanage -p plot.png");
    system(std::string(setTerminal + setPlot1 + setPlot2 + qlmanage).c_str());
}
