template<>
inline program_command from_string<program_command>(std::string const & s)
{
	if (s == "build") {
		return program_command::build;
	} else {
		throw std::invalid_argument("command string is not valid");
	}
}
