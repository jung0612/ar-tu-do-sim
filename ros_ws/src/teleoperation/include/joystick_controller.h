#pragma once

#include <ros/ros.h>

#include <chrono>
#include <drive_msgs/drive_param.h>
#include <sensor_msgs/Joy.h>
#include <string>


constexpr const char* PARAMETER_GAMEPAD_TYPE = "joystick_type";
constexpr const char* TOPIC_DRIVE_PARAMETERS = "input/drive_param/joystick";
constexpr const char* TOPIC_DMS = "/set/dms";

/**
 * @brief scales the absolute acceleration provided by the joystick.
 * Useful if the car should not drive with 100% speed if acceleration button is fully pressed
 */
constexpr float ACCELERATION_SCALING_FACTOR = 0.1f;

/**
 * @brief scales the absolute deceleration provided by the joystick.
 * Useful if the car should not decelerate with 100% speed if deceleration button is fully pressed
 */
constexpr float DECELERATION_SCALING_FACTOR = 0.1f;

/**
 * @brief scales the absolute steering value (between -1 and 1) provided by the joystick.
 * Useful if the car should not steer 100% left and right
 */
constexpr float STEERING_SCALING_FACTOR = 0.8f;

class JoystickController
{
    struct JoystickMapping
    {
        int steeringAxis;
        int accelerationAxis;
        int decelerationAxis;
        int deadMansSwitchButton;
    };

    const struct JoystickMapping joystick_mapping_ps3 = { 0, 13, 12, 14 };
    const struct JoystickMapping joystick_mapping_xbox360 = { 0, 4, 5, 0 };
    const struct JoystickMapping joystick_mapping_xboxone = { 0, 5, 2, 0 };

    public:
    JoystickController();

    private:
    ros::NodeHandle m_node_handle;
    ros::Publisher m_drive_parameter_publisher;
    ros::Subscriber m_joystick_subscriber;
    ros::Publisher m_dms_publisher;

    std::string m_joystick_type = "";

    JoystickMapping m_joystick_map;

    void joystickCallback(const sensor_msgs::Joy::ConstPtr& joystick);
    void publishDriveParameters(double velocity, double steering_angle);
};
