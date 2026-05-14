//
// Created by parallels on 5/14/26.
//

int main(int argc, char **argv) {

    rclcpp::init(argc, argv);


        auto gaus_node = std::make_shared<GaussianBlurNode>();


        rclcpp::executors::SingleThreadedExecutor executor;
        executor.add_node(node);
        std::thread spinner([&executor]() { executor.spin(); });

        executor.add_node(coordinator_node);
        executor.spin();


    rclcpp::shutdown();
    return 0;
}