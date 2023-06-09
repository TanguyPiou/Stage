cmake_minimum_required(VERSION 3.5)

project(LaGuerreDesTortues LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)


set(PROJECT_SOURCES
        main.cpp
        Arene.cpp
        Arene.hpp
        Tortue.cpp
        Tortue.hpp
        res.qrc
        IA.hpp
        IA.cpp
        Joueur.hpp
        Joueur.cpp
        IAleatoire.hpp
        IAleatoire.cpp

        formmode.cpp
        formmode.hpp
        formmode.ui
        formnbj.cpp
        formnbj.hpp
        formnbj.ui
        formtortue.cpp
        formtortue.hpp
        formtortue.ui
        formmap.cpp
        formmap.hpp
        formmap.ui

        jeuaffichage.hpp
        jeuaffichage.cpp
        jeuaffichage.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LaGuerreDesTortues
        ${PROJECT_SOURCES}
    )

else()
    if(ANDROID)
        add_library(LaGuerreDesTortues SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(LaGuerreDesTortues
            ${PROJECT_SOURCES}
        )
    endif()

endif()

target_link_libraries(LaGuerreDesTortues PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
