##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

RED	:=	\033[0;31m
GREEN	:=	\033[0;32m
YELLOW	:=	\033[1;33m
NC	:=	\033[0m

all: zappy_server zappy_gui zappy_ai

zappy_ai:
	@echo -e "$(GREEN)Building AI...$(NC)"
	cd ai && cp ai.py zappy_ai && chmod +x zappy_ai && mv zappy_ai .. && cd ..

zappy_server:
	@echo -e "$(GREEN)Building server...$(NC)"
	@cd server && mkdir -p ./build/
	@cd server/build && cmake --log-level=ERROR ..
	@cd server/build && make --silent && chmod +x zappy_server
	@cd ../..
	@mv server/build/zappy_server server/../zappy_server

zappy_gui:
	@echo -e "$(GREEN)Building GUI...$(NC)"
	@cd gui && mkdir -p ./build/
	@cd gui/build && cmake --log-level=ERROR ..
	@cd gui/build && make --silent && chmod +x zappy_gui
	@cd ../..
	@mv gui/build/zappy_gui gui/../zappy_gui

.PHONY: all clean zappy_gui zappy_server zappy_ai re

clean:
	@rm -rf server/build gui/build zappy_server zappy_gui zappy_ai

re:	clean all
