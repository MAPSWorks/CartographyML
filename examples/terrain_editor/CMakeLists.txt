qt5_add_resources(TERRAIN_EDITOR_QML_SRC qml.qrc)

add_executable(terrain_editor main.cpp ${TERRAIN_EDITOR_QML_SRC})
target_link_libraries(terrain_editor TerrainML ${QT5_WIDGET_LIBRARIES})
