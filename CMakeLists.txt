cmake_minimum_required(VERSION 3.10)
project(WebViewDiscordBot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(webview)

find_package(PkgConfig REQUIRED)
pkg_check_modules(WEBKIT REQUIRED webkit2gtk-4.1)


add_executable(webview_discord_bot main.cpp)
target_include_directories(webview_discord_bot PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/webview/core/include ${WEBKIT_INCLUDE_DIRS})
target_link_libraries(webview_discord_bot webview_core_static ${WEBKIT_LIBRARIES})