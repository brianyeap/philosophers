Library = philo

CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)

Compiler = gcc
Flags =  -Wall -Wextra -Werror

OUTN = $(Library)
NAME = $(OUTN)

INCLUDES = -I./

all: $(NAME)

$(NAME): $(OFILES)
	$(Compiler) $(Flags) -o $(OUTN) $(OFILES)

%.o: %.c
	$(Compiler) $(Flags) -c $< -o $@ $(INCLUDES)

clean:
	rm -rf $(OFILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re