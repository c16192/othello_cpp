EXE = othello
SRC = $(wildcard src/*.cpp src/**/*.cpp)
OBJ = $(addprefix build/,$(SRC:.cpp=.o))

all: $(EXE)

$(EXE): $(OBJ)
	@echo 'Building target: $(EXE)'
	@echo 'Invoking: C Linker'
	g++ -g -o $(EXE) $(OBJ)
	@echo 'Finished building target: $(EXE)'
	@echo ' '

build/%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@mkdir -p $(@D)
	g++ -O0 -g -Wall -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

clean:
	rm -f build/*.o $(EXE)*
