########################################################################################
#----------------------------------EXEC_NAME-------------------------------------------#
########################################################################################

NAME		:= cub3d
NAME_BONUS	:= cub3d_bonus

########################################################################################
#-------------------------------COMPILER_OPTION----------------------------------------#
########################################################################################

COMP		:=	cc
CFLAGS		:=	-g -fsanitize=address -Wall -Wextra -Werror

########################################################################################
#------------------------------SOURCE+OBJECT_FILE--------------------------------------#
########################################################################################

SRC			:=	main.c draw_on_screen.c get_wall_distance.c fill_img.c \
				fill_with_texture.c event_hook_routine.c vector_utils.c

SRCS		:= $(addprefix ./srcs/, $(SRC))
OBJ 		:= $(SRCS:.c=.o)

SRC_BONUS	:=	main_bonus.c set_sprite_bonus.c draw_on_screen_bonus.c \
				get_wall_distance_bonus.c draw_wall_bonus.c \
				fill_wall_col_with_texture_bonus.c draw_weapon_bonus.c \
				draw_floor_ceiling_bonus.c event_hook_routine_bonus.c \
				update_player_data_bonus.c update_spritesheet_index_bonus.c \
				vec_operation_bonus.c exit_bonus.c get_time_bonus.c

SRCS_BONUS	:= $(addprefix ./srcs_bonus/, $(SRC_BONUS))
OBJ_BONUS 	:= $(SRCS_BONUS:.c=.o)

########################################################################################
#---------------------------------HEADER_FILE------------------------------------------#
########################################################################################

INC			:= cub3d.h
INCS		:= $(addprefix ./includes/, $(INC))

INC_BONUS	:= cub3d_bonus.h
INCS_BONUS	:= $(addprefix ./includes_bonus/, $(INC_BONUS))

########################################################################################
#-----------------------------------LIB_VAR--------------------------------------------#
########################################################################################

LIBPATH 	:= ./libft/
LIBNAME 	:= $(LIBPATH)libft.a

MLXPATH		:= ./mlx/
MLXNAME		:= $(MLXPATH)libmlx.a
MLXFMK		:= -framework OpenGL -framework AppKit

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
	@if [ $(1) -eq $(TOTAL_FILES) ]; then echo "$(RED_BOLD)\t\t\tcub3d ready!\n"; fi
	@printf "$(SET_CURSOR)$(WHITE)"
endef

TOTAL_FILES_B 	:= $(words $(SRCS_BONUS))
CURRENT_FILE_B 	:= $(shell find ./srcs_bonus/ -name "*.o" -newer $(MAKEFILE_LIST) | wc -l)
PROG_BAR_INIT_B	:= 0

LINE_B_1		:=	"                    hhhhhhh               iiii  lllllll                  "
LINE_B_2		:=	"                    h:::::h              i::::i l:::::l                  "
LINE_B_3		:=	"                    h:::::h               iiii  l:::::l                  "
LINE_B_4		:=	"                    h:::::h                     l:::::l                  "
LINE_B_5		:=	"ppppp   ppppppppp    h::::h hhhhh       iiiiiii  l::::l    ooooooooooo   "
LINE_B_6		:=	"p::::ppp:::::::::p   h::::hh:::::hhh    i:::::i  l::::l  oo:::::::::::oo "
LINE_B_7		:=	"p:::::::::::::::::p  h::::::::::::::hh   i::::i  l::::l o:::::::::::::::o"
LINE_B_8		:=	"pp::::::ppppp::::::p h:::::::hhh::::::h  i::::i  l::::l o:::::ooooo:::::o"
LINE_B_9		:=	" p:::::p     p:::::p h::::::h   h::::::h i::::i  l::::l o::::o     o::::o"
LINE_B_10		:=	" p:::::p     p:::::p h:::::h     h:::::h i::::i  l::::l o::::o     o::::o"
LINE_B_11		:=	" p:::::p     p:::::p h:::::h     h:::::h i::::i  l::::l o::::o     o::::o"
LINE_B_12		:=	" p:::::p    p::::::p h:::::h     h:::::h i::::i  l::::l o::::o     o::::o"
LINE_B_13		:=	" p:::::ppppp:::::::p h:::::h     h:::::hi::::::il::::::lo:::::ooooo:::::o"
LINE_B_14		:=	" p::::::::::::::::p  h:::::h     h:::::hi::::::il::::::lo:::::::::::::::o"
LINE_B_15		:=	" p::::::::::::::pp   h:::::h     h:::::hi::::::il::::::l oo:::::::::::oo "
LINE_B_16		:=	" p::::::pppppppp     hhhhhhh     hhhhhhhiiiiiiiillllllll   ooooooooooo   "
LINE_B_17		:=	" p:::::p                                                                 "
LINE_B_18		:=	" p:::::p                                                                 "
LINE_B_19		:=	"p:::::::p                                                                "
LINE_B_20		:=	"p:::::::p                                                                "
LINE_B_21		:=	"p:::::::p                                                                "
LINE_B_22		:=	"ppppppppp                                                                "

