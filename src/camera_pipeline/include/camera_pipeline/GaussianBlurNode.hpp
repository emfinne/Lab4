
#ifndef LAB4_GAUSSIANBLURNODE_HPP
#define LAB4_GAUSSIANBLURNODE_HPP


#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <cv_bridge/cv_bridge.hpp>
#include <opencv2/opencv.hpp>



class GaussianBlurNode  : public rclcpp::Node
{
    public:
    GaussianBlurNode();



    private:

    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg);
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_;
};

#endif //LAB4_GAUSSIANBLURNODE_HPP
