# Répertoires
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Nom de l'exécutable
TARGET = $(BIN_DIR)/main

# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++17 -I$(INC_DIR) -Wall -Wextra

# Fichiers source et objets
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/point.cpp $(SRC_DIR)/arc.cpp $(SRC_DIR)/arcE.cpp $(SRC_DIR)/noeud.cpp $(SRC_DIR)/noeudV.cpp $(SRC_DIR)/graphe.cpp
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Cible par défaut : créer l'exécutable
$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Règle pour compiler chaque fichier objet
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers générés
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)