LINE_COUNT_B	:= 22

LINES_B			:= $(foreach elem,$(shell for i in {1..$(LINE_COUNT_B)}; do printf "LINE_B_%d " $$i; done),$($(elem)))
LINE_SIZES_B	:= $(foreach elem,$(shell for i in {1..$(LINE_COUNT_B)}; do printf "LINE_B_%d " $$i; done),$(shell wc -c <<< $($(elem)) | tr -d ' '))

define progress_bar_b
	@$(eval CURRENT_FILE_B := $(shell echo $$(($(CURRENT_FILE_B) + 1))))
	@$(call progress_bar_b_2, $(CURRENT_FILE_B))
    @$(eval PROG_BAR_INIT_B := 1)
endef

define progress_bar_b_2
	@printf "$(UNSET_CURSOR)"
	@if [ $(PROG_BAR_INIT_B) -eq 0 ]; then printf "\n$(RED)$(shell for i in {1..$(LINE_COUNT_B)}; do printf '%%s\\n'; done)\n\n" $(LINES_B); fi
	@printf "\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\r";
	@printf "$(GREEN)$(shell for i in $(LINE_SIZES_B); do printf '%%.%ds\\n' $$(($$i*$(1)/$(TOTAL_FILES_B))); done) \n%d/%d\n" $(LINES_B) $(1) $(TOTAL_FILES_B)
	@if [ $(1) -eq $(TOTAL_FILES_B) ]; then echo "$(RED_BOLD)\t\t\tcub3d_bonus ready!\n"; fi
	@printf "$(SET_CURSOR)$(WHITE)"
endef

########################################################################################
#-------------------------------------MAKEFILE_RULE------------------------------------#
########################################################################################

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(LIBNAME) $(MLXNAME) $(OBJ)
	@$(COMP) $(CFLAGS) $(OBJ) -o $@ -L $(LIBPATH) -L $(MLXPATH) -lft -lmlx $(MLXFMK) -lm

$(NAME_BONUS): $(LIBNAME) $(MLXNAME) $(OBJ_BONUS)
	@$(COMP) $(CFLAGS) $(OBJ_BONUS) -o $@ -L $(LIBPATH) -L $(MLXPATH) -lft -lmlx $(MLXFMK) -lm

$(LIBNAME):
	@make -C $(LIBPATH) all

$(MLXNAME):
	@make -C $(MLXPATH) all

$(OBJ): %.o: %.c $(INCS)
	@$(COMP) $(CFLAGS) -c $< -o $@
	@$(call progress_bar)

$(OBJ_BONUS): %.o: %.c $(INCS_BONUS)
	@$(COMP) $(CFLAGS) -c $< -o $@
	@$(call progress_bar_b)

clean:
	@make -C $(LIBPATH) clean
	@rm -f $(OBJ)
	@echo "$(RED_BOLD)$(NAME) clean: $(GREEN)OK$(WHITE)"
	@$(eval CURRENT_FILE := 0)

bonus_clean:
	@make -C $(LIBPATH) clean
	@rm -f $(OBJ_BONUS)
	@echo "$(RED_BOLD)$(NAME_BONUS) clean: $(GREEN)OK$(WHITE)"
	@$(eval CURRENT_FILE_B := 0)

fclean:
	@make -C $(LIBPATH) fclean
	@make -C $(MLXPATH) clean
	@rm -f $(OBJ) $(NAME)
	@echo "$(RED_BOLD)$(NAME) fclean: $(GREEN)OK$(WHITE)"
	@$(eval CURRENT_FILE := 0)

bonus_fclean:
	@make -C $(LIBPATH) fclean
	@make -C $(MLXPATH) clean
	@rm -f $(OBJ_BONUS) $(NAME_BONUS)
	@echo "$(RED_BOLD)$(NAME_BONUS) fclean: $(GREEN)OK$(WHITE)"
	@$(eval CURRENT_FILE_B := 0)

re: fclean all

bonus_re: bonus_fclean bonus

.PHONY: all clean fclean re bonus bonus_clean bonus_fclean bonus_re
