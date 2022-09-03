find_package(GTest REQUIRED)

set(SOURCE 
        main.cpp
        doubly_linked_list_iter_test.cpp
        doubly_linked_list_test.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
add_executable(exo_test ${SOURCE})
target_link_libraries(exo_test GTest::gtest_main gtest)
target_link_libraries(exo_test pthread)

add_test(NAME exo_test COMMAND exo_test) 