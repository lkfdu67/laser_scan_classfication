add_library(ranging STATIC
        camera.cpp
        classify.cpp
        calculate.cpp
        cross_center.cpp
        )

target_link_libraries(
        ranging
        ${THIRD_PARTY_LIBS}
        )