CC=gcc
CFLAGS=`pkg-config --cflags gtk+-3.0 glib-2.0 gobject-2.0`
LIBS=`pkg-config --libs gtk+-3.0 glib-2.0 gobject-2.0`

SRC=src/main.c src/contact.c src/storage.c
OBJ=build/main.o build/contact.o build/storage.o
EXEC=contact_manager

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

# Compile each source file into object file in the build directory
build/%.o: src/%.c
	mkdir -p build
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf build $(EXEC)