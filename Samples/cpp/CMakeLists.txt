#
# Rendering Sample
#
add_executable(Render rendering.cpp)

target_link_libraries(Render
        PRIVATE
        runtime
        bgfx
        bx
        bimg
)

if(UNIX AND NOT APPLE)
    target_link_libraries(Render PRIVATE SDL3::SDL3-static Threads::Threads dl)
    target_link_options(Render PRIVATE -Wl,--whole-archive $<TARGET_FILE:SDL3::SDL3-static> -Wl,--no-whole-archive)
elseif(APPLE)
    target_link_libraries(Render PRIVATE SDL3::SDL3-static)
    target_link_options(Render PRIVATE -Wl,-force_load,$<TARGET_FILE:SDL3::SDL3-static>)
else()
    target_link_libraries(Render PRIVATE SDL3::SDL3-static)
endif()

compile_shaders(Render)

set(TEST_IMAGE
        "${CMAKE_SOURCE_DIR}/Docs/assets/draconic_logo_no_text.png"
)

add_custom_command(
        TARGET Render POST_BUILD

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${TEST_IMAGE}
        $<TARGET_FILE_DIR:Render>/test.png

        COMMENT "Copying test texture..."
)
