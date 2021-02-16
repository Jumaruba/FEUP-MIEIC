.POSIX:

CC = gcc
CFLAGS = -Wall -pthread -pedantic -Werror

SRCDIR = src
ODIR = obj

COMMON_SRCS := common_utils.c queue.c handle_log.c
COMMON_SRC  := $(addprefix $(SRCDIR)/, $(COMMON_SRCS))
COMMON_OBJ  := $(addprefix $(ODIR)/, $(COMMON_SRCS:%.c=%.o))

U_TARGET := U2
U_SRCS := u.c u_parseArgs.c
U_SRC  := $(addprefix $(SRCDIR)/, $(U_SRCS))
U_OBJ  := $(addprefix $(ODIR)/, $(U_SRCS:%.c=%.o))

Q_TARGET := Q2
Q_SRCS := q.c q_singleton.c
Q_SRC  := $(addprefix $(SRCDIR)/, $(Q_SRCS))
Q_OBJ  := $(addprefix $(ODIR)/, $(Q_SRCS:%.c=%.o))

default_rule: u q

$(COMMON_OBJ): $(ODIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully"

$(U_OBJ): $(ODIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully"

$(Q_OBJ): $(ODIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully"

.PHONY: u
u: $(COMMON_OBJ) $(U_OBJ)
	@$(CC) -o $(U_TARGET) $(COMMON_OBJ) $(U_OBJ) $(CFLAGS)
	@echo "Linking 'u' complete!"

.PHONY: q
q: $(COMMON_OBJ) $(Q_OBJ)
	@$(CC) -o $(Q_TARGET) $(COMMON_OBJ) $(Q_OBJ) $(CFLAGS)
	@echo "Linking 'q' complete!"

.PHONY: clean
clean:
	@rm -f $(COMMON_OBJ) $(U_OBJ) $(Q_OBJ)
	@echo "Cleaned!"

.PHONY: remove
remove: clean
	@rm -f $(U_TARGET) $(Q_TARGET)
	@echo "Everything was cleared"
