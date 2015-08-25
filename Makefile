# Makefile

CXXFLAGS+=-std=c++0x

all : auto decltype move

% : %.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) $< -o $@
