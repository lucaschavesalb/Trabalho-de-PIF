CC = gcc                     # Compilador a ser usado (gcc)
CFLAGS = -Wall -Wextra -g    # Flags: avisos extras + debug
OBJ = main.o board.o fleet.o game.o io.o rnd.o   # Arquivos objeto (.o)
EXEC = batalha_naval         # Nome do executável final

all: $(EXEC)                 # Regra padrão: compilar o executável

$(EXEC): $(OBJ)              # Gera o executável a partir dos .o
	$(CC) $(CFLAGS) -o $@ $^  # $@ = alvo (EXEC) | $^ = dependências (OBJ)

%.o: %.c                     # Regra genérica: .c vira .o
	$(CC) $(CFLAGS) -c $< -o $@   # $< = arquivo fonte | $@ = arquivo objeto

clean:
	rm -f $(OBJ) $(EXEC)         
# Remove arquivos .o e o executável