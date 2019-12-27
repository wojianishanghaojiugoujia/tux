aux_source_directory(. SRC_LIST)
add_library(duktape ${SRC_LIST})
set_target_properties(duktape PROPERTIES OUTPUT_NAME "duktape")