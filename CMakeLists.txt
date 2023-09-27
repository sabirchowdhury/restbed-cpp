cmake_minimum_required(VERSION 3.0)

project(restbedcpp)
find_package(unofficial-restbed CONFIG REQUIRED)

add_executable(restbedcpp 
    main.cpp)

# target_link_libraries(main PRIVATE unofficial::restbed::restbed)
target_link_libraries(restbedcpp PRIVATE unofficial::restbed::restbed)
# target_link_libraries(CalculatorAPI restbed)
# target_include_directories(restbedcpp PUBLIC ${CMAKE_SOURCE_DIR}/include)
set_property(TARGET restbedcpp PROPERTY CXX_STANDARD 17)

