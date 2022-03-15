#set(DEMO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/demo)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Qml QUIET)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Qml REQUIRED)

message("Using Qt version ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}.")

find_package(OGRE COMPONENTS Bites REQUIRED)

find_package(OIS REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CUTEXTURE_QMLDEMO_SOURCES
    src/Core.cpp
    src/main.cpp
    src/SceneManager.cpp
    src/ViewManager.cpp
    src/Game.cpp
    src/OgreCore.cpp
    src/Settings.cpp
    qml/qml.qrc
)


AUX_SOURCE_DIRECTORY("src" CUTEXTURE_QMLDEMO_SOURCES)

set(CUTEXTURE_QMLDEMO_HEADERS
    include/Core.h
    include/Game.h
    include/SceneManager.h
    include/ViewManager.h
    include/OgreCore.h
    include/Settings.h
)

######################################################################
# Configure application outputs									     #
######################################################################

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(cutexture_qmldemo
        MANUAL_FINALIZATION
        ${CUTEXTURE_QMLDEMO_SOURCES} ${CUTEXTURE_QMLDEMO_HEADERS}
    )
else()
    add_executable(
        cutexture_qmldemo ${CUTEXTURE_QMLDEMO_SOURCES} ${CUTEXTURE_QMLDEMO_HEADERS}
    )
endif()

target_link_libraries(
    cutexture_qmldemo PRIVATE cutexture OIS OgreBites Qt::Core Qt::Quick Qt::Qml
)

target_include_directories(cutexture_qmldemo PRIVATE include)


if(CMAKE_BUILD_TYPE MATCHES "Release")
	set(CUTEXTURE_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/output/bin/release)
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
	set(CUTEXTURE_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/output/bin/debug)
endif(CMAKE_BUILD_TYPE MATCHES "Release")

install(
        TARGETS cutexture_qmldemo
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

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(cutexture_qmldemo)
    qt_finalize_executable(cutexture_qmldemo)
endif()
