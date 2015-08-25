# Makefile

CXXFLAGS+=-std=c++0x

all : auto

% : %.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) $< -o $@
