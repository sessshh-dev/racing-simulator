add_library(racing_lib SHARED
    GroundVehicle.cpp
    AirVehicle.cpp
    Race.cpp
)

target_include_directories(racing_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
