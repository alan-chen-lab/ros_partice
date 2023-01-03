### create the workspace
```
mkdir -p ~/your_ws_name/src
cd your_ws_name/src/
catkin_init_workspace
cd ..     
catkin_make

cd your_ws_name/src/
git clone....
cd ..
catkin_make
```
### run
```
1. roslaunch example practice_launch.launch
2. rosrun example pub_lowthreshold
```
### canny_opencv
1. [ROS_wiki] [1]
2. [ROS_wiki] [2]
3. [opencv_wiki] [3]

[1] :http://wiki.ros.org/image_transport/Tutorials/PublishingImages  
[2] :http://wiki.ros.org/image_transport/Tutorials/SubscribingToImages  
[3] :https://docs.opencv.org/3.4/da/d5c/tutorial_canny_detector.html  
