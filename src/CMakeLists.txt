# SPDX-FileCopyrightText: 2020-2025 David Rabkin
# SPDX-License-Identifier: 0BSD
.PHONY: all clean test
add_executable(atm main.cpp driver.cpp machine.cpp)
target_link_libraries(atm PRIVATE projectDefs)
