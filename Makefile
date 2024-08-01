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
				fill_with_texture.c event_hook_routine.c vector_utils.c \
				init_data.c init_colors.c init_map.c init_map_utils.c

SRCS		:= $(addprefix ./srcs/, $(SRC))
OBJ 		:= $(SRCS:.c=.o)

SRC_BONUS	:=	main_bonus.c draw_floor_ceiling_bonus.c draw_on_screen_bonus.c \
				draw_wall_bonus.c draw_weapon_bonus.c event_hook_routine_bonus.c \
				exit_bonus.c fill_wall_col_with_texture_bonus.c get_time_bonus.c \
				get_wall_distance_bonus.c set_sprite_bonus.c update_player_data_bonus.c \
				update_spritesheet_index_bonus.c vec_operation_bonus.c \
				init_data_bonus.c init_colors_bonus.c init_map_bonus.c init_map_utils_bonus.c

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

LINE_1			:=  "                                                                        "
LINE_2			:=	"      ...                               ..                      ..      "
LINE_3			:=	"   xH88\"\`~ .x8X                   . uW8\"        .x~~\"*Weu.    dF        "
LINE_4			:=	" :8888   .f\"8888Hf    x.    .     \`t888        d8Nu.  9888c  '88bu.     "
LINE_5			:=	":8888>  X8L  ^\"\"\`   .@88k  z88u    8888   .    88888  98888  '*88888bu  "
LINE_6			:=	"X8888  X888h       ~\"8888 ^8888    9888.z88N   \"***\"  9888%    ^\"*8888N "
LINE_7			:=	"88888  !88888.       8888  888R    9888  888E       ..@8*\"    beWE \"888L"
LINE_8			:=	"88888   %88888       8888  888R    9888  888E    \`\`\`\`\"8Weu    888E  888E"
LINE_9			:=	"88888 '> \`8888>      8888  888R    9888  888E   ..    ?8888L  888E  888E"
LINE_10			:=	"\`8888L %  ?888   !   8888 ,888B .  9888  888E :@88N   '8888N  888E  888F"
LINE_11			:=	" \`8888  \`-*\"\"   /   \"8888Y 8888\"  .8888  888\" *8888~  '8888F .888N..888 "
LINE_12			:=	"   \"888.      :\"     \`Y\"   'YP     \`%888*%\"   '*8\"\`   9888%   \`\"888*\"\"  "
LINE_13			:=	"     \`\"\"***~\"\`                        \"\`        \`~===*%\"\`        \"\"     "
LINE_14			:=  "                                                                        "

LINE_COUNT		:= 14

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

LINE_B_1			:=  "                                                                        "
LINE_B_2			:=	"      ...                               ..                      ..      "
LINE_B_3			:=	"   xH88\"\`~ .x8X                   . uW8\"        .x~~\"*Weu.    dF        "
LINE_B_4			:=	" :8888   .f\"8888Hf    x.    .     \`t888        d8Nu.  9888c  '88bu.     "
LINE_B_5			:=	":8888>  X8L  ^\"\"\`   .@88k  z88u    8888   .    88888  98888  '*88888bu  "
LINE_B_6			:=	"X8888  X888h       ~\"8888 ^8888    9888.z88N   \"***\"  9888%    ^\"*8888N "
LINE_B_7			:=	"88888  !88888.       8888  888R    9888  888E       ..@8*\"    beWE \"888L"
LINE_B_8			:=	"88888   %88888       8888  888R    9888  888E    \`\`\`\`\"8Weu    888E  888E"
LINE_B_9			:=	"88888 '> \`8888>      8888  888R    9888  888E   ..    ?8888L  888E  888E"
LINE_B_10			:=	"\`8888L %  ?888   !   8888 ,888B .  9888  888E :@88N   '8888N  888E  888F"
LINE_B_11			:=	" \`8888  \`-*\"\"   /   \"8888Y 8888\"  .8888  888\" *8888~  '8888F .888N..888 "
LINE_B_12			:=	"   \"888.      :\"     \`Y\"   'YP     \`%888*%\"   '*8\"\`   9888%   \`\"888*\"\"  "
LINE_B_13			:=	"     \`\"\"***~\"\`                        \"\`        \`~===*%\"\`        \"\"     "
LINE_B_14			:=  "                                                                        "

LINE_COUNT_B	:= 14

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

$(NAME_BONUS): $(LIBNAME) $(OBJ_BONUS)
	@$(COMP) $(CFLAGS) $(OBJ_BONUS) -o $@ -L $(LIBPATH) -lft -lmlx -framework OpenGL -framework AppKit -lm

$(NAME): $(LIBNAME) $(OBJ)
	@$(COMP) $(CFLAGS) $(OBJ) -o $@ -L $(LIBPATH) -lft -lmlx -framework OpenGL -framework AppKit -lm

$(LIBNAME):
	@make -C $(LIBPATH) all

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
	@rm -f $(OBJ) $(NAME)
	@echo "$(RED_BOLD)$(NAME) fclean: $(GREEN)OK$(WHITE)"
	@$(eval CURRENT_FILE := 0)

bonus_fclean:
	@make -C $(LIBPATH) fclean
	@rm -f $(OBJ_BONUS) $(NAME_BONUS)
	@echo "$(RED_BOLD)$(NAME_BONUS) fclean: $(GREEN)OK$(WHITE)"
	@$(eval CURRENT_FILE_B := 0)

bonus_re: bonus_fclean bonus


re: fclean all

.PHONY: all clean fclean re bonus bonus_clean bonus_fclean bonus_re
