# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TwixtQt_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TwixtQt_autogen.dir\\ParseCache.txt"
  "TwixtQt_autogen"
  )
endif()
