# xapp_sdk
set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}")
set(dst_dir "${CMAKE_CURRENT_BINARY_DIR}")

file(GLOB lst_src CONFIGURE_DEPENDS "${src_dir}/*.py")                                                            
set(lst_dst "")                                                                                                   
foreach(src ${lst_src})                                                                                           
  get_filename_component(fname "${src}" NAME)                                                                   
  list(APPEND lst_dst "${dst_dir}/${fname}")                                                                    
endforeach() 

if(XAPP_DB STREQUAL "NONE_XAPP")
    list(APPEND lst_src "${CMAKE_SOURCE_DIR}/lib/_xapp_usr_sdk.so")
    list(APPEND lst_dst "${dst_dir}/_xapp_usr_sdk.so")
elseif(XAPP_DB STREQUAL "SQLITE3_XAPP")
    list(APPEND lst_src "${CMAKE_SOURCE_DIR}/lib/_xapp_usr_sdk_sqlite3.so")
    list(APPEND lst_dst "${dst_dir}/_xapp_usr_sdk.so")
elseif(XAPP_DB STREQUAL "MYSQL_XAPP")
    list(APPEND lst_src "${CMAKE_SOURCE_DIR}/lib/_xapp_usr_sdk_mysql.so")
    list(APPEND lst_dst "${dst_dir}/_xapp_usr_sdk.so")
elseif(XAPP_DB STREQUAL "VICTORIAMETRICS_XAPP")
    list(APPEND lst_src "${CMAKE_SOURCE_DIR}/lib/_xapp_usr_sdk_vm.so")
    list(APPEND lst_dst "${dst_dir}/_xapp_usr_sdk.so")
endif()

list(APPEND lst_src "${src_dir}/xapp_usr_sdk.py")
list(APPEND lst_dst "${dst_dir}/xapp_usr_sdk.py")

foreach(src dst IN ZIP_LISTS lst_src lst_dst)
    file(COPY_FILE ${src} ${dst}
        )
endforeach()
