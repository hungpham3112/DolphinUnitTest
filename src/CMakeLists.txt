add_library(lock_system 
    auto_lock_system.cpp
)

target_include_directories(lock_system PUBLIC ../include)

add_executable(main
    main.cpp
)

find_package(Threads REQUIRED)

target_link_libraries(main
    PRIVATE
    lock_system
    Threads::Threads
)
