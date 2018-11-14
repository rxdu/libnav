/* 
 * geometry_draw.cpp
 * 
 * Created on: Aug 10, 2018 09:18
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#include "lightviz/details/geometry_draw.hpp"

#include <cassert>

#include <tbb/tbb.h>

using namespace librav;
using namespace LightViz;
using namespace CvDraw;

void GeometryDraw::DrawPolyline(const Polyline &polyline, bool show_dot, cv::Scalar ln_color, int32_t ln_width)
{
    std::size_t pt_num = polyline.GetPointNumer();

    if (pt_num == 0)
    {
        return;
    }
    else if (pt_num == 1)
    {
        if (show_dot)
        {
            auto pt = canvas_.ConvertCartisianToPixel(polyline.GetPoint(0).x, polyline.GetPoint(0).y);
            DrawPoint(canvas_.paint_area, cv::Point(pt.x, pt.y), CvDrawColors::red_color);
        }
    }
    else
    {
        for (std::size_t i = 0; i < pt_num - 1; ++i)
        {
            auto pt1 = canvas_.ConvertCartisianToPixel(polyline.GetPoint(i).x, polyline.GetPoint(i).y);
            auto pt2 = canvas_.ConvertCartisianToPixel(polyline.GetPoint(i + 1).x, polyline.GetPoint(i + 1).y);
            DrawLine(canvas_.paint_area, cv::Point(pt1.x, pt1.y), cv::Point(pt2.x, pt2.y), ln_color, ln_width);
        }
        if (show_dot)
        {
            for (std::size_t i = 0; i < pt_num; ++i)
            {
                auto pt1 = canvas_.ConvertCartisianToPixel(polyline.GetPoint(i).x, polyline.GetPoint(i).y);
                DrawPoint(canvas_.paint_area, cv::Point(pt1.x, pt1.y), CvDrawColors::red_color);
            }
        }
    }
}

void GeometryDraw::DrawCubicSpline(const CSpline &spline, double step, cv::Scalar ln_color, int32_t ln_width)
{
    std::vector<cv::Point2d> pts;
    std::vector<CSpline::Knot> knots(spline.GetAllKnots());
    for (double x = knots.front().x; x < knots.back().x; x += step)
        pts.emplace_back(x, spline.Evaluate(x));

    std::cout << "intermediate points: " << pts.size() << std::endl;

    for (std::size_t i = 0; i < pts.size() - 1; ++i)
    {
        auto pt1 = canvas_.ConvertCartisianToPixel(pts[i].x, pts[i].y);
        auto pt2 = canvas_.ConvertCartisianToPixel(pts[i + 1].x, pts[i + 1].y);
        DrawLine(canvas_.paint_area, cv::Point(pt1.x, pt1.y), cv::Point(pt2.x, pt2.y), ln_color, ln_width);
    }
}

void GeometryDraw::DrawParametricCurve(const ParametricCurve &pcurve, double step, cv::Scalar ln_color, int32_t ln_width)
{
    std::vector<cv::Point2d> pts;

    for (double s = 0; s < pcurve.GetTotalLength(); s += step)
        pts.emplace_back(pcurve.GetXSpline().Evaluate(s), pcurve.GetYSpline().Evaluate(s));

    // std::cout << "intermediate points: " << pts.size() << std::endl;

    for (std::size_t i = 0; i < pts.size() - 1; ++i)
    {
        auto pt1 = canvas_.ConvertCartisianToPixel(pts[i].x, pts[i].y);
        auto pt2 = canvas_.ConvertCartisianToPixel(pts[i + 1].x, pts[i + 1].y);
        DrawLine(canvas_.paint_area, cv::Point(pt1.x, pt1.y), cv::Point(pt2.x, pt2.y), ln_color, ln_width);
    }
}

void GeometryDraw::DrawPolygon(const Polygon &polygon, bool show_dot, cv::Scalar ln_color, int32_t ln_width)
{
    std::size_t pt_num = polygon.GetPointNumer();

    if (pt_num < 3)
        return;

    for (std::size_t i = 0; i < pt_num - 1; ++i)
    {
        auto pt1 = canvas_.ConvertCartisianToPixel(polygon.GetPoint(i).x, polygon.GetPoint(i).y);
        auto pt2 = canvas_.ConvertCartisianToPixel(polygon.GetPoint(i + 1).x, polygon.GetPoint(i + 1).y);
        DrawLine(canvas_.paint_area, cv::Point(pt1.x, pt1.y), cv::Point(pt2.x, pt2.y), ln_color, ln_width);
    }
    auto last_pt = canvas_.ConvertCartisianToPixel(polygon.GetPoint(pt_num - 1).x, polygon.GetPoint(pt_num - 1).y);
    auto first_pt = canvas_.ConvertCartisianToPixel(polygon.GetPoint(0).x, polygon.GetPoint(0).y);
    DrawLine(canvas_.paint_area, cv::Point(last_pt.x, last_pt.y), cv::Point(first_pt.x, first_pt.y), ln_color, ln_width);

    if (show_dot)
    {
        for (std::size_t i = 0; i < pt_num; ++i)
        {
            auto pt1 = canvas_.ConvertCartisianToPixel(polygon.GetPoint(i).x, polygon.GetPoint(i).y);
            DrawPoint(canvas_.paint_area, cv::Point(pt1.x, pt1.y), CvDrawColors::red_color);
        }
    }
}

/* 
 * Assumptions:
 *  1. Convext polygon
 *  2. Front line: first two points
*/
void GeometryDraw::DrawPolygonDirection(const Polygon &polygon, cv::Scalar ln_color, int32_t ln_width)
{
    if (polygon.GetPointNumer() < 3)
        return;
    std::vector<SimplePoint> points;
    for (int i = 0; i < polygon.GetPointNumer(); ++i)
        points.push_back(canvas_.ConvertCartisianToPixel(polygon.GetPoint(i).x, polygon.GetPoint(i).y));

    double center_x = 0;
    double center_y = 0;

    for (auto &pt : points)
    {
        center_x += pt.x;
        center_y += pt.y;
    }
    center_x = center_x / polygon.GetPointNumer();
    center_y = center_y / polygon.GetPointNumer();

    double front_x = (points[0].x + points[1].x) / 2.0;
    double front_y = (points[0].y + points[1].y) / 2.0;

    DrawArrow(canvas_.paint_area, cv::Point(center_x, center_y), cv::Point(front_x, front_y), ln_color, ln_width);
}

