set(BINARY binary-tree-project)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.hpp *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})
target_link_libraries(${BINARY}_run ${CMAKE_CURRENT_SOURCE_DIR}/../list/list.hpp)

add_library(${BINARY}_lib STATIC ${SOURCES})