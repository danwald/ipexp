add_executable(server server.cc imagedb.cc)
set(LIBS ${LIBS} boost_system boost_filesystem boost_timer httpserver pHash gnutls-openssl)
target_link_libraries(server ${LIBS})
