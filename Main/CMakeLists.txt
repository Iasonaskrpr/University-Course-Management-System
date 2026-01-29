add_executable(Example main.cpp)

target_include_directories(Example PUBLIC 
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/Include")

target_link_libraries(Example PUBLIC ManagementLibrary)