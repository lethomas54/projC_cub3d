NAME		:=		libft.a

COMP		:=		cc
CFLAGS		:=		-Wall -Wextra -Werror

SRC_io		:= 		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
					ft_putnbr_fd.c get_next_line.c ft_printf.c \
					ft_putnbr_flag.c ft_putpointer_flag.c ft_putstr_flag.c \
					ft_setflag.c ft_conversion.c

SRC_string	:= 		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
					ft_isprint.c ft_toupper.c ft_tolower.c ft_strlen.c \
					ft_strchr.c ft_strrchr.c ft_strlcpy.c ft_strlcat.c \
					ft_strncmp.c ft_strnstr.c ft_strdup.c ft_striteri.c \
					ft_strmapi.c ft_substr.c ft_strtrim.c ft_strjoin.c \
					ft_split.c ft_atoi.c ft_atod.c ft_itoa.c \
					ft_itoa.c

SRC_memory	:= 		ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
					ft_memchr.c ft_memcmp.c ft_calloc.c ft_free.c

SRC_list	:= 		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
					ft_lstadd_back.c  ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
					ft_lstmap.c ft_lstshift.c

SRC_btree	:=		ft_btree_create_node.c ft_btree_apply_infix.c ft_btree_apply_prefix.c \
					ft_btree_apply_suffix.c ft_btree_insert_data.c ft_btree_level_count.c \
					ft_btree_search_item.c ft_btree_clear.c

SRC_other	:= 		ft_ternary_op.c

SRCS_io		:= 		$(addprefix ./srcs/io/, $(SRC_io))
SRCS_string	:= 		$(addprefix ./srcs/string/, $(SRC_string))
SRCS_memory	:= 		$(addprefix ./srcs/memory/, $(SRC_memory))
SRCS_list	:= 		$(addprefix ./srcs/list/, $(SRC_list))
SRCS_btree	:= 		$(addprefix ./srcs/btree/, $(SRC_btree))
SRCS_other	:= 		$(addprefix ./srcs/other/, $(SRC_other))
SRCS		:= 		$(SRCS_io) $(SRCS_string) $(SRCS_memory) $(SRCS_list) $(SRCS_btree) $(SRCS_other)
OBJ			:=		$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rsc $(NAME) $(OBJ)

%.o: %.c
	@$(COMP) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ) $(NAME)

re: fclean all

.PHONY: all clean fclean re
