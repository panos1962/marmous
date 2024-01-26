OBJS = main.o
EXEC = shell.exe

$(EXEC): $(OBJS)
	cc -o $(EXEC) $(OBJS)

test: $(EXEC)
	./$(EXEC)
