# Makefile

CXXFLAGS+=-std=c++0x

all : auto decltype

% : %.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) $< -o $@
