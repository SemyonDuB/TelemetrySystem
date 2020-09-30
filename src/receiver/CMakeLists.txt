add_executable(receiver receiver.cpp)

target_link_libraries(receiver PUBLIC data_transfer)
target_link_arduino_libraries(receiver PRIVATE core)
target_enable_arduino_upload(receiver)
