file(GLOB HEADERS "include/ltnio/wallet_api_plugin/*.hpp")
add_library( wallet_api_plugin
             wallet_api_plugin.cpp
             ${HEADERS} )

target_link_libraries( wallet_api_plugin wallet_plugin http_plugin appbase )
target_include_directories( wallet_api_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
