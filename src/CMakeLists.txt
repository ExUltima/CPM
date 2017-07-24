add_executable (cpm
	exception.cpp
	exception.hpp
	json.cpp
	json.hpp
	main.cpp
	program_options.cpp
	program_options.hpp
	program_options.inl
	program.cpp
	program.hpp
	project_builder.cpp
	project_builder.hpp
	string.cpp
	string.hpp
	string.inl
)

if (NOT MSVC)
	target_link_libraries (cpm stdc++fs)
endif ()