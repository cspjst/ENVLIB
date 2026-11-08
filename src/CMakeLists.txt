# Copyright (c) 2026 Jeremy Simon Thornton, License: MIT
cmake_minimum_required(VERSION 3.10)

# Toolchain (DOS / I86 / wcl) comes from cmk.sh -D flags.
project(DOSLIB VERSION 0.1.0 LANGUAGES C)

# --- Compiler options --------------------------------------------
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

# --- Sources -----------------------------------------------------
# WARNING: Using GLOB for convenience. If adding new files, rerun: ./cmk.sh
# Library code
file(GLOB DOS_SOURCES
    CONFIGURE_DEPENDS
    DOS/*.c
)

# Test harness
file(GLOB TEST_SOURCES
    CONFIGURE_DEPENDS
    *.c
    TEST/*.c
)

# --- Build mode --------------------------------------------------
# Comment out the next line to build TEST.exe only (no library).
set(MAKE_LIB ON)

if(MAKE_LIB)
    # DOS.LIB from library code; TEST.exe gets DOS code only via the lib
    add_library(DOSLIB STATIC ${DOS_SOURCES})
    set_target_properties(DOSLIB PROPERTIES OUTPUT_NAME DOS)
    add_executable(TEST ${TEST_SOURCES})
    target_link_libraries(TEST PRIVATE DOSLIB)
else()
    # Everything compiled straight into TEST.exe
    add_executable(TEST ${TEST_SOURCES} ${DOS_SOURCES})
endif()
