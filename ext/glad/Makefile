# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 13:24:31 by lcottet          #+#    #+#              #
#    Updated: 2026/02/10 17:30:07 by lcottet          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

C = cc

CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3

SRCS_DIR = src

SRCS =	glad.c

OUTDIR = obj

OBJ = $(SRCS:%.c=$(OUTDIR)/%.o)

DEP = $(OBJ:%.o=%.d)

INCLUDE = include

NAME = glad.a

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	$(AR) rcs $(NAME) $(OBJ)

$(OUTDIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(C) $(CFLAGS) $(INCLUDE:%=-I %) -o $@ -c $<

.PHONY: clean
clean:
	rm -rf $(OUTDIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean $(NAME)

-include $(DEP)