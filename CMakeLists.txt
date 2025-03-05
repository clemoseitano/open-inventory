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

# Automatically include all source and header files from the models and ui directories
file(GLOB MODEL_SOURCES "models/*.cpp" "models/*.h")
file(GLOB UI_SOURCES "ui/**/*.cpp" "ui/**/*.h" "ui/**/*.ui")

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    database.h
    usersession.h
    ${MODEL_SOURCES}
    ${UI_SOURCES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Sales
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc
        ui/shop/createproductdialog.h ui/shop/createproductdialog.cpp ui/shop/createproductdialog.ui
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

# Now that 'Sales' is defined, specify include directories
target_include_directories(Sales PRIVATE
    ${CMAKE_SOURCE_DIR}/models
    ${CMAKE_SOURCE_DIR}/ui
)

target_link_libraries(Sales PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
)

set_target_properties(Sales PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Sales
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Sales)
endif()
