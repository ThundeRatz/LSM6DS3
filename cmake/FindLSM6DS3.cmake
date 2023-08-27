set(LSM6DS3_PATH ./lib/LSM6DS3)
set(CUBE_INC_PATH ${CMAKE_SOURCE_DIR}/cube/Inc)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false "${LSM6DS3_PATH}/src/*")

list(APPEND LIB_SOURCES
    ${SOURCES}
)

list(APPEND LIB_INCLUDE_DIRECTORIES
    ${LSM6DS3_PATH}/inc
    ${LSM6DS3_PATH}/inc/types
    ${LSM6DS3_PATH}/inc/reg
    ${LSM6DS3_PATH}/inc/proxys
    ${LSM6DS3_PATH}/inc/interfaces
    ${LSM6DS3_PATH}/inc/platforms
)

if(NOT EXISTS ${CUBE_INC_PATH}/i2c.h)
    list(APPEND LIB_INCLUDE_DIRECTORIES
        ${LSM6DS3_PATH}/inc/cube_mock/i2c_mock
    )
elseif(NOT EXISTS ${CUBE_INC_PATH}/spi.h)
    list(APPEND LIB_INCLUDE_DIRECTORIES
        ${LSM6DS3_PATH}/inc/cube_mock/spi_mock
    )
endif()
