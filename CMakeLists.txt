cmake_minimum_required (VERSION 3.1.0)
project(restbedcpp)
set(MYSQL_CONNECTOR_PATH "C:/Program Files/MySQL/Connector C++ 8.0")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
if(NOT CMAKE_CXX_COMPILE_FEATURES)
    message(FATAL_ERROR "The compiler does not support C++17.")
endif()
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()
# if (WIN32)
#     enable_language("RC")
#     set(WIN32_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/assets/resource.rc)
# endif()

find_package(unofficial-restbed CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE "${MYSQL_CONNECTOR_PATH}/include")
target_link_libraries(${PROJECT_NAME} PRIVATE "${MYSQL_CONNECTOR_PATH}/lib64/vs14/mysqlcppconn.lib")
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::restbed::restbed)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

configure_file(${MYSQL_CONNECTOR_PATH}/lib64/libcrypto-1_1-x64.dll ${CMAKE_BINARY_DIR}/Release/libcrypto-1_1-x64.dll COPYONLY)
configure_file(${MYSQL_CONNECTOR_PATH}/lib64/libssl-1_1-x64.dll ${CMAKE_BINARY_DIR}/Release/libssl-1_1-x64.dll COPYONLY)
configure_file(${MYSQL_CONNECTOR_PATH}/lib64/mysqlcppconn-9-vs14.dll ${CMAKE_BINARY_DIR}/Release/mysqlcppconn-9-vs14.dll COPYONLY)
# dynamic library import ^

if(EXISTS "${CMAKE_BINARY_DIR}/Release/libcrypto-1_1-x64.dll" AND
   EXISTS "${CMAKE_BINARY_DIR}/Release/libssl-1_1-x64.dll" AND
   EXISTS "${CMAKE_BINARY_DIR}/Release/mysqlcppconn-9-vs14.dll")
   
    install(FILES
        "${CMAKE_BINARY_DIR}/Release/libcrypto-1_1-x64.dll"
        "${CMAKE_BINARY_DIR}/Release/libssl-1_1-x64.dll"
        "${CMAKE_BINARY_DIR}/Release/mysqlcppconn-9-vs14.dll"
        DESTINATION bin
    )
else()
    message(FATAL_ERROR "DLL files not present in build dir.")
endif()






