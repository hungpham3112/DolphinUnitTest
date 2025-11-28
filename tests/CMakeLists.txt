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
)

target_link_libraries(test_auto_lock_system
    GTest::gmock_main
    lock_system
)

add_executable(test_five_doubles
    test_five_doubles.cpp
)

target_link_libraries(test_five_doubles
    GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(test_sample)
gtest_discover_tests(test_sum)
gtest_discover_tests(test_mock_sensor)
gtest_discover_tests(test_fixture)
gtest_discover_tests(test_fixture_lifecycle)
gtest_discover_tests(test_auto_lock_system)
gtest_discover_tests(test_five_doubles)
