# Dependency libraries
#find_package(LIBRARY_NAME REQUIRED)

## tests
add_executable(test_polyline test_polyline.cpp)
target_link_libraries(test_polyline geometry)

add_executable(test_cubic_spline test_cubic_spline.cpp)
target_link_libraries(test_cubic_spline geometry)

add_executable(test_parametric_curve test_parametric_curve.cpp)
target_link_libraries(test_parametric_curve geometry)

add_executable(test_polygon test_polygon.cpp)
target_link_libraries(test_polygon geometry)

# add_executable(test_pcurve test_pcurve.cpp)
# target_link_libraries(test_pcurve geometry)

# add_executable(test_polynomial test_polynomial.cpp)
# target_link_libraries(test_polynomial geometry)

# add_executable(test_pcurve_draw test_pcurve_draw.cpp)
# target_link_libraries(test_pcurve_draw geometry)

# add_executable(test_cspline_draw test_cspline_draw.cpp )
# target_link_libraries(test_cspline_draw geometry)

# add_executable(test_polygon_draw test_polygon_draw.cpp )
# target_link_libraries(test_polygon_draw geometry)

# add_executable(test_dist_draw test_dist_draw.cpp )
# target_link_libraries(test_dist_draw geometry)

# add_executable(test_pcurve_viz test_pcurve_viz.cpp)
# target_link_libraries(test_pcurve_viz geometry)

# add_executable(test_polygon_viz test_polygon_viz.cpp )
# target_link_libraries(test_polygon_viz geometry)

# add_executable(test_cspline_viz test_cspline_viz.cpp )
# target_link_libraries(test_cspline_viz geometry)
