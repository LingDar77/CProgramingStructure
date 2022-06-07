cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_STANDARD 11)
set(ROOT_DIR ${CMAKE_SOURCE_DIR})
project(CApplication)

if (MSVC)
    # 设置 msvc 输入代码编码格式为 utf-8
    set(CMAKE_C_FLAGS /source-charset:utf-8)
endif()

# Basic include directories
include_directories(./ ./src ./include)

# Search for source files
# file(GLOB_RECURSE src src/*.cpp)
aux_source_directory(./src src)
foreach(i in ${src})
    message(${i})
endforeach(i in ${src})
# Search for libs
file(GLOB_RECURSE libs libs/*.lib)
foreach(i in ${libs})
    message(${i})
endforeach(i in ${libs})

link_directories("./libs")

# 指定 库文件输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ../libs/${PROJECT_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RLEASE ../libs/${PROJECT_NAME})
# 指定可执行程序输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ../bin/${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ../bin/${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${src})

# Link
target_link_libraries(${PROJECT_NAME} ${libs})
