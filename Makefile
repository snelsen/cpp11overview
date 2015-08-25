# Makefile

#CXXFLAGS+=-std=c++0x
CXXFLAGS+=-std=c++11 -O2 -Wall

binaries=auto decltype move1 move2 lambda pointers

all : auto $(binaries)

% : %.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) $< -o $@

clean :
	$(RM) $(binaries) *.o

distclean : clean
	$(RM) *~

