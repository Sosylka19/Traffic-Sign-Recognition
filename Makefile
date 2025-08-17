
DOCKER_COMPOSE_FILE=docker-compose.yml
QT_PROJECT_DIR=qt/sign-detection
BUILD_DIR=$(QT_PROJECT_DIR)/build
CMAKE_BUILD_TYPE=Release

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CLIENT_EXEC=$(BUILD_DIR)/sign-detection
endif
ifeq ($(UNAME_S),Darwin)
    CLIENT_EXEC=$(BUILD_DIR)/sign-detection.app/Contents/MacOS/sign-detection
endif
ifeq ($(OS),Windows_NT)
    CLIENT_EXEC=$(BUILD_DIR)/sign-detection.exe
endif

.PHONY: all up down client clean run

all: up client

up:
	docker-compose -f $(DOCKER_COMPOSE_FILE) up -d

down:
	docker-compose -f $(DOCKER_COMPOSE_FILE) down

client:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) ../
	cd $(BUILD_DIR) && $(MAKE) -j$(shell nproc)
	$(CLIENT_EXEC)

clean:
	rm -rf $(BUILD_DIR)
