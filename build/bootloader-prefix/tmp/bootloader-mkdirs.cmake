# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/felixwu/esp/v5.1/esp-idf/components/bootloader/subproject"
  "/Users/felixwu/Workspace/development/esp-learn/touchscreen/build/bootloader"
  "/Users/felixwu/Workspace/development/esp-learn/touchscreen/build/bootloader-prefix"
  "/Users/felixwu/Workspace/development/esp-learn/touchscreen/build/bootloader-prefix/tmp"
  "/Users/felixwu/Workspace/development/esp-learn/touchscreen/build/bootloader-prefix/src/bootloader-stamp"
  "/Users/felixwu/Workspace/development/esp-learn/touchscreen/build/bootloader-prefix/src"
  "/Users/felixwu/Workspace/development/esp-learn/touchscreen/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/felixwu/Workspace/development/esp-learn/touchscreen/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/felixwu/Workspace/development/esp-learn/touchscreen/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
