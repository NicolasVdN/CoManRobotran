#
# author: Nicolas Van der Noot
# Feb 27 2014
#
# CMakeLists used to compile the main sources files of the project
#

# list all source files to compile
list_source_files_c(SOURCE_FILES_C)

# list all directories where the header files are located (except the external ones)
list_full_include_directories(FULL_INCLUDE_DIRECTORIES)

# include the corresponding directories
include_directories (${FULL_INCLUDE_DIRECTORIES})

set(SOURCE_FILES ${SOURCE_FILES_C})

if (FLAG_CXX)
	list_source_files_cpp(SOURCE_FILES_CPP)
	set(SOURCE_FILES ${SOURCE_FILES} ${SOURCE_FILES_CPP})
endif (FLAG_CXX)

if (FLAG_OPTI)
	list_opti_files_c(OPTI_FILES_C)
	list_opti_files_cpp(OPTI_FILES_CPP)
	list_opti_include_directories(OPTI_INCLUDE_DIRECTORIES)

	set(SOURCE_FILES ${SOURCE_FILES} ${OPTI_FILES_C} ${OPTI_FILES_CPP})
	include_directories (${OPTI_INCLUDE_DIRECTORIES})

	set(SOURCE_FILES_CPP ${SOURCE_FILES_CPP} ${OPTI_FILES_CPP})
endif (FLAG_OPTI)

if (FLAG_BIOROB)
	list_biorob_files_cpp(BIOROB_FILES_CPP)
	set(SOURCE_FILES_CPP ${SOURCE_FILES_CPP} ${BIOROB_FILES_CPP})
	set(SOURCE_FILES ${SOURCE_FILES} ${BIOROB_FILES_CPP})
endif (FLAG_BIOROB)


# name of the executable: 'Exec'
if (FLAG_BIOROB)
	set (Executable dispatcher_opti)
else (FLAG_BIOROB)
	set (Executable Exec)
endif (FLAG_BIOROB)

# put the executable in the root of the build folder
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )

# generate the executable
add_executable (${Executable} ${SOURCE_FILES})

# math external library (for Unix): linkage
if (UNIX)
	target_link_libraries (${Executable} m)
endif (UNIX)

# Libxml2 external libray: linkage
target_link_libraries (${Executable} ${LIBXML2_LIBRARIES})

if (FLAG_REAL_TIME)

	# SDL external library: linkage
	if (FLAG_SDL)
		target_link_libraries (${Executable} ${SDL2_LIBRARIES})
		target_link_libraries (${Executable} ${SDL2TTF_LIBRARIES})
	endif (FLAG_SDL)

	# JNI external library: linkage
	if (FLAG_JNI)
		target_link_libraries (${Executable} ${JNI_LIBRARIES})
	endif (FLAG_JNI)

endif (FLAG_REAL_TIME)

# Simbody
if (FLAG_SIMBODY)
	target_link_libraries (${Executable} ${SIMBODY_LIBRARIES})
endif(FLAG_SIMBODY)

# YARP
if (FLAG_YARP)
    #TARGET_LINK_LIBRARIES(${Executable} ${YARP_LIBRARIES} ${ACE_LIBRARIES} curl) 
    TARGET_LINK_LIBRARIES(${Executable} ${YARP_LIBRARIES} ${ACE_LIBRARIES}) 
endif (FLAG_YARP)

# files compiled as C++ files
if (FLAG_CXX)
	set_source_files_properties(${SOURCE_FILES_CPP} PROPERTIES LANGUAGE CXX )
endif (FLAG_CXX)

