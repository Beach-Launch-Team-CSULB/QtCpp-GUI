cmake_minimum_required(VERSION 3.16)

project(BLT-Theseus-GUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Core Quick QuickControls2 Qml Gui SerialBus Charts Multimedia)

qt_standard_project_setup()

qt_add_executable(appBLT-Theseus-GUI
    main.cpp
    DirHelper.hpp DirHelper.cpp
    FrameHandler.hpp FrameHandler.cpp
    Sensor.hpp Sensor.cpp SensorObjectDefinitions.hpp
    HPSensor.hpp HPSensor.cpp HPSensorObjectDefinitions.hpp
    LoadCellSensor.hpp LoadCellSensor.cpp LoadCellSensorObjectDefinitions.hpp
    Valve.hpp Valve.cpp ValveObjectDefinitions.hpp
    Autosequence.hpp Autosequence.cpp AutosequenceObjectDefinitions.hpp
    Thermocouple.hpp Thermocouple.cpp ThermocoupleObjectDefinitions.hpp
    GNCThread.hpp GNCThread.cpp
    EngineController.hpp EngineController.cpp EngineControllerObjectDefinitions.hpp
    TankPressController.hpp TankPressController.cpp TankPressControllerObjectDefinitions.hpp
    Node.hpp

    Logger.hpp Logger.cpp
)

qt_add_qml_module(appBLT-Theseus-GUI
    URI BLT-Theseus-GUI
    VERSION 1.0
    QML_FILES   Main.qml MainPage1.qml MainPage2.qml MainPage3.qml
                StatusBar.qml
                GraphQML.qml HPSensorQML.qml SensorQML.qml ValveQML.qml AutosequenceButton.qml
                Tab.qml CountdownTimerQML.qml AutosequenceQML.qml VehicleStateQML.qml TankStateQML.qml EngineControllerStateQML.qml
)

set_target_properties(appBLT-Theseus-GUI PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appBLT-Theseus-GUI
    PRIVATE Qt6::Core Qt6::Quick Qt6::Qml Qt6::Gui Qt6::SerialBus Qt6::Charts Qt6::Multimedia Qt6::QuickControls2
)

install(TARGETS appBLT-Theseus-GUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
