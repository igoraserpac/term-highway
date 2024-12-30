# Nome do executável
EXEC = main

# Compilador
CXX = g++

# Flags do compilador
CXXFLAGS = -Wall -Wextra -std=c++17

# Flags para linkagem da biblioteca curses
LDFLAGS = -lcurses

# Diretório com os arquivos fonte e cabeçalhos
SRC_DIR = .
OBJ_DIR = obj

# Lista de fontes e cabeçalhos
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Regra padrão
all: $(EXEC)

# Compilar o executável
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compilar objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar os objetos e o executável
clean:
	rm -rf $(OBJ_DIR) $(EXEC)

# Remover apenas os objetos
clean_objs:
	rm -rf $(OBJ_DIR)

# Phony targets
.PHONY: all clean clean_objs
