qt5_add_resources(TERRAIN_EDITOR_QML_SRC qml.qrc)

add_executable(terrain_viewer_3d main.cpp ${TERRAIN_EDITOR_QML_SRC})
target_link_libraries(terrain_viewer_3d TerrainML3D Qt5::3DQuickExtras ${QT5_WIDGET_LIBRARIES})
