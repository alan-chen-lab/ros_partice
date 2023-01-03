#include<ros/ros.h>
#include<stdio.h>
#include<stdlib.h>
#include<example/threshold_msg.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pub_low_threshold");
    ros::NodeHandle nh;

    ros::Publisher pub_low = nh.advertise<example::threshold_msg>("/low_threshold", 1);
    ros::Rate loop_rate(30);

    example::threshold_msg msg;
    int low_th;
    while (nh.ok())
    {
        printf("input value of the threshold: ");
        scanf("%d", &low_th);
        msg.th_value = low_th;
        pub_low.publish(msg);
        ROS_INFO("published : [%d]", low_th);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}