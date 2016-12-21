qt5_add_resources(WORLD_VIEWER_QML_SRC qml.qrc data.qrc)

add_executable(world_viewer main.cpp ${WORLD_VIEWER_QML_SRC})
target_link_libraries(world_viewer MapnikML )


