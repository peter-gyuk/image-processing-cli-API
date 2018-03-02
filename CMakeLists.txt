project(ip_api)
set(CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(src SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})
find_package( OpenCV REQUIRED )
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )

enable_testing()
add_test(test1 ip_api data/test1.png)
add_test(test_region ip_api data/test1.png FIND_REGION 58 125 1)
add_test(test_region_show ip_api data/test1.png DISPLAY_IMAGE FIND_REGION 58 125 1 DISPLAY_PIXELS)
add_test(test_region_perimeter ip_api data/test1.png FIND_REGION 58 125 1 FIND_PERIMETER SAVE_PIXELS out.png)
add_test(test_region_perimeter_2 ip_api data/test2.png FIND_REGION 150 100 1 FIND_PERIMETER SAVE_PIXELS out2.png)
add_test(test_smooth_perimeter_2 ip_api data/test3.png FIND_REGION 100 100 1 FIND_SMOOTH_PERIMETER 0.2 SAVE_PIXELS out_smooth_2.png)
add_test(test_smooth_perimeter_05 ip_api data/test3.png FIND_REGION 100 100 1 FIND_SMOOTH_PERIMETER 0.05 SAVE_PIXELS out_smooth_05.png)

