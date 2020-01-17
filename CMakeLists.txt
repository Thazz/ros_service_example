cmake_minimum_required(VERSION 2.8.3)
project(ros_service_example)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  message_generation
  roscpp
  std_msgs
)

## Generate services in the 'srv' folder
 add_service_files(
   FILES
   AddNumbers.srv
   ReverseString.srv
 )

## Generate actions in the 'action' folder
 add_action_files(
   DIRECTORY 
    action
   FILES
    CountTo.action
 )

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
     actionlib_msgs 
     std_msgs
 )

catkin_package(
#  INCLUDE_DIRS include
  CATKIN_DEPENDS 
    actionlib 
    actionlib_msgs
    message_generation 
    roscpp 
    std_msgs 
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${smartgv_utils_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)

# Services
add_executable(ex_add_numbers src/add_numbers.cpp)
add_dependencies(ex_add_numbers ${catkin_EXPORTED_TARGETS} ros_service_example_gencpp)
target_link_libraries(ex_add_numbers ${catkin_LIBRARIES})
set_target_properties(ex_add_numbers  PROPERTIES OUTPUT_NAME add_numbers)

add_executable(ex_reverse_string src/reverse_string.cpp)
add_dependencies(ex_reverse_string  ${catkin_EXPORTED_TARGETS} ros_service_example_gencpp) 
target_link_libraries(ex_reverse_string ${catkin_LIBRARIES})
set_target_properties(ex_reverse_string  PROPERTIES OUTPUT_NAME reverse_string)

add_executable(ex_count_to src/count_to.cpp)
add_dependencies(ex_count_to ${catkin_EXPORTED_TARGETS} ros_service_example_gencpp)
target_link_libraries(ex_count_to ${catkin_LIBRARIES})
set_target_properties(ex_count_to  PROPERTIES OUTPUT_NAME count_to)

# Install
install(TARGETS ex_add_numbers ex_reverse_string ex_count_to
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY config launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)