# CMakeLists.txt for DalitzModel module. 
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(PACKAGE DalitzModel)
project(${PACKAGE})

option(BUILD_TESTS "Build test programs" OFF)

#--- Ensure C++17.
set (CMAKE_CXX_STANDARD 17)

#--- define macros
MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

#--- Create header only library.
add_library(${PACKAGE} INTERFACE)

#--- Get recursive directories.
HEADER_DIRECTORIES(header_dir_list)

#--- Include headers in library.
target_include_directories(${PACKAGE} INTERFACE ${header_dir_list})

if (BUILD_TESTS)
    add_executable(build_model ${CMAKE_SOURCE_DIR}/tests/build_model.cpp)
    target_link_libraries(build_model ${PACKAGE})
endif()