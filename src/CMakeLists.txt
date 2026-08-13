# SPDX-FileCopyrightText: 2020-2026 David Rabkin
# SPDX-License-Identifier: 0BSD
add_executable(atm main.cpp driver.cpp machine.cpp)
target_link_libraries(atm PRIVATE projectDefs)
