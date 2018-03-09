/* 
 * rc_tamiya_sim_client.hpp
 * 
 * Created on: Aug 10, 2017
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#ifndef RC_TAMIYA_SIM_CLIENT_HPP
#define RC_TAMIYA_SIM_CLIENT_HPP

#include <cstdint>

#include "common/librav_types.hpp"

#include "rc_tamiya_sim/rc_tamiya_sim_types.hpp"
#include "vrep_interface/vrep_sim_client.hpp"

namespace librav
{

class RCTamiyaSimClient : public VrepSimClient<DataFromRCTamiyaSim, DataToRCTamiyaSim>
{
  public:
	RCTamiyaSimClient();
	~RCTamiyaSimClient();

	virtual bool ReceiveDataFromSimRobot(DataFromRCTamiyaSim *rdata) override;
	virtual void UpdateCtrlLoop(const DataFromRCTamiyaSim &rdata, DataToRCTamiyaSim *rcmd) override;
	virtual void SendDataToSimRobot(const DataToRCTamiyaSim &rcmd) override;

  private:
	simxInt car_handle_;
	simxInt camera_handle_;
	simxInt steering_right_;
	simxInt steering_left_;
	simxInt driving_front_right_;
	simxInt driving_front_left_;
	simxInt driving_rear_right_;
	simxInt driving_rear_left_;

	float body_lin_vel_[3];
	float body_ang_vel_[3];
	float body_vel_;

	float driving_right_vel_;
	float driving_left_vel_;
	float steering_angle_;
	float steering_vel_;

	simxUChar *image_raw_;
	int img_res[2];

	virtual void ConfigDataStreaming(void) override;

	bool GetCarDrivingVel(float &rvel, float &lvel, float &body_vel);
	bool GetCarSteeringAngle(float &data);
	bool GetVisionImage(simxUChar img[IMG_RES_Y][IMG_RES_X]);

	void SetCarSteeringAngle(float cmd);
	void SetCarSteeringVelocity(float cmd);
	void SetCarDrivingVel(float cmd);

};
}

#endif /* RC_TAMIYA_SIM_CLIENT_HPP */