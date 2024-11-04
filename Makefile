# Nombre del compilador
CC = gcc

# Opciones del compilador
CFLAGS = -Wall -Wextra -std=c11

# Opciones del enlazador
LDFLAGS = -lm

# Archivos fuente
SRCS_VECTOR = main-vector.c
SRCS_KDTREE = main-kdtree.c

# Archivos ejecutables
TARGET_VECTOR = main-vector
TARGET_KDTREE = main-kdtree

# Regla por defecto
all: $(TARGET_VECTOR) $(TARGET_KDTREE)

# Regla para compilar el archivo ejecutable main-vector
$(TARGET_VECTOR): $(SRCS_VECTOR)
	$(CC) $(CFLAGS) -o $(TARGET_VECTOR) $(SRCS_VECTOR) $(LDFLAGS)

# Regla para compilar el archivo ejecutable main-kdtree
$(TARGET_KDTREE): $(SRCS_KDTREE)
	$(CC) $(CFLAGS) -o $(TARGET_KDTREE) $(SRCS_KDTREE) $(LDFLAGS)

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET_VECTOR) $(TARGET_KDTREE)

# Regla para ejecutar y medir el tiempo de main-vector
run-vector: $(TARGET_VECTOR)
	@echo "Ejecutando main-vector:"
	@time ./$(TARGET_VECTOR)

# Regla para ejecutar y medir el tiempo de main-kdtree
run-kdtree: $(TARGET_KDTREE)
	@echo "Ejecutando main-kdtree:"
	@time ./$(TARGET_KDTREE)

# Regla para ejecutar ambos programas y medir el tiempo
run: run-vector run-kdtree

.PHONY: all clean run run-vector run-kdtree