void GeometryDraw::DrawFilledPolygon(const Polygon &polygon, bool show_dot, cv::Scalar fill_color, cv::Scalar ln_color, int32_t ln_width)
{
    std::size_t pt_num = polygon.GetPointNumer();

    if (pt_num < 3)
        return;

    cv::Point pts[1][100];
    for (int i = 0; i < polygon.GetPointNumer(); ++i)
    {
        auto pt1 = canvas_.ConvertCartisianToPixel(polygon.GetPoint(i).x, polygon.GetPoint(i).y);
        pts[0][i] = cv::Point(pt1.x, pt1.y);
    }

    const cv::Point *ppt[1] = {pts[0]};
    int npt[] = {static_cast<int>(polygon.GetPointNumer())};

    cv::fillPoly(canvas_.paint_area, ppt, npt, 1, fill_color);
}

void GeometryDraw::WritePointPosition(const std::vector<SimplePoint> &points)
{
    for (auto &pt : points)
    {
        auto pt1 = canvas_.ConvertCartisianToPixel(pt.x, pt.y);
        std::string pos_str = "(" + std::to_string(static_cast<int32_t>(pt.x)) + "," + std::to_string(static_cast<int32_t>(pt.y)) + ")";
        WriteText(canvas_.paint_area, pos_str, cv::Point(pt1.x, pt1.y));
    }
}

void GeometryDraw::WriteTextAtPosition(std::string txt, SimplePoint pt)
{
    auto pt1 = canvas_.ConvertCartisianToPixel(pt.x, pt.y);
    WriteText(canvas_.paint_area, txt, cv::Point(pt1.x, pt1.y));
}

