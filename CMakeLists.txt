# Set path
CU_SET_PATH("CMAKE_QUICKTELE_DIR" "${CMAKE_CURRENT_LIST_DIR}")

# Add SC
AC_ADD_SCRIPT("${CMAKE_QUICKTELE_DIR}/src/QuickTeleport.cpp")

#Add SL
AC_ADD_SCRIPT_LOADER("QuickTeleport" "${CMAKE_QUICKTELE_DIR}/src/loader.h")

#CMake Hook
CU_ADD_HOOK(AFTER_WORLDSERVER_CMAKE "${CMAKE_QUICKTELE_DIR}/src/cmake/after_ws_install.cmake")

