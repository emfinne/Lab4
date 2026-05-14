
#include "camera_pipeline/GaussianBlurNode.hpp"

GaussianBlurNode::GaussianBlurNode()

: Node("gaussian_blur")

{
    sub_ = this->create_subscription<sensor_msgs::msg::Image>(
        "image_raw",
        10,
        std::bind(&GaussianBlurNode::image_callback, this, std::placeholders::_1)
    );
    pub_ = this->create_publisher<sensor_msgs::msg::Image>(
        "output_image",
        10
    );
}

void GaussianBlurNode::image_callback(sensor_msgs::msg::Image::SharedPtr msg)
{
    cv::Mat cv_image;

    try {
        cv_image = cv_bridge::toCvCopy(msg, "bgr8")->image;
    } catch (const cv_bridge::Exception & e) {
        RCLCPP_ERROR(this->get_logger(), "Failed to convert image: %s", e.what());
        return;
    }

    cv::Mat blurred;
    cv::GaussianBlur(cv_image, blurred, cv::Size(15, 15), 0);

    auto blur_msg = cv_bridge::CvImage(msg->header, "bgr8", blurred).toImageMsg();
    pub_->publish(*blur_msg);
}



int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<GaussianBlurNode>());
    rclcpp::shutdown();
    return 0;
}