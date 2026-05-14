cmake_minimum_required(VERSION 3.8)
project(camera_pipeline)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(GaussianBlurNode
        src/GaussianBlurNode.cpp
)

add_executable(canny_edge
        src/canny_edge.cpp
)

target_include_directories(GaussianBlurNode PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(canny_edge PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(
        GaussianBlurNode
        rclcpp
        sensor_msgs
        cv_bridge
)

ament_target_dependencies(
        canny_edge
        rclcpp
        sensor_msgs
        cv_bridge
)

target_link_libraries(
        GaussianBlurNode
        ${OpenCV_LIBS}
)

target_link_libraries(
        canny_edge
        ${OpenCV_LIBS}
)

install(DIRECTORY include/
        DESTINATION include
)

install(TARGETS
        GaussianBlurNode
        canny_edge
        DESTINATION lib/${PROJECT_NAME}
)

install(
        DIRECTORY launch
        DESTINATION share/${PROJECT_NAME}
)

ament_package()