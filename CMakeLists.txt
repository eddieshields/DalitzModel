# CMakeLists.txt for DalitzModel module. 
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(PACKAGE DalitzModel)
project(${PACKAGE})

option(BUILD_TESTS "Build test programs" OFF)
option(BUILD_ROOT "Build with ROOT" OFF)

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

#--- Build tests.
if (BUILD_TESTS)
    add_executable(build_model ${CMAKE_SOURCE_DIR}/tests/build_model.cpp)
    target_link_libraries(build_model ${PACKAGE})
endif()

#--- Build with root.
if (BUILD_ROOT)
    # Tell CMake where to find ROOT.
    list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
    #--- Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
    find_package(ROOT REQUIRED COMPONENTS Core RIO Hist Graf Graf3d Postscript Gpad
                                 RooFit RooFitCore Tree MathCore Foam Physics
                                 Proof ProofBench ProofDraw ProofPlayer)

    #--- Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
    include(${ROOT_USE_FILE})
    include_directories(${ROOT_INCLUDE_DIRS})

    #--- Define the headers and src directories
    include_directories(${header_dir_list})
    file(GLOB_RECURSE headers include/*.h include/lineshapes/*h)

    ROOT_GENERATE_DICTIONARY(G__${PACKAGE} ${headers} LINKDEF dict/${PACKAGE}LinkDef.h)

    #--- Generate library with ROOT dictionary
    add_library(ROOT${PACKAGE} SHARED  G__${PACKAGE}.cxx)

    #--- Link
    target_link_libraries(ROOT${PACKAGE} ${ROOT_LIBRARIES} ${PACKAGE})

    if (BUILD_TESTS)
        add_executable(build_model_root ${CMAKE_SOURCE_DIR}/tests/build_model_root.cpp)
        target_link_libraries(build_model_root ROOT${PACKAGE})
    endif()
endif()