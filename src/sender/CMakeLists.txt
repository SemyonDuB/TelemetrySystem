add_executable(sender sender.cpp)

target_link_libraries(sender PRIVATE data_transfer)
target_link_arduino_libraries(sender PRIVATE core)
target_enable_arduino_upload(sender)
