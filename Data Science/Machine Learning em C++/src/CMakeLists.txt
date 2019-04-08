project(source)

add_library(data STATIC "data.cpp")
add_library(statistics STATIC "statistics.cpp")
target_link_libraries(data statistics)
target_link_libraries(statistics data)

add_executable(main "main.cpp")
target_link_libraries(main data)

