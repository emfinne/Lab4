
#ifndef LAB4_GAUSSIANBLURNODE_HPP
#define LAB4_GAUSSIANBLURNODE_HPP


#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"
#include <opencv2/opencv.hpp>
class GaussianBlurNode  : public rclcpp::Node
{
    public:
    GaussianBlurNode();



    private:
};

#endif //LAB4_GAUSSIANBLURNODE_HPP
