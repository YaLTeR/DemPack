cmake_minimum_required (VERSION 3.1)
project (DemPack)

if (NOT MSVC)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14 -march=native -mtune=native -Ofast -Wall -Wextra")
endif ()

add_subdirectory ("HLDemo")
include_directories ("HLDemo/src")

set (Boost_USE_STATIC_LIBS ON)
if (MSVC)
	find_package (Boost 1.57.0 REQUIRED COMPONENTS nowide)
else ()
	find_package (Boost 1.57.0 REQUIRED)
endif()
include_directories (${Boost_INCLUDE_DIR})

set (LIBRARY_OUTPUT_DIRECTORY ".")
set (SOURCE_FILES
	src/main.cpp
)

add_executable (DemPack ${SOURCE_FILES})
target_link_libraries (DemPack HLDemo ${Boost_LIBRARIES})
