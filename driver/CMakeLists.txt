# This file is part of rcythrScript.
# rcythrScript is licensed under the MIT LICENSE. For more info see the LICENSE file.

add_executable(driver driver.cc)
target_link_libraries(driver rcythrscript)
