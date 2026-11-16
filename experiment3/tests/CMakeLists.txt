set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../../third_party/googletest"
                 "${CMAKE_CURRENT_BINARY_DIR}/googletest" EXCLUDE_FROM_ALL)
AUX_SOURCE_DIRECTORY(. SOURCE)
ADD_EXECUTABLE(training_main ${SOURCE})
TARGET_LINK_LIBRARIES(training_main training gtest_main)

ADD_TEST(NAME training_main COMMAND training_main)
