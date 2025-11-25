# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TcpCilentWithHercules_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TcpCilentWithHercules_autogen.dir\\ParseCache.txt"
  "TcpCilentWithHercules_autogen"
  )
endif()
