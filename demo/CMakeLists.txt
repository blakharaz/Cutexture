#set(DEMO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/demo)

find_package(Qt5 COMPONENTS Core Widgets WebEngine WebEngineWidgets UiTools REQUIRED)

message("Using Qt version ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}.")

find_package(OGRE COMPONENTS Bites REQUIRED)

find_package(OIS REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CUTEXTURE_DEMO_SOURCES
    src/Core.cpp
    src/main.cpp
    src/SceneManager.cpp
    src/ViewManager.cpp
    src/Game.cpp
    src/OgreCore.cpp
    src/Settings.cpp)


AUX_SOURCE_DIRECTORY("src" CUTEXTURE_DEMO_SOURCES)

set(CUTEXTURE_DEMO_HEADERS
    include/Core.h
    include/Game.h
    include/SceneManager.h
    include/ViewManager.h
    include/OgreCore.h
    include/Settings.h
)

#qt5_wrap_cpp(CUTEXTURE_MOC_SOURCES ${CUTEXTURE_MOC_HEADERS})

######################################################################
# Configure application outputs									     #
######################################################################

add_executable(
    cutexture_demo ${CUTEXTURE_DEMO_SOURCES} ${CUTEXTURE_DEMO_HEADERS}
)

target_link_libraries(
    cutexture_demo cutexture OIS OgreBites Qt5::Core Qt5::Widgets Qt5::WebEngineWidgets Qt5::UiTools
)

target_include_directories(cutexture_demo PRIVATE include)


if(CMAKE_BUILD_TYPE MATCHES "Release")
	set(CUTEXTURE_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/output/bin/release)
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
	set(CUTEXTURE_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/output/bin/debug)
endif(CMAKE_BUILD_TYPE MATCHES "Release")

install(
        TARGETS cutexture_demo
	DESTINATION ${CUTEXTURE_INSTALL_DIR}
)

######################################################################
# Install configuration files									     #
######################################################################

if(WIN32)
	set(CUTEXTURE_OGRE_CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/configurations/ogre-plugins-win32.cfg)
elseif(UNIX)
	set(CUTEXTURE_OGRE_CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/configurations/ogre-plugins-unix.cfg)
endif(WIN32)

if(WIN32)
	set(CUTEXTURE_OGRE_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/configurations/ogre-resources-win32.cfg)
elseif(UNIX)
	set(CUTEXTURE_OGRE_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/configurations/ogre-resources-unix.cfg)
endif(WIN32)

install(FILES ${CUTEXTURE_OGRE_CONFIG}
	DESTINATION ${CUTEXTURE_INSTALL_DIR}
	RENAME plugins.cfg
)

install(FILES ${CUTEXTURE_OGRE_RESOURCES}
	DESTINATION ${CUTEXTURE_INSTALL_DIR}
	RENAME resources.cfg
)

install(FILES ui/game.ui
	DESTINATION ${CUTEXTURE_INSTALL_DIR}
)
