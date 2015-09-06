cmake_minimum_required(VERSION 2.8.3)
project(uhf_rfid_api)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)
## Generate messages in the 'msg' folder
add_message_files(
   FILES
   UhfRfid.msg
)

 generate_messages(
   DEPENDENCIES
   std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES uhf_rfid_api
  CATKIN_DEPENDS message_runtime
)



include_directories(include include/uhf_rfid_api)
include_directories(  ${catkin_INCLUDE_DIRS})


add_library(uhf_rfid_api   src/uhf_rfid_api.cpp)

target_link_libraries(uhf_rfid_api )

add_executable(uhf_single_tag src/uhf_inventory_single_tag.cpp)

target_link_libraries(uhf_single_tag uhf_rfid_api  ${catkin_LIBRARIES})

add_executable(reader src/uhf_reader.cpp)
target_link_libraries(reader ${catkin_LIBRARIES})
add_dependencies(reader beginner_tutorials_gencpp)





