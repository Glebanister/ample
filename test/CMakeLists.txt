set(TEST_SOURCES
    test_all.cpp
    testJsonIO.cpp
    )

add_subdirectory(../extern/googletest buildGoogletest)

include_directories(../extern/rapidjson/include/)
include_directories(../extern/googletest/googletest/include/)
include_directories(../core/include/)

add_executable(${CMAKE_PROJECT_NAME}-test ${TEST_SOURCES})

add_test(NAME ${CMAKE_PROJECT_NAME}-test COMMAND ${CMAKE_PROJECT_NAME}-test)

target_link_libraries(${CMAKE_PROJECT_NAME}-test PUBLIC ${CMAKE_PROJECT_NAME} gtest)
target_link_libraries(${CMAKE_PROJECT_NAME}-test PUBLIC ${CMAKE_PROJECT_NAME} ample)
