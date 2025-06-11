set(LIST_XAPP xapp_ho_sdk xapp_sdk_moni_ue xapp_sdk_moni xapp_sdk_moni_cb xapp_sdk_moni_ue_cb xapp_slice_sdk xapp_sdk_moni_slice)

if(XAPP_DB STREQUAL "NONE_XAPP")
  set(E42_SDK_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/libxapp_sdk_c.a")
elseif(XAPP_DB STREQUAL "SQLITE3_XAPP")
  set(E42_SDK_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/libxapp_sdk_c_sqlite3.a")
else(XAPP_DB STREQUAL "MYSQL_XAPP")
  set(E42_SDK_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/libxapp_sdk_c_mysql.a")
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
                          -lmysqlclient
                          )

    target_compile_definitions(${XAPP} PUBLIC ${E2AP_VERSION} ${KPM_VERSION}) 
endforeach()
