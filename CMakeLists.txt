cmake_minimum_required(VERSION 3.10)

project(camlisp
        LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE on)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

string(CONCAT COMPILER_WARNING_FLAGS
  " -Werror"                            # make all warnings into errors
#  " -Weverything"                       # enable ALL warnings (clang only)
  " -Wall"
  " -Wextra"
  " -Wpedantic"
#  " -Winline"                           # warn when a function marked inline could not be substituted
  " -Wformat=2"                         # additional format string security checks
#  " -wfatal-errors"                     # abort compilation after the first error
#  " -Wno-c++98-compat"
#  " -Wno-c++98-compat-pedantic"
#  " -Wno-exit-time-destructors"
#  " -Wno-global-constructors"
#  " -Wno-missing-prototypes"
#  " -Wno-missing-variable-declarations"
#  " -Wno-padded"
)

string(CONCAT COMPILER_DIAGNOSTIC_FLAGS
  " -fdiagnostics-show-template-tree"   # print a tree-like structure when debugging templates
)

string(CONCAT COMPILER_FEATURE_FLAGS
#  " -fchar8_t"                          # enable support for C++20 char8_t (UTF-8 string)
)

string(CONCAT COMPILER_INSTRUMENTATION_FLAGS
  " -g"                                 # generate debugging information
  " -fsanitize=address,undefined"       # enable AddressSanitizer and UndefinedBehaviorSanitizer
  " -fsanitize-undefined-trap-on-error" # trap on undefined behavior
  " -fstack-clash-protection"           # increased reliablility of stack overflow detection
  " -fstack-protector-strong"           # stack smashing protector
)

string(CONCAT COMPILER_SECURITY_FLAGS
  " -D_FORTIFY_SOURCE=2"                # run-time buffer overflow detection
  " -D_GLIBCXX_ASSERTIONS"              # run-time bounds checking for containers
  " -fasynchronous-unwind-tables"       # increase reliablity of backtraces
  " -fexceptions"                       # enable table-based thread cancellation (?)
  " -fpie"                              # full ASLR for executables
  # " -fpic -shared"                      # no text relocations for shared libraries
)

string(CONCAT OTHER_COMPILER_FLAGS
  " -fanalyzer"                         # enable static analysis of code/advanced warnings
  " -pipe"                              # avoid temp files to speed up builds
  " -O2"                                # recommended optimizations
)

string(CONCAT CMAKE_CXX_FLAGS
  " ${CMAKE_CXX_FLAGS}"
  " ${COMPILER_WARNING_FLAGS}"
  " ${COMPILER_DIAGNOSTIC_FLAGS}"
  " ${COMPILER_FEATURE_FLAGS}"
  " ${COMPILER_INSTRUMENTATION_FLAGS}"
  " ${COMPILER_SECURITY_FLAGS}"
  " ${OTHER_COMPILER_FLAGS}"
)

add_link_options(
  "LINKER:-pie"                         # Produce a dynamically linked position independent executable
  "LINKER:-z,defs"                      # detect and reject underlinking
  "LINKER:-z,now"                       # disable lazy binding
  "LINKER:-z,relro"                     # read-only segments after relocation
)

find_package(Boost REQUIRED)

set(SRC_FILES src/Parse.cpp
              src/Parse.h
              src/Readline.cpp
              src/Readline.h
              src/Type.cpp
              src/Type.h
              src/Util.cpp
              src/Util.h
              src/main.cpp)

add_executable(camlisp ${SRC_FILES})

target_link_libraries(camlisp readline)
