##################################################
# Invoke ExternalProject Build
##################################################

file(MAKE_DIRECTORY "${EXTERNALPROJECT_BUILD_PREFIX}")
execute_process(COMMAND ${CMAKE_COMMAND} -G ${CMAKE_GENERATOR} ${PROJECT_ARGS} "-DCMAKE_MINIMUM_REQUIRED_VERSION:STRING=${CMAKE_MINIMUM_REQUIRED_VERSION}" "-DEXTERNALPROJECT_BUILD_ARGS=${EXTERNALPROJECT_BUILD_ARGS}" ${EXTERNALPROJECT_BUILD_CONFIG_ARGS} "${CMAKE_CURRENT_LIST_DIR}"
                WORKING_DIRECTORY "${EXTERNALPROJECT_BUILD_PREFIX}")
message(FATAL_ERROR ${CMAKE_COMMAND} -G ${CMAKE_GENERATOR} ${PROJECT_ARGS} "-DCMAKE_MINIMUM_REQUIRED_VERSION:STRING=${CMAKE_MINIMUM_REQUIRED_VERSION}" "-DEXTERNALPROJECT_BUILD_ARGS=${EXTERNALPROJECT_BUILD_ARGS}" ${EXTERNALPROJECT_BUILD_CONFIG_ARGS} "${CMAKE_CURRENT_LIST_DIR}" "\n" ${CMAKE_COMMAND} --build "${EXTERNALPROJECT_BUILD_PREFIX}" ${EXTERNALPROJECT_BUILD_BUILD_ARGS})
execute_process(COMMAND ${CMAKE_COMMAND} --build "${EXTERNALPROJECT_BUILD_PREFIX}" ${EXTERNALPROJECT_BUILD_BUILD_ARGS})

unset(EXTERNALPROJECT_BUILD_PREFIX)
unset(EXTERNALPROJECT_BUILD_CONFIG_ARGS)
unset(EXTERNALPROJECT_BUILD_BUILD_ARGS)
unset(EXTERNALPROJECT_BUILD_ARGS)
