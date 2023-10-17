cmake_minimum_required(VERSION 3.16)
project(BrainBlast LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_COLOR_DIAGNOSTICS ON)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(BrainBlast source/Main.cpp
        source/Collision/Collision.cpp)

target_link_libraries(BrainBlast PRIVATE sfml-graphics)
target_link_libraries(BrainBlast PRIVATE sfml-audio)
target_compile_features(BrainBlast PRIVATE cxx_std_17)

if(MSVC)
    target_compile_options(BrainBlast PRIVATE /W4 /WX)
else()
    target_compile_options(BrainBlast PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

if(UNIX)
    target_link_libraries(BrainBlast PRIVATE m)
endif()

if(WIN32)
    add_custom_command(
        TARGET BrainBlast
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:BrainBlast>
        VERBATIM)

    # add_custom_command(
    #     TARGET BrainBlast
    #     COMMENT "Copy DLLs"
    #     POST_BUILD COMMAND ldd BrainBlast.exe | grep -vi system32 | grep -vi windows | grep -vi sfml | grep -v :$ | cut -f2 -d\> | cut -f1 -d\( | tr \\ / | while read a; do ! [ -e "build/`basename $a`" ] && cp -v "$a" .; done
    #     VERBATIM)
endif()

if(NOT BUILD_SHARED_LIBS AND WIN32)
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ ${CMAKE_CXX_STANDARD_LIBRARIES}")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lwinpthread")
    set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} -lwinpthread")
    set(CMAKE_CXX_STANDARD_LIBRARIES "-lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
endif()

install(TARGETS BrainBlast)
