/*
 * quad_flattraj.h
 *
 *  Created on: Aug 29, 2016
 *      Author: rdu
 */

#ifndef PLANNING_SRC_POLYOPT_QUAD_FLATTRAJ_H_
#define PLANNING_SRC_POLYOPT_QUAD_FLATTRAJ_H_

#include <cstdint>

#include "lcmtypes/srcl_ctrl.hpp"

#include "polyopt/poly_curve.h"

namespace srcl_ctrl {

typedef struct {
	double x;
	double y;
	double z;
	double yaw;
}QuadFlatOutput;

typedef struct {
	PolyCurve seg_x;
	PolyCurve seg_y;
	PolyCurve seg_z;
	PolyCurve seg_yaw;

	double t_start;
	double t_end;

	void print()
	{
		seg_x.print();
		seg_y.print();
		seg_z.print();
		seg_yaw.print();
	}
}QuadFlatOutputSeg;

class QuadFlatTraj {
public:
	QuadFlatTraj()=default;
	~QuadFlatTraj()=default;

public:
	std::vector<QuadFlatOutputSeg> traj_segs_;

public:
	void AddTrajSeg(const std::vector<std::vector<double>>& seg_coeffs, double ts, double te)
	{
		if(seg_coeffs.size() != 4) {
			std::cerr << "data incomplete, failed to add trajectory segment" << std::endl;
			return;
		}

		QuadFlatOutputSeg seg;
		seg.seg_x = PolyCurve(seg_coeffs[0], true, ts, te, "x");
		seg.seg_y = PolyCurve(seg_coeffs[1], true, ts, te, "y");
		seg.seg_z = PolyCurve(seg_coeffs[2], true, ts, te, "z");
		seg.seg_yaw = PolyCurve(seg_coeffs[3], true, ts, te, "yaw");

		seg.t_start = ts;
		seg.t_end = te;

		traj_segs_.push_back(seg);
	}

	QuadFlatOutput GetTrajPointPos(double t)
	{
		QuadFlatOutput state;

		if(t < traj_segs_.front().t_start)
		{
			state.x = traj_segs_.front().seg_x.GetCurvePointPos(t);
			state.y = traj_segs_.front().seg_y.GetCurvePointPos(t);
			state.z = traj_segs_.front().seg_z.GetCurvePointPos(t);
			state.yaw = traj_segs_.front().seg_yaw.GetCurvePointPos(t);
		}
		else if(t > traj_segs_.back().t_end)
		{
			state.x = traj_segs_.back().seg_x.GetCurvePointPos(t);
			state.y = traj_segs_.back().seg_y.GetCurvePointPos(t);
			state.z = traj_segs_.back().seg_z.GetCurvePointPos(t);
			state.yaw = traj_segs_.back().seg_yaw.GetCurvePointPos(t);
		}
		else
		{
			// TODO here assumes the trajectory is continuous
			for(auto& seg:traj_segs_)
			{
				if(t >= seg.t_start && t <= seg.t_end)
				{
					state.x = seg.seg_x.GetCurvePointPos(t);
					state.y = seg.seg_y.GetCurvePointPos(t);
					state.z = seg.seg_z.GetCurvePointPos(t);
					state.yaw = seg.seg_yaw.GetCurvePointPos(t);

					break;
				}
			}
		}

		return state;
	}

	void clear() { traj_segs_.clear(); traj_segs_.resize(0); };
	void print()
	{
		std::cout << "\n######################################################################"<< std::endl;
		uint32_t idx = 0;
		for(auto& seg:traj_segs_)
		{
			std::cout << "\n-----> segment " << idx++ << std::endl;
			seg.print();
		}
	}
};

}


#endif /* PLANNING_SRC_POLYOPT_QUAD_FLATTRAJ_H_ */
