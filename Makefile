# Makefile

#CXXFLAGS+=-std=c++0x
CXXFLAGS+=-std=c++11

all : auto decltype move

% : %.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) $< -o $@
