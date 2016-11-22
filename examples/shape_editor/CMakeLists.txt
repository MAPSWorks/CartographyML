qt5_add_resources(SHAPE_EDITOR_QML_SRC qml.qrc)

add_executable(shape_editor main.cpp ${SHAPE_EDITOR_QML_SRC})
target_link_libraries(shape_editor CartographerML ${QT5_WIDGET_LIBRARIES})
