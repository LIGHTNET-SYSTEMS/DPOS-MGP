# will be implictly used for any compilation unit if not overrided by SYSTEM_INCLUDE_FOLDERS parameter
# these directories go as -isystem <dir> to avoid warnings from code of third-party libraries

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/ltnio.bios/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/ltnio.bios/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/ltnio.msig/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/ltnio.msig/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/ltnio.system/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/ltnio.system/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/ltnio.token/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/ltnio.token/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/ltnio.wrap/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/ltnio.wrap/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/old_versions/v1.6.0-rc3/ltnio.bios/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/old_versions/v1.6.0-rc3/ltnio.bios/)
