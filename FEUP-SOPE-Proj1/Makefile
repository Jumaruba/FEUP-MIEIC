.POSIX:

TARGET = simpledu

CC = gcc
CFLAGS = -Wall # -Werror

SRCDIR = src
ODIR = obj

SRCS := simpledu.c utils.c showDirec.c queue.c handleLog.c handleSignal.c
SRC  := $(addprefix $(SRCDIR)/, $(SRCS))
OBJ  := $(addprefix $(ODIR)/, $(SRCS:%.c=%.o))

$(TARGET): $(OBJ)
	@$(CC) -o $@ $(OBJ) $(CFLAGS)
	@echo "Linking complete!"

$(OBJ): $(ODIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully"

.PHONY: clean
clean:
	@rm -f $(OBJ)
	@echo "Cleaned!"

.PHONY: remove
remove: clean
	@rm -f $(TARGET)
	@echo "Everything was cleared"
