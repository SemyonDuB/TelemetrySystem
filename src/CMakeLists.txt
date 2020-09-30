add_library(data_transfer "")

target_sources(data_transfer
    PUBLIC data_transfer.hpp
    PRIVATE data_transfer.cpp)

target_include_directories(data_transfer 
	PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_arduino_libraries(data_transfer PUBLIC core)

add_subdirectory(receiver)
add_subdirectory(sender)
