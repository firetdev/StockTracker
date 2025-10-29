## 🛠️ Updated CMakeLists.txt (Using Hardcoded SFML_DIR)

cmake_minimum_required(VERSION 3.10)
project(MySFMLApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# --- ⚠️ Hardcoded Fix for Homebrew SFML ⚠️ ---
# You MUST replace <YOUR_FOUND_PATH_HERE> with the directory you found 
# in Step 1 (e.g., /opt/homebrew/lib/cmake/SFML or the full Cellar path).
set(SFML_DIR "/opt/homebrew/Cellar/sfml/3.0.2/lib/cmake/SFML" CACHE PATH "Path to SFMLConfig.cmake directory.")
# -------------------------------------------

# Find SFML 3.0.2. CMake will now use the path set in SFML_DIR.
find_package(SFML 3.0.2 COMPONENTS Graphics Window System REQUIRED)

# --- Add ImGui-SFML Subdirectory ---
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/imgui" CACHE PATH "Path to ImGui root directory")
add_subdirectory(imgui-sfml)

# --- Add Executable ---
add_executable(MySFMLApp main.cpp)

# --- Link Libraries ---
target_link_libraries(MySFMLApp PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    ImGui-SFML
)

# --- 📦 Set RPATH for macOS ---
if(APPLE)
    set_target_properties(MySFMLApp PROPERTIES
        MACOSX_RPATH TRUE
        INSTALL_RPATH "@loader_path" 
    )
endif()
