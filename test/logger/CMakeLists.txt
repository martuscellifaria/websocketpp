
file (GLOB SOURCE_FILES *.cpp)
file (GLOB HEADER_FILES *.hpp)

init_target (test_logger)

build_test (${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})


final_target ()

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "test")
