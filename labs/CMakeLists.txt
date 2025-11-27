set(LIST_XAPP lab1 lab3 lab5 lab6)

if(XAPP_DB STREQUAL "NONE_XAPP")
  set(E42_SDK_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/libxapp_sdk_c.a")
elseif(XAPP_DB STREQUAL "SQLITE3_XAPP")
  set(E42_SDK_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/libxapp_sdk_c_sqlite3.a")
else(XAPP_DB STREQUAL "MYSQL_XAPP")
  set(E42_SDK_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/libxapp_sdk_c_mysql.a")
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


set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}")
set(dst_dir "${CMAKE_CURRENT_BINARY_DIR}")

list(APPEND lst_src "${src_dir}/lab2.py")
list(APPEND lst_dst "${dst_dir}/lab2.py")

list(APPEND lst_src "${src_dir}/lab5.py")
list(APPEND lst_dst "${dst_dir}/lab5.py")

list(APPEND lst_src "${CMAKE_SOURCE_DIR}/src/usr/python3/xapp_usr_sdk.py")
list(APPEND lst_dst "${dst_dir}/xapp_usr_sdk.py")



if(XAPP_DB STREQUAL "NONE_XAPP")
    list(APPEND lst_src "${CMAKE_SOURCE_DIR}/lib/_xapp_usr_sdk.so")
    list(APPEND lst_dst "${dst_dir}/_xapp_usr_sdk.so")
elseif(XAPP_DB STREQUAL "SQLITE3_XAPP")
    list(APPEND lst_src "${CMAKE_SOURCE_DIR}/lib/_xapp_usr_sdk_sqlite3.so")
    list(APPEND lst_dst "${dst_dir}/_xapp_usr_sdk.so")
else(XAPP_DB STREQUAL "MYSQL_XAPP")
    list(APPEND lst_src "${CMAKE_SOURCE_DIR}/lib/_xapp_usr_sdk_sqlite3.so")
    list(APPEND lst_dst "${dst_dir}/_xapp_usr_sdk.so")
endif()


foreach(src dst IN ZIP_LISTS lst_src lst_dst)
    file(COPY_FILE ${src} ${dst})
endforeach()


