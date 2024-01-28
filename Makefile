OBJS = main.o read.o parse.o exec.o
EXEC = shell.exe

$(EXEC): $(OBJS)
	cc -o $(EXEC) $(OBJS)

cleanup:
	@rm -f $(EXEC) $(OBJS)

test: $(EXEC)
	./$(EXEC)
