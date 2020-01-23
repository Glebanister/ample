set(BINARY test_ample)

include_directories(Ample/include)

set(TEST_SOURCES

    test_all.cpp

    )

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC Ample gtest)
