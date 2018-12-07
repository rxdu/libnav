/* 
 * sim_scenarios.cpp
 * 
 * Created on: Dec 07, 2018 02:01
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#include "traffic_sim/sim_scenarios.hpp"

namespace librav
{

TrafficSimConfig SimScenario::GenerateScenarioCase1()
{
    TrafficSimConfig config;

    config.tf = 15.0;
    config.dt = 0.1;

    config.map = "/home/rdu/Workspace/librav/data/road_map/intersection_single_lane_full.osm";

    config.surrounding_vehicles.push_back(VehicleInfo(std::make_pair("s2", "s1"), 20.0, 15.0));
    config.surrounding_vehicles.push_back(VehicleInfo(std::make_pair("s2", "s1"), 40.0, 15.5));
    config.surrounding_vehicles.push_back(VehicleInfo(std::make_pair("s2", "s1"), 90.0, 15.5));
    config.surrounding_vehicles.push_back(VehicleInfo(std::make_pair("s6", "s3"), 15.0, 15.0));
    config.surrounding_vehicles.push_back(VehicleInfo(std::make_pair("s6", "s3"), 35.0, 15.0));
    config.surrounding_vehicles.push_back(VehicleInfo(std::make_pair("s6", "s3"), 95.0, 16.0));

    return config;
}

} // namespace librav