void GeometryDraw::DrawDistribution(double cx, double cy, double xspan, double yspan, std::function<double(double, double)> dist_fun)
{
    // std::cout << "distribution: " << cx << " , " << cy << " ; " << xmin_ << " , " << xmax_ << " , " << ymin_ << " , " << ymax_ << std::endl;

    assert(cx >= canvas_.xmin_ && cx < canvas_.xmax_ && cy >= canvas_.ymin_ && cy < canvas_.ymax_);

    // distributions coverage x/y limits
    double dxmin = cx - xspan / 2.0;
    double dxmax = cx + xspan / 2.0;
    double dymin = cy - yspan / 2.0;
    double dymax = cy + yspan / 2.0;

    // crop distribution to canvas area
    if (dxmin < canvas_.xmin_)
        dxmin = canvas_.xmin_;
    if (dxmax > canvas_.xmax_)
        dxmax = canvas_.xmax_;
    if (dymin < canvas_.ymin_)
        dymin = canvas_.ymin_;
    if (dymax > canvas_.ymax_)
        dymax = canvas_.ymax_;

    double dxspan = dxmax - dxmin;
    double dyspan = dymax - dymin;
    int32_t x_size = dxspan * canvas_.ppu_;
    int32_t y_size = dyspan * canvas_.ppu_;

    Eigen::MatrixXd threat_matrix = Eigen::MatrixXd::Zero(y_size, x_size);
    int32_t meter_per_pixel = 1 / canvas_.ppu_;
    double ppu = canvas_.ppu_;

    // serial version
    // for (int32_t i = 0; i < x_size; ++i)
    //     for (int32_t j = 0; j < y_size; ++j)
    //     {
    //         // convert to cartisian coordinate
    //         double x = dxmin + i / ppu;
    //         double y = dymin + j / ppu;

    //         threat_matrix(j, i) = dist_fun(x, y);
    //     }

    int64_t pixel_num = x_size * y_size;

    // OpenMP version
    // #pragma omp parallel for
    //     for (int64_t k = 0; k < pixel_num; ++k)
    //     {
    //         threat_matrix(k % y_size, k / y_size) = threat(dxmin + (k / y_size) / ppu, dymin + (k % y_size) / ppu, t_k);
    //     }

    // parallel version
    // const auto &fill_threat_matrix = [&dist_fun, &threat_matrix, x_size, y_size, dxmin, dymin, ppu](int64_t k) {
    //     threat_matrix(k % y_size, k / y_size) = dist_fun(dxmin + (k / y_size) / ppu, dymin + (k % y_size) / ppu);
    // };
    // igl::parallel_for(pixel_num, fill_threat_matrix, 100);
    const auto &fill_threat_matrix2 = [&dist_fun, &threat_matrix, x_size, y_size, dxmin, dymin, ppu](size_t k) {
        threat_matrix(k % y_size, k / y_size) = dist_fun(dxmin + (k / y_size) / ppu, dymin + (k % y_size) / ppu);
    };
    tbb::parallel_for(size_t(0), size_t(pixel_num), fill_threat_matrix2);

    cv::Mat threat_vis = CreateColorMapFromEigenMatrix(threat_matrix, true);

    // merge threat distribution to canvas
    auto top_left_pixel = canvas_.ConvertCartisianToPixel(dxmin, dymax); // y inverted in cartesian coordinate
    threat_vis.copyTo(canvas_.paint_area(cv::Rect(top_left_pixel.x, top_left_pixel.y, threat_vis.cols, threat_vis.rows)));
    // cv::add(canvas_.paint_area(cv::Rect(top_left_pixel.x, top_left_pixel.y, threat_vis.cols, threat_vis.rows)),
    //                 threat_vis,
    //                 canvas_.paint_area(cv::Rect(top_left_pixel.x, top_left_pixel.y, threat_vis.cols, threat_vis.rows)));

    // std::cout << int32_t(threat_vis.at<cv::Vec3b>(0, 0)[0]) << " , "
    //           << int32_t(threat_vis.at<cv::Vec3b>(0, 0)[1]) << " , "
    //           << int32_t(threat_vis.at<cv::Vec3b>(0, 0)[2]) << std::endl;

    // std::cout << "------------" << std::endl;
    // std::cout << "dx: " << dxmin << " , " << dxmax << std::endl;
    // std::cout << "dy: " << dymin << " , " << dymax << std::endl;
    // std::cout << "size: " << x_size << " , " << y_size << std::endl;
    // std::cout << "threat: " << threat_vis.cols << " , " << threat_vis.rows << std::endl;
    // std::cout << "top left coordinate: " << top_left_pixel.x << " , " << top_left_pixel.y << std::endl;
}