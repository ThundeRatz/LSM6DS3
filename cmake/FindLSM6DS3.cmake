set(LSM6DS3_PATH ./lib/LSM6DS3)
set(CUBE_INC_PATH ${CMAKE_SOURCE_DIR}/cube/Inc)

file(GLOB SOURCES LIST_DIRECTORIES false "${LSM6DS3_PATH}/src/**")

foreach(FILE IN LISTS SOURCES)
    list(APPEND LIB_SOURCES
       ${FILE}
    ) 
endforeach()

list(APPEND LIB_INCLUDE_DIRECTORIES
    ${LSM6DS3_PATH}/inc
    ${LSM6DS3_PATH}/inc/types
    ${LSM6DS3_PATH}/inc/reg 
    ${LSM6DS3_PATH}/inc/proxys 
    ${LSM6DS3_PATH}/inc/interfaces
)

if(NOT EXISTS ${CUBE_INC_PATH}/i2c.h AND NOT EXISTS ${CUBE_INC_PATH}/spi.h)
    list(APPEND LIB_INCLUDE_DIRECTORIES
        ${LSM6DS3_PATH}/inc/cube_mock
    )
endif()