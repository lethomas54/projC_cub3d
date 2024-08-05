########################################################################################
#----------------------------------EXEC_NAME-------------------------------------------#
########################################################################################

NAME		:=	cub3d
NAME_BONUS	:=	cub3d_bonus

########################################################################################
#-------------------------------COMPILER_OPTION----------------------------------------#
########################################################################################

COMP		:=	cc
CFLAGS		:=	-Wall -Wextra -Werror

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
				get_wall_distance_bonus.c set_sprite_bonus.c \
				update_player_data_bonus.c update_spritesheet_index_bonus.c \
				vec_operation_bonus.c init_data_bonus.c init_colors_bonus.c \
				init_map_bonus.c init_map_utils_bonus.c init_map_playable_bonus.c

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

GREEN		:=	\033[0;32m
RED 		:=	\033[0;31m
RED_BOLD 	:=	\033[1;31m
BLUE_BOLD	:=	\033[1;34m
WHITE 		:=	\033[0;0m

########################################################################################
#-------------------------------------MAKEFILE_RULE------------------------------------#
########################################################################################

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(LIBNAME) $(OBJ)
	@$(COMP) $(CFLAGS) $(OBJ) -o $@ -L $(LIBPATH) -lft -lmlx -lm -framework OpenGL -framework AppKit
	@echo "$(BLUE_BOLD)$(NAME) compilation: $(GREEN)OK$(WHITE)"

$(NAME_BONUS): $(LIBNAME) $(OBJ_BONUS)
	@$(COMP) $(CFLAGS) $(OBJ_BONUS) -o $@ -L $(LIBPATH) -lft -lmlx -lm -framework OpenGL -framework AppKit
	@echo "$(BLUE_BOLD)$(NAME_BONUS) compilation: $(GREEN)OK$(WHITE)"

$(LIBNAME):
	@make -C $(LIBPATH) all

$(OBJ): %.o: %.c $(INCS)
	@$(COMP) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS): %.o: %.c $(INCS_BONUS)
	@$(COMP) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBPATH) clean
	@rm -f $(OBJ)
	@echo "$(RED_BOLD)$(NAME) clean: $(GREEN)OK$(WHITE)"

bonus_clean:
	@make -C $(LIBPATH) clean
	@rm -f $(OBJ_BONUS)
	@echo "$(RED_BOLD)$(NAME_BONUS) clean: $(GREEN)OK$(WHITE)"

fclean:
	@make -C $(LIBPATH) fclean
	@rm -f $(OBJ) $(NAME)
	@echo "$(RED_BOLD)$(NAME) fclean: $(GREEN)OK$(WHITE)"

bonus_fclean:
	@make -C $(LIBPATH) fclean
	@rm -f $(OBJ_BONUS) $(NAME_BONUS)
	@echo "$(RED_BOLD)$(NAME_BONUS) fclean: $(GREEN)OK$(WHITE)"

bonus_re: bonus_fclean bonus


re: fclean all

.PHONY: all clean fclean re bonus bonus_clean bonus_fclean bonus_re
