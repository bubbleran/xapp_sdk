# xapp_sdk
set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}")
set(dst_dir "${CMAKE_CURRENT_BINARY_DIR}")

# monitor
list(APPEND lst_src "${src_dir}/xapp_cust_moni.py")
list(APPEND lst_dst "${dst_dir}/xapp_cust_moni.py")

list(APPEND lst_src "${src_dir}/xapp_all_moni.py")
list(APPEND lst_dst "${dst_dir}/xapp_all_moni.py")

list(APPEND lst_src "${src_dir}/xapp_oran_moni.py")
list(APPEND lst_dst "${dst_dir}/xapp_oran_moni.py")

list(APPEND lst_src "${src_dir}/xapp_sdk.py")
list(APPEND lst_dst "${dst_dir}/xapp_sdk.py")

if(XAPP_DB STREQUAL "NONE_XAPP")
    list(APPEND lst_src "${CMAKE_SOURCE_DIR}/lib/_xapp_sdk_python.so")
    list(APPEND lst_dst "${dst_dir}/_xapp_sdk_python.so")
elseif(XAPP_DB STREQUAL "SQLITE3_XAPP")
    list(APPEND lst_src "${CMAKE_SOURCE_DIR}/lib/_xapp_sdk_python_sqlite3.so")
    list(APPEND lst_dst "${dst_dir}/_xapp_sdk_python.so")
else(XAPP_DB STREQUAL "MYSQL_XAPP")
    list(APPEND lst_src "${CMAKE_SOURCE_DIR}/lib/_xapp_sdk_python_mysql.so")
    list(APPEND lst_dst "${dst_dir}/_xapp_sdk_python.so")
endif()

foreach(src dst IN ZIP_LISTS lst_src lst_dst)
    file(COPY_FILE ${src} ${dst} )
endforeach()
