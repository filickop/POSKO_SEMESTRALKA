CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -pthread  # Add any additional linker flags here

SERVER_SRC = Server.c SpolocneData.c Main.c  # List of server source files
CLIENT_SRC = Client.c SpolocneData.c Main.c  # List of client source files

SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

EXEC_SERVER = server
EXEC_CLIENT = client

all: server client

server: $(SERVER_OBJ)
    $(CC) $(SERVER_OBJ) -o $(EXEC_SERVER) $(LDFLAGS)

client: $(CLIENT_OBJ)
    $(CC) $(CLIENT_OBJ) -o $(EXEC_CLIENT) $(LDFLAGS)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(SERVER_OBJ) $(CLIENT_OBJ) $(EXEC_SERVER) $(EXEC_CLIENT)