qt5_add_resources(TERRAIN_MOSAIC_QML_SRC qml.qrc)

add_executable(terrain_mosaic TestDatasource.cpp main.cpp ${TERRAIN_MOSAIC_QML_SRC})
target_link_libraries(terrain_mosaic TerrainML ${QT5_WIDGET_LIBRARIES})

