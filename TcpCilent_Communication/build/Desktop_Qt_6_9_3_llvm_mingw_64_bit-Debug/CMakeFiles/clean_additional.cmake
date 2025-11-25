# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TcpCilentWithHercules_QTableWidget_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TcpCilentWithHercules_QTableWidget_autogen.dir\\ParseCache.txt"
  "TcpCilentWithHercules_QTableWidget_autogen"
  )
endif()
