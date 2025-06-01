# Makefile for building a C++ project with CMake
# THIS IS REQUIRED BY THE SUBJECT
# and way of building a cmake project is dumb
# but I want to use cmake for this project

NAME := scop

ifeq ($(OS),Windows_NT)
	BUILD_DIR := build_windows
	NAME := scop.exe
else ifeq ($(shell uname),Darwin)
	BUILD_DIR := build_macos
else ifeq ($(shell uname),Linux)
	BUILD_DIR := build_linux
else
	$(error Unsupported OS)
endif


.PHONY: all
all: $(NAME)

$(NAME): ${BUILD_DIR}/$(NAME)
	cp ${BUILD_DIR}/$(NAME) .

.PHONY: ${BUILD_DIR}/$(NAME)
${BUILD_DIR}/$(NAME): ${BUILD_DIR}/Makefile
	cd ${BUILD_DIR} && cmake --build .

${BUILD_DIR}/Makefile: CMakeLists.txt
	mkdir -p ${BUILD_DIR}
	cd ${BUILD_DIR} && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..

.PHONY: clean
clean:
	rm -rf ${BUILD_DIR}