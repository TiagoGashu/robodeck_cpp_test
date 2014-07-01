#include "ros/ros.h"
#include "robodeck_msgs/connect.h"
#include "robodeck_msgs/readOpticalSensor.h"
#include "robodeck_msgs/disconnect.h"
#include <cstdlib>
#include <iostream>
 
int main(int argc, char **argv) {
	ros::init(argc, argv, "readoptical_test");
	ros::NodeHandle n;
	
	ros::ServiceClient connectService = n.serviceClient<robodeck_msgs::connect>("robodeck/connect");
	robodeck_msgs::connect connectSrv;
	connectSrv.request.ip = "192.168.1.1";
	connectSrv.request.port = 2000;

	if (connectService.call(connectSrv)){
		if (connectSrv.response.isConnected) {
			ROS_INFO("Conectou-se ao robo!");
			
			ros::ServiceClient readOpticalService = n.serviceClient<robodeck_msgs::readOpticalSensor>("robodeck/opticalSensor/read");
			robodeck_msgs::readOpticalSensor readOpticalSrv;
			
			if (readOpticalService.call(readOpticalSrv)) {
				if (readOpticalSrv.response.reading) {
					ROS_INFO("AE");
				}
			}
			ros::ServiceClient disconnectService = n.serviceClient<robodeck_msgs::disconnect>("robodeck/disconnect");
			robodeck_msgs::disconnect disconnectSrv;
			if (disconnectService.call(disconnectSrv)) {
				if (disconnectSrv.response.isDisconnected) {
					ROS_INFO("Desconectou-se do robô com sucesso!");
				}
				else {
					ROS_INFO("Problema ao tentar desconectar");
				}
			}
		}
	}else{
		ROS_ERROR("Falha ao tentar conectar-se ao robô");
		return 1;
	}

	return 0;
}
