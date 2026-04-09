cmake_minimum_required(VERSION 3.14)

if(POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("hldiscord" CXX)

include(FetchContent)

FetchContent_Declare(
	discord
	GIT_REPOSITORY https://github.com/EclipseMenu/discord-presence.git
	GIT_TAG        main
	GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(discord)

add_library(extension SHARED "src/idl_hl.cpp")

set_target_properties(extension PROPERTIES
	OUTPUT_NAME "discord"
	SUFFIX      ".hdll"
	PREFIX      ""
	CXX_STANDARD 17
)

if(WIN32)
	set_target_properties(extension PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
	target_include_directories(extension PRIVATE "$ENV{HASHLINK}/include")
	target_link_libraries(extension PRIVATE
		"$ENV{HASHLINK}/libhl.lib"
		ole32
		advapi32
	)
endif()

target_include_directories(extension PRIVATE discord-rpc)
target_link_libraries(extension PRIVATE discord-rpc)