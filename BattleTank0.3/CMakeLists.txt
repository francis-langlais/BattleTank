cmake_minimum_required(VERSION 3.13)
project(BattleTank0_1)

set ( Protobuf_USE_STATIC_LIBS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${BattleTank0_1_SOURCE_DIR}/cmake")

INCLUDE(FindProtobuf)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Protobuf REQUIRED)

PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER test.proto)

set(EXECUTABLE_NAME "BattleTank0_1")
add_executable(${EXECUTABLE_NAME} main.cpp spriteSheetAnim.cpp spriteSheetAnim.h
        Map.cpp Map.h Game.cpp Game.h TextureManager.cpp TextureManager.h ECS/ECS.h ECS/SpriteComponent.h ECS/Components.h
        Vector2D.h ECS/TransformComponent.h EngineMath.h ECS/ColliderComponent.h Collider.h CollisionDetection.cpp
        CollisionDetection.h ECS/ECS.cpp ECS/Animation.h AssetManager.cpp AssetManager.h ECS/ProjectileComponent.h
        ECS/KeyboardController.h Collider.cpp ECS/TileComponent.h protocolbuffer/test.pb.h protocolbuffer/test.pb.cc
        ECS/NetworkController.h MiniMap.cpp MiniMap.h UI/TextBox.cpp UI/TextBox.h UI/ProgressBar.cpp UI/ProgressBar.h)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${PROTOBUF_INCLUDE_DIRS})

target_link_libraries(${EXECUTABLE_NAME} ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${PROTOBUF_LIBRARY})
        #${PROTOBUF_LITE_LIBRARY})

