set(LSM6DS3_PATH ./lib/LSM6DS3)

list(APPEND LIB_SOURCES
    ${LSM6DS3_PATH}/src/lsm6dso_reg.c
    ${LSM6DS3_PATH}/src/lsm6ds.c
)

list(APPEND LIB_INCLUDE_DIRECTORIES
    ${LSM6DS3_PATH}/inc
)
