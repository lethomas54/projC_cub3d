########################################################################################
#----------------------------------EXEC_NAME-------------------------------------------#
########################################################################################

NAME		:= philo

########################################################################################
#-------------------------------COMPILER_OPTION----------------------------------------#
########################################################################################

COMP		:=	cc
CFLAGS		:=	-g -fsanitize=address -Wall -Wextra -Werror

########################################################################################
#------------------------------SOURCE+OBJECT_FILE--------------------------------------#
########################################################################################

SRC			:=	main.c ft_init_philo.c ft_create_thread.c \
				ft_free_destroy.c ft_thread_routine.c \
				ft_philo_utils.c

SRCS		:= $(addprefix ./srcs/, $(SRC))
OBJ 		:= $(SRCS:.c=.o)

########################################################################################
#---------------------------------HEADER_FILE------------------------------------------#
########################################################################################

INC			:= philosopher.h
INCS		:= $(addprefix ./includes/, $(INC))

########################################################################################
#-----------------------------------LIB_VAR--------------------------------------------#
########################################################################################

LIBPATH 	:= ../libft/
LIBNAME 	:= $(LIBPATH)libft.a

########################################################################################
#-----------------------------------COLOR_VAR------------------------------------------#
########################################################################################

RED 			:= \033[0;31m
GREEN			:= \033[0;32m
RED_BOLD 		:= \033[1;31m
WHITE 			:= \033[0;0m

########################################################################################
#-----------------------------------PROGRESS_BAR---------------------------------------#
########################################################################################

TOTAL_FILES 	:= $(words $(SRCS))
CURRENT_FILE 	:= $(shell find ./srcs/ -name "*.o" -newer $(MAKEFILE_LIST) | wc -l)
PROG_BAR_INIT	:= 0
SET_CURSOR		:= \033[?25h
UNSET_CURSOR	:= \033[?25l

LINE_1			:=	"                    hhhhhhh               iiii  lllllll                  "
LINE_2			:=	"                    h:::::h              i::::i l:::::l                  "
LINE_3			:=	"                    h:::::h               iiii  l:::::l                  "
LINE_4			:=	"                    h:::::h                     l:::::l                  "
LINE_5			:=	"ppppp   ppppppppp    h::::h hhhhh       iiiiiii  l::::l    ooooooooooo   "
LINE_6			:=	"p::::ppp:::::::::p   h::::hh:::::hhh    i:::::i  l::::l  oo:::::::::::oo "
LINE_7			:=	"p:::::::::::::::::p  h::::::::::::::hh   i::::i  l::::l o:::::::::::::::o"
LINE_8			:=	"pp::::::ppppp::::::p h:::::::hhh::::::h  i::::i  l::::l o:::::ooooo:::::o"
LINE_9			:=	" p:::::p     p:::::p h::::::h   h::::::h i::::i  l::::l o::::o     o::::o"
LINE_10			:=	" p:::::p     p:::::p h:::::h     h:::::h i::::i  l::::l o::::o     o::::o"
LINE_11			:=	" p:::::p     p:::::p h:::::h     h:::::h i::::i  l::::l o::::o     o::::o"
LINE_12			:=	" p:::::p    p::::::p h:::::h     h:::::h i::::i  l::::l o::::o     o::::o"
LINE_13			:=	" p:::::ppppp:::::::p h:::::h     h:::::hi::::::il::::::lo:::::ooooo:::::o"
LINE_14			:=	" p::::::::::::::::p  h:::::h     h:::::hi::::::il::::::lo:::::::::::::::o"
LINE_15			:=	" p::::::::::::::pp   h:::::h     h:::::hi::::::il::::::l oo:::::::::::oo "
LINE_16			:=	" p::::::pppppppp     hhhhhhh     hhhhhhhiiiiiiiillllllll   ooooooooooo   "
LINE_17			:=	" p:::::p                                                                 "
LINE_18			:=	" p:::::p                                                                 "
LINE_19			:=	"p:::::::p                                                                "
LINE_20			:=	"p:::::::p                                                                "
LINE_21			:=	"p:::::::p                                                                "
LINE_22			:=	"ppppppppp                                                                "

LINE_COUNT		:= 22

LINES			:= $(foreach elem,$(shell for i in {1..$(LINE_COUNT)}; do printf "LINE_%d " $$i; done),$($(elem)))
LINE_SIZES		:= $(foreach elem,$(shell for i in {1..$(LINE_COUNT)}; do printf "LINE_%d " $$i; done),$(shell wc -c <<< $($(elem)) | tr -d ' '))

define progress_bar
	@$(eval CURRENT_FILE := $(shell echo $$(($(CURRENT_FILE) + 1))))
	@$(call progress_bar_2, $(CURRENT_FILE))
    @$(eval PROG_BAR_INIT := 1)
endef

define progress_bar_2
	@printf "$(UNSET_CURSOR)"
	@if [ $(PROG_BAR_INIT) -eq 0 ]; then printf "\n$(RED)$(shell for i in {1..$(LINE_COUNT)}; do printf '%%s\\n'; done)\n\n" $(LINES); fi
	@printf "\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\r";
	@printf "$(GREEN)$(shell for i in $(LINE_SIZES); do printf '%%.%ds\\n' $$(($$i*$(1)/$(TOTAL_FILES))); done) \n%d/%d\n" $(LINES) $(1) $(TOTAL_FILES)
	@if [ $(1) -eq $(TOTAL_FILES) ]; then echo "$(RED_BOLD)\t\t\tPhilo ready!\n"; fi
	@printf "$(SET_CURSOR)$(WHITE)"
endef

########################################################################################
#-------------------------------------MAKEFILE_RULE------------------------------------#
########################################################################################

all: $(NAME)

bonus: $(NAME_bonus)

$(NAME): $(LIBNAME) $(OBJ)
	@$(COMP) $(CFLAGS) $(OBJ) -o $@ -L $(LIBPATH) -lft

$(LIBNAME):
	@make -C $(LIBPATH) all

%.o: %.c $(INCS)
	@$(COMP) $(CFLAGS) -c $< -o $@
	@$(call progress_bar)

clean:
	@make -C $(LIBPATH) clean
	@rm -f $(OBJ)
	@echo "$(RED_BOLD)$(NAME) clean: $(GREEN)OK$(WHITE)"
	@$(eval CURRENT_FILE := 0)

fclean:
	@make -C $(LIBPATH) fclean
	@rm -f $(OBJ) $(NAME)
	@echo "$(RED_BOLD)$(NAME) fclean: $(GREEN)OK$(WHITE)"
	@$(eval CURRENT_FILE := 0)

re: fclean all

.PHONY: all clean fclean re
