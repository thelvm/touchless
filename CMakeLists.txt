PROJECT(touchless)
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
SET(CMAKE_CXX_STANDARD 17)

SET(PKG_MODULES
        glibmm-2.4
        giomm-2.4
        )

FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(PkgConfig REQUIRED)
pkg_check_modules(PKGS ${PKG_MODULES} REQUIRED)

if (NOT EXISTS $ENV{LEAP_SDK_DIR})
    message(SEND_ERROR "LEAP_SDK_DIR invalid or not set.")
else ()
    message(STATUS "LeapSDK root folder set to " $ENV{LEAP_SDK_DIR})
endif ()

SET(API_SOURCES
        src/api/touchless.cpp
        src/api/Gesture.cpp
        src/api/GestureKeyframe.cpp
        src/api/GestureParser.cpp
        src/api/Hand.cpp
        src/api/Hands.cpp
        src/api/HandsParser.cpp
        )

set(DBUS_SOURCES
        dbus/touchless_gdbus_common.cpp
        dbus/touchless_gdbus_proxy.cpp
        dbus/touchless_gdbus_stub.cpp
        )

set(GESTURE_MANAGER_SOURCES
        ${API_SOURCES}
        src/gesture-manager/main.cpp
        src/gesture-manager/commands.cpp)

set(DAEMON_SOURCES
        ${API_SOURCES}
        src/daemon/main.cpp
        )

INCLUDE_DIRECTORIES(
        include/api
        include/daemon
        include/gesture-manager
        $ENV{LEAP_SDK_DIR}/include
        dbus
        ${PKGS_INCLUDE_DIRS}
)

LINK_LIBRARIES(
        $ENV{LEAP_SDK_DIR}/lib/x64/libLeap.so
        ${PKGS_LIBRARIES}
        stdc++fs
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_executable(gesture-manager ${GESTURE_MANAGER_SOURCES})
add_executable(daemon ${DBUS_SOURCES} ${DAEMON_SOURCES})
