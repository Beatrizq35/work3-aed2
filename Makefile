CC     = gcc
CFLAGS = -Wall -Wextra

SRCS = main.c Registro.c IndiceArvBST.c IndiceArvCR.c \
       IndiceHash.c BuscaSeq.c metricas.c
OBJS = $(SRCS:.c=.o)
TARGET = prog

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) alunos.dat

.PHONY: all clean
