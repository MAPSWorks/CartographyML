qt5_add_resources(SHAPE_VIEWER_QML_SRC qml.qrc)

add_executable(shape_viewer main.cpp ${SHAPE_VIEWER_QML_SRC})
target_link_libraries(shape_viewer MapnikML ${QT5_WIDGET_LIBRARIES})


