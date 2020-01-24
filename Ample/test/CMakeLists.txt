set(BINARY test_ample)

include_directories(Ample/include)
include_directories(Ample/lib/googletest)

set(TEST_SOURCES

    test_all.cpp
    testActivity.cpp

    )

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC Ample gtest)
