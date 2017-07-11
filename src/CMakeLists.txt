add_executable (cpm
	exception.cpp
	exception.hpp
	main.cpp
	program_options.cpp
	program_options.hpp
	program_options.inl
	program.cpp
	program.hpp
	string.cpp
	string.hpp
	string.inl
)

if (NOT MSVC)
	target_link_libraries (cpm stdc++fs)
endif ()