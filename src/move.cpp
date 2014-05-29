#include "ros/ros.h"
#include "robodeck_msgs/connect.h"
#include "robodeck_msgs/move.h"
#include "robodeck_msgs/disconnect.h"
#include <cstdlib>
 
int main(int argc, char **argv) {
	ros::init(argc, argv, "move_test");
	ros::NodeHandle n;
	
	ros::ServiceClient connectService = n.serviceClient<robodeck_msgs::connect>("robodeck/connect");
	robodeck_msgs::connect connectSrv;
	connectSrv.request.ip = "192.168.1.1";
	connectSrv.request.port = 2000;

	if (connectService.call(connectSrv)){
		if (connectSrv.response.isConnected) {
			ROS_INFO("Conectou-se ao robo!");
			
			ros::ServiceClient moveService = n.serviceClient<robodeck_msgs::move>("robodeck/move");
			robodeck_msgs::move moveSrv;
			moveSrv.request.intensity = 32767;
			
			if (moveService.call(moveSrv)) {
				if (moveSrv.response.executed) {
					ROS_INFO("Robo movimentou!");
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
