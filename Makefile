
CC= gcc
CFLAGS= -Wall -Werror -Wextra
RM= rm -f
NAME= minitalk
SERVER= server
CLIENT= client
BCLIENT= client_bonus
BSERVER= server_bonus
HEADER= minitalk.h

ODIR= obj

S_SOURCE= server.c
C_SOURCE= client.c
BS_SOURCE= server_bonus.c
BC_SOURCE= client_bonus.c

S_OBJECT= $(addprefix $(ODIR)/,$(S_SOURCE:.c=.o))
C_OBJECT= $(addprefix $(ODIR)/,$(C_SOURCE:.c=.o))
BS_OBJECT= $(addprefix $(ODIR)/,$(BS_SOURCE:.c=.o))
BC_OBJECT= $(addprefix $(ODIR)/,$(BC_SOURCE:.c=.o))

LIBFT = libft/libft.a

all: libft $(SERVER) $(CLIENT)

bonus: libft $(BSERVER) $(BCLIENT)

$(NAME): all

$(SERVER): $(S_OBJECT) | $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ -L./libft -lft

$(CLIENT): $(C_OBJECT) | $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ -L./libft -lft

$(BSERVER): $(BS_OBJECT) | $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ -L./libft -lft

$(BCLIENT): $(BC_OBJECT) | $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ -L./libft -lft


$(ODIR):
	@mkdir -p $@

git_submodule_update:
	@git submodule deinit -f libft
	rm -rf .git/modules/libft
	@git submodule update --init --recursive

libft: git_submodule_update
	@make -sC ./libft

$(ODIR)/%.o: %.c $(HEADER) | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(ODIR)
	@make clean -sC ./libft

fclean: clean
	$(RM) $(SERVER) $(CLIENT) $(BCLIENT) $(BSERVER)
	@make fclean -sC ./libft

re: fclean all

.PHONY: all bonus clean fclean re libft
