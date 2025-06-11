cmake_minimum_required(VERSION 3.15)

project(Flexric VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LibConfig REQUIRED libconfig)

set(E2AP_VERSION "E2AP_V3" CACHE STRING "E2AP version")
set(KPM_VERSION "KPM_V3_00" CACHE STRING "The KPM SM version to use")

set(XAPP_DB "NONE_XAPP" CACHE STRING "xApp DB")
set_property(CACHE XAPP_DB PROPERTY STRINGS "MYSQL_XAPP" "SQLITE3_XAPP" "NONE_XAPP")
message(STATUS "Selected xApp DB : ${XAPP_DB}")

# include src files
include_directories(include)
include_directories(src/usr/c)
include_directories(src/dev/c)

add_subdirectory(src)
add_subdirectory(labs)

# Remember to 
# sudo make install && ldconfig
install(FILES "${CMAKE_SOURCE_DIR}/lib/libe42_xapp_shared.so" DESTINATION /usr/local/lib/)

file(GLOB_RECURSE CONF_FILES "${CMAKE_SOURCE_DIR}/conf/*.conf")
install(FILES ${CONF_FILES} DESTINATION /usr/local/etc/flexric)

