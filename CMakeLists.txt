cmake_minimum_required(VERSION 3.16)

project(BLT-GUI-Maker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick SerialBus REQUIRED)

qt_add_executable(appBLT-GUI-Maker
    main.cpp
    FrameHandler.hpp FrameHandler.cpp
    Sensor.hpp Sensor.cpp SensorObjectDefinitions.hpp
    Valve.hpp Valve.cpp ValveObjectDefinitions.hpp
    GNCThread.hpp GNCThread.cpp
    Controller.hpp Controller.cpp


    QMLtestclass.hpp QMLtestclass.cpp
)

qt_add_qml_module(appBLT-GUI-Maker
    URI BLT-GUI-Maker
    VERSION 1.0
    QML_FILES main.qml 
    SOURCES FrameHandler.hpp FrameHandler.cpp
    Sensor.hpp Sensor.cpp SensorObjectDefinitions.hpp
    Valve.hpp Valve.cpp ValveObjectDefinitions.hpp
    GNCThread.hpp GNCThread.cpp
    Controller.hpp Controller.cpp


    QMLtestclass.hpp QMLtestclass.cpp

)

set_target_properties(appBLT-GUI-Maker PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appBLT-GUI-Maker
    PRIVATE Qt6::Quick Qt6::SerialBus)

install(TARGETS appBLT-GUI-Maker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
