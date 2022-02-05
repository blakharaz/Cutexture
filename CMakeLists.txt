######################################################################
# Build system for Cutexture										 #
######################################################################

project(Cutexture)
cmake_minimum_required(VERSION 3.18)
set(CMAKE_MODULE_PATH "${CMAKE_ROOT}/Modules;${CMAKE_CURRENT_SOURCE_DIR}/cmake")

######################################################################
# Configure Dependencies													     #
######################################################################

# Find QT and provide a hint on where it might be
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

message("Using Qt version ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}.")

find_package(OGRE REQUIRED)

find_package(OIS REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


######################################################################
# Configure includes											     #
######################################################################

set(CUTEXTURE_INCLUDE_DIR 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

######################################################################
# Configure sources                                                  #
######################################################################

set(CUTEXTURE_SOURCES src/Exception.cpp src/InputManager.cpp src/UiManager.cpp)
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/src" CUTEXTURE_SOURCES)

set(CUTEXTURE_MOC_HEADERS
    ${CUTEXTURE_INCLUDE_DIR}/UiManager.h
    ${CUTEXTURE_INCLUDE_DIR}/InputManager.h
)

######################################################################
# Configure application outputs                                      #
######################################################################

add_library(
        cutexture SHARED ${CUTEXTURE_SOURCES} ${CUTEXTURE_MOC_SOURCES} ${CUTEXTURE_MOC_HEADERS}
)

target_link_libraries(cutexture OgreMain Qt::Core)
target_include_directories(cutexture PUBLIC ${CUTEXTURE_INCLUDE_DIR})

install(
	TARGETS cutexture
	LIBRARY DESTINATION ${CUTEXTURE_INSTALL_DIR}
)

######################################################################
# Configure unit tests                                               #
######################################################################

#include(src/tests/CMakeLists.txt)

######################################################################
# Configure demo project                                             #
######################################################################

add_subdirectory(demo)
