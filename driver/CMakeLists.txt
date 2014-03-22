# This file is part of rcythrScript.
# rcythrScript is licensed under the MIT LICENSE. For more info see the LICENSE file.

add_executable(rcythrscript-bin driver.cc)
set_target_properties(rcythrscript-bin PROPERTIES OUTPUT_NAME rcythrscript)
target_link_libraries(rcythrscript-bin rcythrscript)
