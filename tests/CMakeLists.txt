add_executable(test_sum test_sum.cpp)

target_link_libraries(test_sum 
    GTest::gtest_main
)

add_executable(test_mock_sensor test_mock_sensor.cpp)

target_link_libraries(test_mock_sensor 
    GTest::gtest
    GTest::gmock_main
)

add_executable(test_sample test_sample.cpp)
target_link_libraries(test_sample 
    GTest::gtest
)

add_executable(test_fixture test_fixture.cpp)
target_link_libraries(test_fixture 
    GTest::gtest_main
)

add_executable(test_fixture_lifecycle test_fixture_lifecycle.cpp)
target_link_libraries(test_fixture_lifecycle
    GTest::gtest_main
)

add_executable(test_auto_lock_system
    test_auto_lock_system.cpp
    # Bạn có thể thêm các file test khác vào đây, ví dụ:
    # test_sample.cpp
    # test_mock_sensor.cpp
)

target_link_libraries(test_auto_lock_system
    GTest::gmock_main
    lock_system
)

include(GoogleTest)
gtest_discover_tests(test_sample)
gtest_discover_tests(test_sum)
gtest_discover_tests(test_mock_sensor)
gtest_discover_tests(test_fixture)
gtest_discover_tests(test_fixture_lifecycle)
gtest_discover_tests(test_auto_lock_system)
