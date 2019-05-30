CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(gameserver)

FIND_PACKAGE(Boost REQUIRED COMPONENTS system)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

SET(CMAKE_CXX_STANDARD 11)
SET(SOURCES 
    src/Connection.cpp
    src/CommunicationChannel.cpp
    src/Server.cpp
    src/Client.cpp
)

ADD_EXECUTABLE(gameserver ${SOURCES} src/server_.cpp)
TARGET_LINK_LIBRARIES(gameserver ${Boost_SYSTEM_LIBRARY})

ADD_EXECUTABLE(gameclient ${SOURCES} src/client_.cpp)
TARGET_LINK_LIBRARIES(gameclient ${Boost_SYSTEM_LIBRARY})


ADD_EXECUTABLE(playground ${SOURCES} src/playground.cpp)
TARGET_LINK_LIBRARIES(playground ${Boost_SYSTEM_LIBRARY})