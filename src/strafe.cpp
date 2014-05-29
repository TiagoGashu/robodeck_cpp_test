#include "ros/ros.h"
#include "robodeck_msgs/connect.h"
#include "robodeck_msgs/strafe.h"
#include "robodeck_msgs/disconnect.h"
#include <cstdlib>
 
int main(int argc, char **argv) {
	ros::init(argc, argv, "strafe_test");
	ros::NodeHandle n;
	
	ros::ServiceClient connectService = n.serviceClient<robodeck_msgs::connect>("robodeck/connect");
	robodeck_msgs::connect connectSrv;
	connectSrv.request.ip = "192.168.1.1";
	connectSrv.request.port = 2000;

	if (connectService.call(connectSrv)){
		if (connectSrv.response.isConnected) {
			ROS_INFO("Conectou-se ao robo!");
			
			ros::ServiceClient strafeService = n.serviceClient<robodeck_msgs::strafe>("robodeck/strafe");
			robodeck_msgs::strafe strafeSrv;
			strafeSrv.request.intensity = 15000;
			strafeSrv.request.curvature = 30;
			
			if (strafeService.call(strafeSrv)) {
				if (strafeSrv.response.executed) {
					ROS_INFO("O robô realizou um strafe!");
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
