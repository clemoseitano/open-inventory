cmake_minimum_required(VERSION 3.16)

project(Sales VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the architecture to arm64 for macOS (Apple Silicon)
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_OSX_ARCHITECTURES "arm64")
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Sql Widgets Xml)

# Automatically include all source and header files from the models and sql directories
file(GLOB MODEL_SOURCES "models/*.cpp" "models/*.h", "usersession.h")

# Include the generated .qrc file in the project sources
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    database.h
    usersession.h
    ${MODEL_SOURCES}   # Include all model source and header files
)

include_directories(${CMAKE_SOURCE_DIR}/models)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Sales
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            resources.qrc
            ui/auth/logindialog.cpp ui/auth/logindialog.h ui/auth/logindialog.ui ui/auth/signupdialog.cpp ui/auth/signupdialog.h
            ui/auth/signupdialog.h ui/auth/signupdialog.cpp ui/auth/signupdialog.ui
            ui/shop/shopselectiondialog.h ui/shop/shopselectiondialog.cpp ui/shop/shopselectiondialog.ui
            ui/shop/shopitem.h ui/shop/shopitem.cpp
            ui/shop/createshopwizard.h ui/shop/createshopwizard.cpp ui/shop/createshopwizard.ui
            ui/shop/emptystatewidget.h ui/shop/emptystatewidget.cpp ui/shop/emptystatewidget.ui

    )
else()
    if(ANDROID)
        add_library(Sales SHARED
                ${PROJECT_SOURCES}
        )
    else()
        add_executable(Sales
                ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Sales PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Sql
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Xml
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Sales)
endif()

set_target_properties(Sales PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Sales
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Sales)
endif()
