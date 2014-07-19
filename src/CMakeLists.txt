cmake_minimum_required(VERSION 2.8)

project(ipexp)

add_executable(server server.cc)
find_package (httpserver REQUIRED)
if (HTTPSERVER_FOUND)
    include_directories(${HTTPSERVER_INCLUDE_DIRS})
    target_link_libraries (server ${HTTPSERVER_LIBRARIES})
endif (HTTPSERVER_FOUND)
find_package (boost_thread REQUIRED)
if (BOOST_THREAD_FOUND)
    include_directories(${BOOST_THREAD_INCLUDE_DIRS})
    target_link_libraries (server ${BOOST_THREAD_LIBRARIES})
endif (BOOST_THREAD_FOUND)


install(TARGETS server DESTINATION bin)
