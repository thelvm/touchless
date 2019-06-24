PROJECT(touchless-api)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
SET(CMAKE_CXX_STANDARD 17)

FIND_PACKAGE(Threads)
SET(PKG_MODULES
        glibmm-2.4
        giomm-2.4
        )

FIND_PACKAGE(PkgConfig REQUIRED)
pkg_check_modules(PKGS REQUIRED ${PKG_MODULES})

SET(GESTURE_PARSER_DIR ${CMAKE_CURRENT_SOURCE_DIR})
SET(LEAP_SDK_DIR /home/lucas/leapSDK/2.3.1)

SET(GESTURE_PARSER_SOURCES
        src/touchless.cpp
        src/Gesture.cpp
        src/GestureKeyframe.cpp
        src/GestureParser.cpp
        src/Hand.cpp
        src/Hands.cpp
        src/HandsParser.cpp
        src/DbusInterface.cpp

        dbus/touchless_gdbus_common.cpp
        dbus/touchless_gdbus_proxy.cpp
        dbus/touchless_gdbus_stub.cpp
        )

INCLUDE_DIRECTORIES(
        include
        ${LEAP_SDK_DIR}/include
        dbus
        ${PKGS_INCLUDE_DIRS}
)

LINK_LIBRARIES(
        ${LEAP_SDK_DIR}/lib/x64/libLeap.so
        ${PKGS_LIBRARIES}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

ADD_EXECUTABLE(tests src/example.cpp ${GESTURE_PARSER_SOURCES})

ADD_LIBRARY(touchless ${GESTURE_PARSER_SOURCES})

