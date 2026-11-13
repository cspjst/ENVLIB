# Copyright (c) 2026 Jeremy Simon Thornton, License: MIT
cmake_minimum_required(VERSION 3.10)

# Toolchain (DOS / I86 / wcl) comes from cmk.sh -D flags.
project(ENVLIB VERSION 0.0.2 LANGUAGES C)

# Compiler options
# Reference: https://users.pja.edu.pl/~jms/qnx/help/watcom/compiler-tools/cpopts.html
add_compile_options(
    -0          # 8086/8088 instructions only
    -bt=dos     # Target DOS
    -ml         # Large memory model: MUST match every program linking this lib
    -za99       # C99 (partial in OW2)
    -zp1        # 1-byte struct packing (structs are filled from asm)
    -ox         # Full optimisation (note: implies -s, no stack checks)
    -os         # Favour size
    -d2         # Full debug info
    -w2         # Warning level 2
    -zq         # Quiet
)
# Optional switches:
#   -e<n>   stop after n errors
#   -fpi87  assume 8087 present (only if every target XT has one)

# Dependencies
# BIOSLIB (vendored copy: include/BIOS/*.h, lib/BIOS.lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(BIOS_LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/BIOS.lib)

# Sources
# Library code
file(GLOB ENV_SOURCES
    CONFIGURE_DEPENDS
    ENV/*.c
)
# Test harness
file(GLOB TEST_SOURCES
    CONFIGURE_DEPENDS
    *.c
    TEST/*.c
)

# Versioning
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/../README.md.in
    ${CMAKE_CURRENT_SOURCE_DIR}/../README.md
    @ONLY
)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/ENV/env_version.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/ENV/env_version.h
  @ONLY
)

# Build mode selection
set(MAKE_LIB ON)

if(MAKE_LIB)
    # ENV.LIB from library code; TEST.exe gets ENV code only via the lib
    add_library(ENVLIB STATIC ${ENV_SOURCES})
    set_target_properties(ENVLIB PROPERTIES OUTPUT_NAME ENV)
    add_executable(TEST ${TEST_SOURCES})
    target_link_libraries(TEST PRIVATE ENVLIB ${BIOS_LIB})
  else()
      # Everything compiled straight into TEST.exe
      add_executable(TEST ${TEST_SOURCES} ${ENV_SOURCES})
      target_link_libraries(TEST PRIVATE ${BIOS_LIB})
  endif()
