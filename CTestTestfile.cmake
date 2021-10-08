# CMake generated Testfile for 
# Source directory: /home/shadow/dev/shadoemu_gba
# Build directory: /home/shadow/dev/shadoemu_gba
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(check_gbe "/home/shadow/dev/shadoemu_gba/tests/check_gbe")
set_tests_properties(check_gbe PROPERTIES  _BACKTRACE_TRIPLES "/home/shadow/dev/shadoemu_gba/CMakeLists.txt;97;add_test;/home/shadow/dev/shadoemu_gba/CMakeLists.txt;0;")
subdirs("lib")
subdirs("gbemu")
subdirs("tests")
