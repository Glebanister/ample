set(TEST_SOURCES
    test_all.cpp
    testActivity.cpp
    )

add_executable(test_${CMAKE_PROJECT_NAME} ${TEST_SOURCES})

add_test(NAME test_${CMAKE_PROJECT_NAME} COMMAND test_${CMAKE_PROJECT_NAME})

target_link_libraries(test_${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_PROJECT_NAME} gtest)
target_link_libraries(test_${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_PROJECT_NAME} Ample)
