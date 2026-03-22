add_library(hldiscord SHARED "extension.cpp" "extension.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET hldiscord PROPERTY CXX_STANDARD 20)
endif()

set_target_properties(hldiscord PROPERTIES
	OUTPUT_NAME "discord"
	SUFFIX ".hdll")

target_include_directories(hldiscord PRIVATE "$ENV{HASHLINK}/include")
target_link_libraries(hldiscord PRIVATE "$ENV{HASHLINK}/libhl.lib")

add_subdirectory("libs/discord-presence")
target_include_directories(hldiscord PRIVATE "libs/discord-presence/include")
target_link_libraries(hldiscord PRIVATE discord-rpc)