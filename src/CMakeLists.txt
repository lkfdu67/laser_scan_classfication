add_library(ranging STATIC
        camera.cpp
        )

target_link_libraries(
        ranging
        ${THIRD_PARTY_LIBS}
        )