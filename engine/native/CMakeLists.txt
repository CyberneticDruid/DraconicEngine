include(Compiler)
include(Modules)

add_modules_library(core SHARED)
target_link_libraries(core PUBLIC definitions math io memory)

add_subdirectory(thirdparty SYSTEM)
add_subdirectory(platform)
add_subdirectory(input)
add_subdirectory(rendering)
add_subdirectory(scene)