add_subdirectory(thirdparty SYSTEM)

add_modules_library(runtime)
target_link_libraries(runtime PUBLIC platform core input scene rendering)

# TODO: binding library