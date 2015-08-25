# Makefile

#CXXFLAGS+=-std=c++0x
CXXFLAGS+=-std=c++11 -O2 -Wall

binaries=decltype move

all : auto $(binaries)

% : %.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) $< -o $@

clean :
	$(RM) $(binaries) *.o

