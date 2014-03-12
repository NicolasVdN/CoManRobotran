#
# author: Nicolas Van der Noot
# Feb 27 2014
#
# CMakeLists used to generate the executable in charge of automatically
# generating the optimization related files
#

# CMake minimum version
cmake_minimum_required(VERSION 2.8.7)

# project name
project (GEN_OPTI)

# message to display the project name
message(STATUS "Processing ${PROJECT_NAME}")

# use Release version and not the Debug one (faster)
set(CMAKE_BUILD_TYPE Release)

# main source project path (to print in 'cmake_config_opti.h') 
set (OPTI_PROJECT_ABS_PATH ${PROJECT_SOURCE_DIR})
set (OPTI_BINARY_ABS_PATH ${PROJECT_BINARY_DIR})

# get the name of the build fodler
get_filename_component(BUILD_FOLDER ${PROJECT_BINARY_DIR} PATH)
get_filename_component(BUILD_FOLDER ${BUILD_FOLDER} PATH)
get_filename_component(BUILD_FOLDER ${BUILD_FOLDER} PATH)
get_filename_component(BUILD_FOLDER ${BUILD_FOLDER} PATH)
get_filename_component(BUILD_FOLDER ${BUILD_FOLDER} NAME)

set (BUILD_FOLDER_NAME ${BUILD_FOLDER})

# for Unix: display all the warnings, except the ones related to /* -- */
if (UNIX)
  set(CMAKE_C_FLAGS "-g -Wall -Wno-comment")
endif (UNIX)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/src/cmake_config_opti.h.in"
  "${PROJECT_BINARY_DIR}/src/cmake_config_opti.h"
  )

# function to list all source files in the src/ directory, 
# recursing into sub-directories
function(list_gen_source_files HEADER_FILES)
    file(GLOB_RECURSE SOURCE_FILES_TMP "${PROJECT_SOURCE_DIR}/src/*.c" "${PROJECT_SOURCE_DIR}/src/*.cpp")

    set(SOURCE_FILES_TMP ${SOURCE_FILES_TMP} "${PROJECT_SOURCE_DIR}/../functions/automatic_generation/get_real_params_to_opt.c")
    
    set(SOURCE_FILES ${SOURCE_FILES_TMP} PARENT_SCOPE)
endfunction()

# function to list all paths to header files in the src/ directory, 
# recursing into sub-directories (includes)
function(list_gen_include_directories FULL_INCLUDE_DIRECTORIES)
    file(GLOB_RECURSE FULL_INCLUDE_DIRECTORIES_TMP RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${PROJECT_SOURCE_DIR}/src/*.h" "${PROJECT_SOURCE_DIR}/src/*.hpp")
    set(DIR_LIST "")
    foreach(FILE_PATH ${FULL_INCLUDE_DIRECTORIES_TMP})
        get_filename_component(DIR_PATH ${FILE_PATH} PATH)
        set(DIR_LIST ${DIR_LIST} ${DIR_PATH})
    endforeach(FILE_PATH)
    list(REMOVE_DUPLICATES DIR_LIST) 
    set(FULL_INCLUDE_DIRECTORIES ${DIR_LIST} PARENT_SCOPE)
endfunction()
 
# list source files to compile
list_gen_source_files(SOURCE_FILES)

# list include directories (to find headers)
list_gen_include_directories(FULL_INCLUDE_DIRECTORIES)

# include these directories
include_directories (${FULL_INCLUDE_DIRECTORIES})

# include the cmake_config header
include_directories (${PROJECT_BINARY_DIR}/src)

# Prepare the 'Results' folder
file(COPY ${PROJECT_SOURCE_DIR}/OptiParams/ DESTINATION ${CMAKE_BINARY_DIR}/Results)

# name of the executable: 'Gen_state_var'
set (Executable Gen_opti)

# generate the executable
add_executable (${Executable} ${SOURCE_FILES})

# automatically launch the executable
add_custom_target(CheckOpti ALL 
    COMMAND ${Executable})

# math external library (for Unix): linkage
if (UNIX)
	target_link_libraries (${Executable} m)
endif (UNIX)
