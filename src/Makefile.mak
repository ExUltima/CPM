OUTPUT = cpm.exe
CPPFLAGS = /EHsc
SOURCES = \
	json\errors.cpp \
	json\parser.cpp \
	json\tokenizer.cpp \
	json\value.cpp \
	option\commands.cpp \
	option\errors.cpp \
	option\optionals.cpp \
	option\options.cpp \
	project\config.cpp \
	toolchain\identifiers.cpp \
	exception.cpp \
	filesystem.cpp \
	main.cpp \
	program.cpp \
	project_builder.cpp \
	string.cpp

all: $(OUTPUT)

clean:
	del /s /q /f *.obj
	del $(OUTPUT)

$(OUTPUT): $(SOURCES:.cpp=.obj)
	LINK /OUT:$@ $**

.cpp.obj:
	$(CPP) $(CPPFLAGS) /c /Fo$@ $<
