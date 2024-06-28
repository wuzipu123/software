
####################
# UNIT TESTS
####################

#list(REMOVE_ITEM unittest-includes ${PROJECT_SOURCE_DIR}/target_h/events ${PROJECT_SOURCE_DIR}/target_h/events/equeue)

set(unittest-includes ${unittest-includes}
        target_h
        ../src/sensor
        ../lib
        ../src/utils
        )

set(unittest-sources
        ../src/sensor/SensorData.cpp
        )

set(unittest-test-sources
        sensor/SensorData/test_SensorData.cpp
        stubs/utils_stub.cpp
        stubs/Logger_stub.cpp
        )
