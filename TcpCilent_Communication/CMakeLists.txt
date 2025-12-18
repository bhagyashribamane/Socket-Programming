cmake_minimum_required(VERSION 3.19)
project(TcpCilentWithHercules_QTableWidget LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network Sql)
find_package(Qt6 REQUIRED COMPONENTS Core Network)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(TcpCilentWithHercules_QTableWidget
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    tcpcilent.h tcpcilent.cpp
    learndialog.h learndialog.cpp learndialog.ui
    databasemanager.h databasemanager.cpp



)

target_link_libraries(TcpCilentWithHercules_QTableWidget
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
        Qt::Sql
)
target_link_libraries(TcpCilentWithHercules_QTableWidget PRIVATE Qt6::Core)
target_link_libraries(TcpCilentWithHercules_QTableWidget PRIVATE Qt6::Core)
target_link_libraries(TcpCilentWithHercules_QTableWidget PRIVATE Qt6::Core)
target_link_libraries(TcpCilentWithHercules_QTableWidget PRIVATE Qt6::Core)

include(GNUInstallDirs)

install(TARGETS TcpCilentWithHercules_QTableWidget
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET TcpCilentWithHercules_QTableWidget
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
