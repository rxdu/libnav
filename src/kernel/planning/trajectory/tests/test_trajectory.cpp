#include <iostream>
#include <vector>
#include <cmath>

#include "trajectory/trajectory.hpp"

using namespace librav;

int main()
{
    Trajectory<3> traj;

    std::cout << "trajectory dimension: " << traj.GetDimension() << std::endl;

    return 0;
}