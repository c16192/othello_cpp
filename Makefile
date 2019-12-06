EXE = othello
SRC_DIR = src/
SRC = $(wildcard $(SRC_DIR)*.cpp $(SRC_DIR)**/*.cpp)
_OBJ = $(SRC:.cpp=.o)
OBJ = $(addprefix build/,$(_OBJ:$(SRC_DIR)%=%))

all: $(EXE)

$(EXE): $(OBJ)
	@echo 'Building target: $(EXE)'
	@echo 'Invoking: C++ Linker'
	g++ -g -o $(EXE) $(OBJ)
	@echo 'Finished building target: $(EXE)'
	@echo ' '

build/%.o: $(SRC_DIR)%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: G++ C++ Compiler'
	@mkdir -p $(@D)
	g++ -O0 -g -Wall -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

clean:
	rm -R build $(EXE)*
