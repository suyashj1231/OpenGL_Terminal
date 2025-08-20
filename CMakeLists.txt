cmake_minimum_required(VERSION 3.16)
project(ogl_terminal LANGUAGES CXX)
set(CMAKE_POLICY_VERSION_MINIMUM "3.5")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Helpful flags
if(MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include(FetchContent)

# ---- GLAD ----
FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

# ---- GLFW ----
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# ---- FreeType ----
FetchContent_Declare(
        freetype
        GIT_REPOSITORY https://github.com/freetype/freetype.git
        GIT_TAG VER-2-13-2
)
# keep FreeType light (no extra deps)
set(FT_DISABLE_BZIP2   ON CACHE BOOL "" FORCE)
set(FT_DISABLE_PNG     ON CACHE BOOL "" FORCE)
set(FT_DISABLE_HARFBUZZ ON CACHE BOOL "" FORCE)
set(FT_DISABLE_BROTLI  ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(freetype)

# ---- Sources ----
file(GLOB SRC CONFIGURE_DEPENDS src/*.cpp src/*.h)
add_executable(ogl_terminal ${SRC})
target_include_directories(ogl_terminal PRIVATE src)
target_link_libraries(ogl_terminal PRIVATE glad glfw freetype)

# macOS frameworks for GLFW
if(APPLE)
    target_link_libraries(ogl_terminal PRIVATE
            "-framework Cocoa" "-framework IOKit" "-framework CoreVideo"
    )
endif()

# On Windows, ensure we find the assets folder at runtime (for your font)
# (CLion & VS usually run from the build dir; this copies assets alongside the exe)
add_custom_command(TARGET ogl_terminal POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:ogl_terminal>/assets
)