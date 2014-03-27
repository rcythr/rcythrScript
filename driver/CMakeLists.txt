# This file is part of rscript.
# rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

add_executable(rscript-bin driver.cc keyboard_input.cc)
set_target_properties(rscript-bin PROPERTIES OUTPUT_NAME rscript)
target_link_libraries(rscript-bin rscript)
