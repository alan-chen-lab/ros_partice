#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include<example/threshold_msg.h>
using namespace cv;

cv::Mat src, src_gray;
cv::Mat dst, detected_edges;
int lowThreshold = 0;
const int max_lowThreshold = 100;
const int ratio = 3;
const int kernel_size = 3;
const char* window_name = "canny image";


static void CannyThreshold(int, void*)
{
    blur( src_gray, detected_edges, Size(3,3) );
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
    dst = Scalar::all(0);
    src.copyTo( dst, detected_edges);
    imshow( window_name, dst );
}

void imageCallback(const sensor_msgs::ImageConstPtr& msg) // canny
{
  try
  {
    cv::imshow("origin_image", cv_bridge::toCvShare(msg, "bgr8")->image);
    src = cv_bridge::toCvShare(msg, "bgr8")->image;
    // canny
    dst.create( src.size(), src.type() );
    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
    CannyThreshold(0, 0);
    // canny

    cv::waitKey(30);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

void catch_low_th_value(const example::threshold_msg &msg)
{
    lowThreshold = msg.th_value;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_listener");
    ros::NodeHandle nh;
    cv::namedWindow("origin_image");

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("/image_pub", 1, imageCallback);

    ros::Subscriber sub_th = nh.subscribe("/low_threshold", 1, catch_low_th_value);

    ros::spin();
    cv::destroyWindow("origin_image");

    return 0;
}