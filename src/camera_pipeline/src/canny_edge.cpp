#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"

#include "cv_bridge/cv_bridge.hpp"
#include "opencv2/imgproc.hpp"


class CannyEdgeNode : public rclcpp::Node
{
public:
    CannyEdgeNode()
    : Node("canny_edge")
    {
        subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
          "image_raw",
          10,
          std::bind(&CannyEdgeNode::image_callback, this, std::placeholders::_1)
        );

        publisher_ = this->create_publisher<sensor_msgs::msg::Image>(
          "output_image",
          10
        );
    }

private:
    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        cv::Mat cv_image;

        try {
            cv_image = cv_bridge::toCvCopy(msg, "bgr8")->image;
        } catch (const cv_bridge::Exception & e) {
            RCLCPP_ERROR(this->get_logger(), "Failed to convert image: %s", e.what());
            return;
        }

        cv::Mat gray;
        cv::cvtColor(cv_image, gray, cv::COLOR_BGR2GRAY);

        cv::Mat edges;
        cv::Canny(gray, edges, 100, 200);

        cv::Mat cv_edge;
        cv::cvtColor(edges, cv_edge, cv::COLOR_GRAY2BGR);

        auto edge_msg = cv_bridge::CvImage(
          msg->header,
          "bgr8",
          cv_edge
        ).toImageMsg();

        publisher_->publish(*edge_msg);
    }

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
};


int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CannyEdgeNode>());
    rclcpp::shutdown();
    return 0;
}