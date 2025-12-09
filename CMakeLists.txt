cmake_minimum_required(VERSION 4.2.0)
project(DragonScaler)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/include")
set(PROJECT_LIB "${CMAKE_CURRENT_LIST_DIR}/lib")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld -Xlinker /SUBSYSTEM:WINDOWS -Xlinker /ENTRY:mainCRTStartup")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_LIB})

target_link_libraries(${PROJECT_NAME} PRIVATE glfw3 imgui_glfw opencv4 kernel32 user32 gdi32 winmm shell32 opengl32 )
