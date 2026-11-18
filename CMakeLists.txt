cmake_minimum_required(VERSION 3.19)

project(SCAPMS VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Svg)

qt_standard_project_setup()

qt_add_executable(scapms
    main.cpp

    #--UTILS
    utils/Theme.h
    utils/ClinicException.h utils/ClinicException.cpp

    #--GUI
    gui/MainWindow.h gui/MainWindow.cpp gui/MainWindow.ui
    gui/LoginWindow.h gui/LoginWindow.cpp gui/LoginWindow.ui
    gui/components/PinInput.h gui/components/PinInput.cpp

    #--MODELS
    models/PatientRecord.h models/PatientRecord.cpp
    models/GeneralPatient.h models/GeneralPatient.cpp
    models/EmergencyPatient.h models/EmergencyPatient.cpp
    models/FollowUpPatient.h models/FollowUpPatient.cpp
    models/Appointable.h
    models/Appointment.h models/Appointment.cpp

    #--CONTROLLERS
    controllers/ClinicDatabase.h controllers/ClinicDatabase.cpp
)

target_include_directories(scapms PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(scapms PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)

set_target_properties(scapms PROPERTIES
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)

install(TARGETS scapms
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET scapms
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})