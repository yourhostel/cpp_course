# III_course/2025-09-24-qt-notepad/CMakeLists.txt
project(qt_notepad)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(qt_notepad
        main.cpp
        notepad.cpp
)

target_link_libraries(qt_notepad PRIVATE Qt6::Widgets)

# ---------- ІНСТАЛЯЦІЯ ----------
include(GNUInstallDirs)

# 1) Бінарник => /usr/local/bin
install(TARGETS qt_notepad
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# 2) .desktop: сконфігурувати з шаблону і встановити => /usr/local/share/applications
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/qt_notepad.desktop.in
        ${CMAKE_CURRENT_BINARY_DIR}/qt_notepad.desktop
        @ONLY
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qt_notepad.desktop
        DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
)

# 3) Іконка : /usr/local/share/icons/hicolor/128x128/apps
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/icons/qt_notepad-128.png)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/icons/qt_notepad-128.png
            DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/128x128/apps
            RENAME qt_notepad.png)
endif()