cmake_minimum_required(VERSION 3.15)

project(Flexric VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LibConfig REQUIRED libconfig)

set(E2AP_VERSION "E2AP_V3" CACHE STRING "E2AP version")
set(KPM_VERSION "KPM_V3_00" CACHE STRING "The KPM SM version to use")

set(XAPP_DB "NONE_XAPP" CACHE STRING "xApp DB")
set_property(CACHE XAPP_DB PROPERTY STRINGS "VICTORIAMETRICS_XAPP" "MYSQL_XAPP" "SQLITE3_XAPP" "NONE_XAPP")
message(STATUS "Selected xApp DB : ${XAPP_DB}")

# include src files
include_directories(include)
include_directories(src/usr/c)
include_directories(src/dev/c)

add_subdirectory(src)
add_subdirectory(labs)

# Remember to do `sudo make install && ldconfig`
# message(STATUS "CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")
# message(STATUS "CMAKE_INSTALL_LIBDIR = ${CMAKE_INSTALL_LIBDIR}")
set(_installed "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/libe42_xapp_shared.so")

if(XAPP_DB STREQUAL "NONE_XAPP")
  set(_source "${CMAKE_SOURCE_DIR}/lib/libe42_xapp_shared.so")
elseif(XAPP_DB STREQUAL "SQLITE3_XAPP")
  set(_source "${CMAKE_SOURCE_DIR}/lib/libe42_xapp_shared_sqlite3.so")
elseif(XAPP_DB STREQUAL "MYSQL_XAPP")
  set(_source "${CMAKE_SOURCE_DIR}/lib/libe42_xapp_shared_mysql.so")
elseif(XAPP_DB STREQUAL "VICTORIAMETRICS_XAPP")
  set(_source "${CMAKE_SOURCE_DIR}/lib/libe42_xapp_shared_vm.so")
endif()

install(CODE "
    message(STATUS \"Installing new libe42_xapp_shared.so from: ${_source}\")
    message(STATUS \"Install destination: ${_installed}\")

    if (EXISTS \"${_installed}\")
        message(STATUS \"Removing old library: ${_installed}\")
        file(REMOVE \"${_installed}\")
    endif()

    file(INSTALL
        DESTINATION \"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\"
        TYPE FILE
        FILES \"${_source}\"
        RENAME \"libe42_xapp_shared.so\")
")

file(GLOB_RECURSE CONF_FILES "${CMAKE_SOURCE_DIR}/conf/*.conf")
install(FILES ${CONF_FILES} DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/flexric)

