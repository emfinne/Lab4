from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([

        # Rectify node from image_proc — produces /image_rect from
        # image_raw + camera_info coming from Person A's camera node
        Node(
            package='image_proc',
            executable='rectify_node',
            name='rectify_node',
        ),

        # Gaussian blur node
        # Reads the calibrated image, publishes the blurred image
        Node(
            package='camera_pipeline',
            executable='GaussianBlurNode',
            name='gaussian_blur',
            remappings=[
                ('image_raw', 'image_rect'),
                ('output_image', 'image_blurred'),
            ],
        ),

        # Canny edge node
        # Reads the blurred image, publishes the final processed image
        Node(
            package='camera_pipeline',
            executable='canny_edge',
            name='canny_edge',
            remappings=[
                ('image_raw', 'image_blurred'),
                # output_image is left as-is — this is the final topic
            ],
        ),

    ])