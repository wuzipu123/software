
####################
# UNIT TESTS
####################

#list(REMOVE_ITEM unittest-includes ${PROJECT_SOURCE_DIR}/target_h/events ${PROJECT_SOURCE_DIR}/target_h/events/equeue)

set(unittest-includes ${unittest-includes}
        target_h
        ../lib
        ../src/protocol
        ../src/sensor
        ../src/utils
        )

set(unittest-sources
        ../src/protocol/JsonProtocol.cpp
        ../src/protocol/Protocol.cpp
        ../src/sensor/SensorData.cpp
        )

set(unittest-test-sources
        protocol/JsonProtocol/test_JsonProtocol.cpp
        stubs/SensorBoardSerial_stub.cpp
        stubs/ThisThread_stub.cpp
        stubs/utils_stub.cpp
        stubs/Logger_stub.cpp
        stubs/MbedCRC_stub.cpp
        )
