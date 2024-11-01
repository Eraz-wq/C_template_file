
TARGET = c_template
# C++ Source Code Files
CXXFILES = c_template.cc c_template_functions.cc
# C++ Headers Files
HEADERS = c_template_functions.h

CXX = clang++
CXXFLAGS += -g -O3 -Wall -pedantic -pipe -std=c++17
LDFLAGS += -g -O3 -Wall -pedantic -pipe -std=c++17

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CXXFLAGS += -D LINUX
	LDFLAGS += 
	SED = sed
	GTESTINCLUDE = -D LINUX
	GTESTLIBS = -L /usr/lib/gcc/x86_64-linux-gnu/11 -lgtest -lgtest_main -lpthread
	# Note in Ubuntu 22 clang++ has it's own std. library
	# clang++ -nostdinc++ -nostdlib++ -isystem /usr/lib/llvm-14/include/c++/v1 -L /usr/lib/llvm-14/lib -Wl,-rpath,/usr/lib/llvm-14/lib -lc++ -std=c++17 
endif
ifeq ($(UNAME_S),Darwin)
	ifeq (,$(wildcard "/opt/local/bin/port"))
		# Use MacPorts clang++'s standard library
		CXXFLAGS += -D OSX
		LDFLAGS += 
		SED = gsed
		GTESTINCLUDE = -I /opt/local/include -I /opt/local/src/googletest
		GTESTLIBS = -L /opt/local/libexec/llvm-18/lib/libc++ -L /opt/local/libexec/llvm-18/lib -L /opt/local/lib -lgtest -lgtest_main -lunwind -rpath /opt/local/libexec/llvm-18/lib/libc++ -rpath /opt/local/libexec/llvm-18/lib
	else
		# Use Apple's standard library (not recommended)
		CXXFLAGS += -D OSX
	endif
endif
UNAME_M = $(shell uname -m)
ifeq ($(UNAME_M),x86_64)
	CXXFLAGS += -D AMD64
endif
ifneq ($(filter %86,$(UNAME_M)),)
	CXXFLAGS += -D IA32
endif
ifneq ($(filter arm%,$(UNAME_M)),)
	CXXFLAGS += -D ARM
endif

FORMATTER = clang-format
FORMATTERFLAGS = -style=file --Werror -i

LINTER = clang-tidy
LINTERFLAGS = --config-file=.clang-tidy
LINTERCOMPILECMD = -- -Wall -std=c++17 -x c++

OBJECTS = $(CXXFILES:.cc=.o)

DEP = $(CXXFILES:.cc=.d)

default all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LLDLIBS)

-include $(DEP)

%.d: %.cc
	set -e; $(CXX) -MM $(CXXFLAGS) $< 	| sed 's/\($*\)\.o[ :]*/.o $@ : /g' > $@; 	[ -s $@ ] || rm -f $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

clean:
	-rm -f $(OBJECTS) core $(TARGET).core

spotless: clean
	-rm -f $(TARGET) $(DEP) a.out
	-rm -rf $(DOCDIR)
	-rm -rf $(TARGET).dSYM
	-rm -f compile_commands.json

format: $(CXXFILES) $(HEADERS)
	$(FORMATTER) $(FORMATTERFLAGS) $(CXXFILES) $(HEADERS)

lint:
	$(LINTER) $(LINTERFLAGS) $(CXXFILES) $(HEADERS) $(LINTERCOMPILECMD)

        
