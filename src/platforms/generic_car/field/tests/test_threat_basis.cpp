#include "field/threat_basis.hpp"
#include "field/threat_distribution.hpp"
#include "fastplot/field_plot.hpp"

#include "stopwatch/stopwatch.h"

using namespace librav;

int main()
{
    ThreatBasis basis(50, 50);

    stopwatch::StopWatch timer;
    timer.tic();
    GaussianThreat gau(20, 20, 5);
    basis.SetThreatBasisDistribution(gau);
    ScalarFieldMatrix mat = basis.GenerateFieldMatrix(0, 1, 0, 1, true);
    std::cout << "time elapsed: " << timer.toc() << std::endl;

    // plot surface
    FastPlot::ShowFieldSurface(mat.x, mat.y, mat.z, true);

    return 0;
}