
file(GLOB XAPP_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.c")                                       
set(LIST_XAPP "")                                                                                                 
foreach(XAPP_SRC ${XAPP_SOURCES})                                                                                 
  get_filename_component(XAPP_NAME ${XAPP_SRC} NAME_WE)                                                           
  list(APPEND LIST_XAPP ${XAPP_NAME})                                                                             
endforeach() 

if(XAPP_DB STREQUAL "NONE_XAPP")
  set(E42_SDK_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/libxapp_sdk_c.a")
elseif(XAPP_DB STREQUAL "SQLITE3_XAPP")
  set(E42_SDK_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/libxapp_sdk_c_sqlite3.a")
elseif(XAPP_DB STREQUAL "MYSQL_XAPP")
  set(E42_SDK_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/libxapp_sdk_c_mysql.a")
elseif(XAPP_DB STREQUAL "VICTORIAMETRICS_XAPP")
  set(E42_SDK_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/libxapp_sdk_c_vm.a")
endif()

foreach(XAPP ${LIST_XAPP})
    add_executable(${XAPP}
                   ${XAPP}.c
                   )
    
    target_link_libraries(${XAPP}
                          PUBLIC
                          ${E42_SDK_LIB_PATH}
                          -lconfig
                          -lpthread
                          -lm
                          -lsctp
                          -ldl
                          )

    if(XAPP_DB STREQUAL "MYSQL_XAPP")
        target_link_libraries(${XAPP} PUBLIC -lmysqlclient)
    endif()

    target_compile_definitions(${XAPP} PUBLIC ${E2AP_VERSION} ${KPM_VERSION}) 
endforeach()
