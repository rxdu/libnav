#include <iostream>

#include "field/collision_field.hpp"

#include "fastplot/field_plot.hpp"
#include "fastplot/contour_plot.hpp"
#include "stopwatch/stopwatch.h"

using namespace librav;

int main()
{
    const int32_t fsize_x = 301;
    const int32_t fsize_y = 301;

    CollisionField cfield(fsize_x, fsize_y);
    cfield.SetOriginCoordinate(150,150);
    cfield.LoadEgoCenteredBasisPattern(50, M_PI/4);
    // cfield.LoadUniformBasisPattern(50,50);
    cfield.UpdateCollisionField();

    std::cout << "collision field created" << std::endl;

    ScalarFieldMatrix mat = cfield.GenerateFieldMatrix(0, 1, 0, 1, true);

    // plot surface
    // FieldPlot fplot(50, 50);
    // fplot.SetWrapScale(4.0);
    // fplot.ShowField(mat.x, mat.y, mat.z, true);

    ContourPlot cplot;
    cplot.ShowContour(mat.x, mat.y, mat.z, true);

    return 0;
}