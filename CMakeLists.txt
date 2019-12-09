cmake_minimum_required(VERSION 3.15)
project(othello)

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

FILE(GLOB SOURCES src/*.cpp src/**/*.cpp src/*.h src/**/*.h)
ADD_EXECUTABLE(othello ${SOURCES})

target_link_libraries(othello "${TORCH_LIBRARIES}")
set_property(TARGET othello PROPERTY CXX_STANDARD 14)

if (MSVC)
    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    add_custom_command(TARGET othello
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${TORCH_DLLS}
            $<TARGET_FILE_DIR:othello>)
endif (MSVC)