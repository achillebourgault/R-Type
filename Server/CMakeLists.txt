set(SERVER_SRC
        main.cpp
        ../Shared/BinaryPacket.cpp
        Source/Server.cpp
        Source/ServerNetworking.cpp
        ../Shared/GameState.h
        ../Shared/MonsterHandler.cpp
        Include/CollisionHandler.cpp Include/CollisionHandler.hpp)
find_package(Threads)
add_executable(r-type_server ${SERVER_SRC})

include_directories(r-type_server ${CONAN_INCLUDE_DIRS} Include ../Shared/)

target_link_libraries(r-type_server
        Threads::Threads
        ${CONAN_LIBS}
)