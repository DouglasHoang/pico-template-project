cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(main C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Export commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(main
        main.c
        )

# pull in common dependencies
target_link_libraries(main pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(main)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/wrapper.tmp
"#!/usr/bin/env bash
# Note that './main' is relative from whatever directory you are in
# Use just main assuming the install prefix is in your bath
# Or use $<TARGET_FILE:main> 
# Or maybe ${CMAKE_INSTALL_PREFIX}/bin/main
openocd -f /home/douglashoang/openocd/tcl/interface/cmsis-dap.cfg -f /home/douglashoang/openocd/tcl/target/rp2040.cfg -c \"program ${CMAKE_CURRENT_BINARY_DIR}/main.elf verify reset exit\"
")

# add execute permissions
file(
    COPY ${CMAKE_CURRENT_BINARY_DIR}/wrapper.tmp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

# Rename the file
file(RENAME 
    ${CMAKE_CURRENT_BINARY_DIR}/wrapper.tmp
    ${CMAKE_CURRENT_BINARY_DIR}/flash
)

# Make file executeable
file(CHMOD 
    ${CMAKE_CURRENT_BINARY_DIR}/flash
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
