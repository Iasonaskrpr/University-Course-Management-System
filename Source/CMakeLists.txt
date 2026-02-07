add_library(ManagementLibrary
            Course.cpp
            
            Person.cpp
            Professor.cpp
            Secretary.cpp
            Student.cpp
            )

target_include_directories(ManagementLibrary PUBLIC 
                "${PROJECT_BINARY_DIR}"
                "${PROJECT_SOURCE_DIR}/Include")
