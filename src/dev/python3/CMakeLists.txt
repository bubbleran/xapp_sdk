# xapp_sdk
set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}/")
set(dst_dir "${CMAKE_BINARY_DIR}/src/dev/python3/")

# monitor
list(APPEND lst_src "${src_dir}xapp_cust_moni.py")
list(APPEND lst_dst "${dst_dir}xapp_cust_moni.py")

list(APPEND lst_src "${src_dir}xapp_all_moni.py")
list(APPEND lst_dst "${dst_dir}xapp_all_moni.py")

list(APPEND lst_src "${src_dir}xapp_oran_moni.py")
list(APPEND lst_dst "${dst_dir}xapp_oran_moni.py")

list(APPEND lst_src "${src_dir}xapp_sdk.py")
list(APPEND lst_dst "${dst_dir}xapp_sdk.py")

list(APPEND lst_src "${src_dir}../../../lib/_xapp_sdk.so")
list(APPEND lst_dst "${dst_dir}_xapp_sdk.so")

foreach(src dst IN ZIP_LISTS lst_src lst_dst)
    file(COPY_FILE ${src} ${dst} )
endforeach()
