# xapp_sdk
set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}/")
set(dst_dir "${CMAKE_BINARY_DIR}/src/usr/python3/")

# monitor
list(APPEND lst_src "${src_dir}ho.py")
list(APPEND lst_dst "${dst_dir}ho.py")

list(APPEND lst_src "${src_dir}mntr_cb.py")
list(APPEND lst_dst "${dst_dir}mntr_cb.py")

list(APPEND lst_src "${src_dir}mntr_ue_cb.py")
list(APPEND lst_dst "${dst_dir}mntr_ue_cb.py")

list(APPEND lst_src "${src_dir}mntr_ue.py")
list(APPEND lst_dst "${dst_dir}mntr_ue.py")

list(APPEND lst_src "${src_dir}mntr.py")
list(APPEND lst_dst "${dst_dir}mntr.py")

list(APPEND lst_src "${src_dir}slicing.py")
list(APPEND lst_dst "${dst_dir}slicing.py")

list(APPEND lst_src "${src_dir}../../../lib/_xapp_usr_sdk.so")
list(APPEND lst_dst "${dst_dir}_xapp_usr_sdk.so")

list(APPEND lst_src "${src_dir}xapp_usr_sdk.py")
list(APPEND lst_dst "${dst_dir}xapp_usr_sdk.py")

foreach(src dst IN ZIP_LISTS lst_src lst_dst)
    file(COPY_FILE ${src} ${dst}
        )
endforeach()
