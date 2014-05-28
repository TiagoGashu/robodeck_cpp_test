#include "ros/ros.h"
#include "robodeck_msgs/connect.h"
#include "robodeck_msgs/move.h"
#include <cstdlib>
 
int main(int argc, char **argv) {
	ros::init(argc, argv, "robodeck_cpp_test");
	if (argc != 3){
		ROS_INFO("usage: add_two_ints_client X Y");
		return 1;
	}
 
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
		}
	}else{
		ROS_ERROR("Failed to call service connect");
		return 1;
	}

	return 0;
}
