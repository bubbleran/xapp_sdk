set(LIST_XAPP hw 
              xapp_all_moni 
              xapp_cust_moni 
              xapp_cust_moni_simple 
              xapp_cust_slice_moni_ctrl
	      xapp_cust_isac_srs
              xapp_get_mcs 
              xapp_mcs 
              xapp_oran_ccc_bwp_ctrl
              xapp_oran_moni 
              xapp_oran_rc_handover_ctrl
              xapp_oran_rc_slice_ctrl
	      xapp_oran_llc_srs
              )

if(XAPP_DB STREQUAL "NONE_XAPP")
  set(E42_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/libe42_xapp.a")
elseif(XAPP_DB STREQUAL "SQLITE3_XAPP")
  set(E42_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/libe42_xapp_sqlite3.a")
elseif(XAPP_DB STREQUAL "MYSQL_XAPP")
  set(E42_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/libe42_xapp_mysql.a")
elseif(XAPP_DB STREQUAL "VICTORIAMETRICS_XAPP")
  set(E42_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/libe42_xapp_vm.a")
endif()

foreach(XAPP ${LIST_XAPP})
    add_executable(${XAPP}
                   ${XAPP}.c
                   )

    target_link_libraries(${XAPP}
                          PUBLIC
                          ${E42_LIB_PATH}
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



