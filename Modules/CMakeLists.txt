set(HEADERS
    Publisher.h
    Subscriber.h
    FrameGrabber.h
    ReconstructionMod.h
    DetectionMod.h
    VisualizationMod.h
)

set(SOURCES
    Publisher.cpp
    Subscriber.cpp
    FrameGrabber.cpp
    ReconstructionMod.cpp
    DetectionMod.cpp
    VisualizationMod.cpp
)

add_library(Modules ${SOURCES})
set_target_properties(Modules PROPERTIES LINKER_LANGUAGE CXX)
include_directories(${PROJECT_SOURCE_DIR})
target_link_libraries(Modules ${Visiontransfer_LIB} ${Open3D_LIBRARIES} ${OpenCV_LIBS} ${EXTRA_LIBS})
