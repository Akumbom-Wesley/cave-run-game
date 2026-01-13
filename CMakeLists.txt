cmake_minimum_required(VERSION 3.28)
project(CaveRunGame)

set(CMAKE_CXX_STANDARD 14)

# SFML path
set(SFML_DIR "C:/SFML-2.6.2")

# Include directories
include_directories(${SFML_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/entities)
include_directories(${PROJECT_SOURCE_DIR}/src/world)
include_directories(${PROJECT_SOURCE_DIR}/src/core)
include_directories(${PROJECT_SOURCE_DIR}/src/gui)
include_directories(${PROJECT_SOURCE_DIR}/src/gui/renderers)
include_directories(${PROJECT_SOURCE_DIR}/src/handlers)

# Link directories
link_directories(${SFML_DIR}/lib)

# Source files organized by module
set(ENTITY_SOURCES
        src/entities/Character.cpp
        src/entities/Player.cpp
        src/entities/Monster.cpp
)

set(WORLD_SOURCES
        src/world/Position.cpp
        src/world/Map.cpp
        src/world/MapGenerator.cpp
        src/world/Room.cpp
        src/world/PoisonRoom.cpp
        src/world/TrapRoom.cpp
        src/world/HealingRoom.cpp
        src/world/PowerUpRoom.cpp
)

set(CORE_SOURCES
        src/core/Game.cpp
)

set(RENDERER_SOURCES
        src/gui/renderers/Renderer.cpp
        src/gui/renderers/GridRenderer.cpp
        src/gui/renderers/RoomRenderer.cpp
        src/gui/renderers/CharacterRenderer.cpp
        src/gui/renderers/UIRenderer.cpp
)

set(GUI_SOURCES
        src/gui/GameGUI.cpp
        src/gui/InputHandler.cpp
        src/gui/NotificationManager.cpp
        src/gui/GameGUI.cpp
        src/gui/InputHandler.cpp
        src/gui/NotificationManager.cpp
        src/gui/GameOverScreen.cpp
        src/gui/TurnManager.cpp
        src/gui/MoveExecutor.cpp
        ${RENDERER_SOURCES}
        ${RENDERER_SOURCES}
)

set(HANDLER_SOURCES
        # src/handlers/GameOverHandler.cpp  # Uncomment if you create .cpp
)

# Combine all sources
set(ALL_SOURCES
        main.cpp
        ${ENTITY_SOURCES}
        ${WORLD_SOURCES}
        ${CORE_SOURCES}
        ${GUI_SOURCES}
        ${HANDLER_SOURCES}
        src/gui/GameOverScreen.h
        src/gui/GameOverScreen.cpp
        src/gui/TurnManager.h
        src/gui/TurnManager.cpp
        src/gui/MoveExecutor.cpp
        src/gui/MoveExecutor.h
)

# Create executable
add_executable(CaveRunGame ${ALL_SOURCES})

# Link SFML libraries (debug versions)
target_link_libraries(CaveRunGame
        sfml-graphics-d
        sfml-window-d
        sfml-system-d
)

# Copy DLL files after build
add_custom_command(TARGET CaveRunGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_DIR}/bin/sfml-graphics-d-2.dll"
        "${SFML_DIR}/bin/sfml-window-d-2.dll"
        "${SFML_DIR}/bin/sfml-system-d-2.dll"
        $<TARGET_FILE_DIR:CaveRunGame>
)

# Optional: Add source groups for IDE organization
source_group("Entities" FILES ${ENTITY_SOURCES})
source_group("World" FILES ${WORLD_SOURCES})
source_group("Core" FILES ${CORE_SOURCES})
source_group("GUI" FILES ${GUI_SOURCES})
source_group("GUI\\Renderers" FILES ${RENDERER_SOURCES})
source_group("Handlers" FILES ${HANDLER_SOURCES})
