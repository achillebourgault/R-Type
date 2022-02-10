set(CLIENT_SRC
        main.cpp
        Source/Client.cpp
        ../Shared/RType.h
        ../Shared/ECS/ECS.hpp
        ../Shared/ECS/Manager.cpp
        ../Shared/ECS/Entity.cpp
        ../Shared/ECS/Scene.hpp
        ../Shared/BinaryPacket.cpp
        Source/Components/GUI/TextComp.cpp
        Source/Components/GUI/InputTextComp.cpp
        Source/Scenes/MenuScene.cpp
        Source/Mediator.cpp
        Include/Mediator.hpp
        ../Shared/GameState.h
        )

set(CLIENT_COMPONENTS
        Source/Components/GUI/BackgroundComponent.cpp
        Source/Components/TransformComp.cpp
        Source/Components/AudioComp.cpp
        Source/ClientNetworking.cpp
        Source/Components/GUI/TextButton.cpp
        Source/Components/GUI/InputTextComp.cpp
        Source/Components/GUI/SubPanelComp.cpp
        Source/Components/GUI/ChatComp.cpp
        Source/Components/SpriteComp.cpp
        Source/Components/AssetLoader.cpp
        Source/Components/GUI/AnimatedComp.cpp
        Source/Components/GUI/AnimatedComp.cpp

        Source/Scenes/GameScene.cpp
        Source/Scenes/MenuScene.cpp
        Source/Scenes/OptionsScene.cpp
        Source/Scenes/ScoresScene.cpp
        Source/Scenes/ConnectScene.cpp
        Source/Scenes/LaunchScene.cpp
        Source/Scenes/GameOverScene.cpp

        Source/Traductions.cpp

        Source/Components/Player/PlayerMovementComp.cpp
        Source/Components/ProjectileComp.cpp
        Include/Components/ProjectileComp.hpp
        Source/Components/Player/PlayerComp.cpp
        Include/Components/Player/PlayerComp.hpp
        Source/Components/Player/PlayerShootComp.cpp
        Include/Components/Player/PlayerShootComp.hpp
        Source/Components/Player/PlayerForceBar.cpp
        Include/Components/Player/PlayerForceBar.hpp
        Source/Components/Player/PlayerHUDComp.cpp
        Include/Components/Player/PlayerHUDComp.hpp
        Source/Components/GUI/ListSelectorComp.cpp
        Include/Components/GUI/ListSelectorComp.hpp
        Source/Scenes/LobbyScene.cpp
        Include/Scenes/LobbyScene.hpp
        Include/Scenes/GameOverScene.hpp
        Source/LobbyComp.cpp
        Include/Components/LobbyComp.hpp
        Source/Components/MonsterComp.cpp Include/Components/MonsterComp.hpp Source/Components/MonsterManager.cpp Include/Components/MonsterManager.hpp Source/Components/ExplosionFxComp.cpp Include/Components/ExplosionFxComp.hpp)

add_executable(r-type_client ${CLIENT_SRC} ${CLIENT_COMPONENTS})

include_directories(r-type_client ${CONAN_INCLUDE_DIRS} Include Include/Components Include/ECS ../Shared/)

target_link_libraries(r-type_client
        ${CONAN_LIBS}
)