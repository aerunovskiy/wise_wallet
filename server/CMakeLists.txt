cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project( server )

find_package(Boost REQUIRED COMPONENTS
        program_options
)

set(CMAKE_CXX_STANDARD 20)

include( ${CMAKE_CURRENT_LIST_DIR}/src/src.cmake )

add_executable( ${PROJECT_NAME} ${SRC} )

target_link_libraries( ${PROJECT_NAME} PRIVATE
        Boost::program_options
)