# README

![](https://github.com/Thazz/ros_service_example/workflows/CI/badge.svg) [![CircleCI](https://circleci.com/gh/Thazz/ros_service_example.svg?style=shield)](https://circleci.com/gh/Thazz/ros_service_example)

## ros\_service\_example

Example nodes for ROS service and action server

### Service

#### Add numbers:

Accepts list of \(float\) numbers and returns their sum

```text
roslaunch ros_service_example add_numbers.launch
```

To call service from command line use `rosservice call add_numbers [1,2,3,4,5.02]`

#### Reverse string

Accepts string and returns reversed string

```text
roslaunch ros_service_example reverse_string.launch
```

To call service from command line use `rosservice call reverse_string 'The quick brown fox jumps over the lazy dog'`

### Action server

Accepts number as goal and counts to that number \(e.g 24\). During feedback returns current count \(1, 2, 3, ...\) and as result final number \(24\).

```text
roslaunch ros_service_example count_to.launch
```

