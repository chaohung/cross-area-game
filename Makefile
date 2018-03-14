CXX = g++
PROG = main

all: $(PROG)

%: %.cpp
	$(CXX) $< -o $@

run: $(PROG)
	@./$(PROG)

clean:
	$(RM) $(PROG)
