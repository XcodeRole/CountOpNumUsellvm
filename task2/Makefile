CXX=clang++
CC=clang

CXXFLAGS=$(shell llvm-config --cxxflags)
LDFLAGS=$(shell llvm-config --ldflags)

CXXFLAGS+= -fPIC
LDFLAGS+= -shared

# target=$(shell find . -name \*.cpp | sed "s/.cpp/.so/")
target=InsertFunctionPass.so
all:$(target)
	
%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.so:%.o
	$(CXX) $(LDFLAGS) -o $@ $<

.PHONY:clean

clean:
	rm -rf *.so *.ll *.bc *.o


