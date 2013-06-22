CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(JSONRPC) 

# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

INCLUDE_DIRECTORIES(include ${CMAKE_CURRENT_SOURCE_DIR}/../json/include)
ADD_LIBRARY(jsonrpc STATIC 
	    src/jsonrpc_client.cpp
	    src/jsonrpc_handler.cpp 
	    src/jsonrpc_server.cpp
	    src/jsonrpc_tcpclient.cpp
	    src/jsonrpc_tcpserver.cpp
	    src/jsonrpc_udpclient.cpp
	    src/jsonrpc_udpserver.cpp
	    src/netstring.cpp
	    src/networking.cpp)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/..)
