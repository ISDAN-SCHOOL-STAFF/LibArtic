SRC_DIRS := src
INC_DIRS := include
HPPS := $(shell find $(INC_DIRS) -type f -name '*.hpp')
SRCS := $(shell find $(SRC_DIRS) -name '*.c' -or -name '*.cpp')
OBJS := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))

CFLAGS := -O0 -g -g3 -ggdb -W -Wall -fPIC -std=c++11 -Wno-write-strings -Wno-unused-result -Wno-format-security -Wno-frame-address -Wno-narrowing -Wno-cast-function-type
CPPFLAGS := $(foreach dir,$(dir $(HPPS)),-I$(dir))

all: check-errors libartic.a
libartic.a: $(OBJS)
	@ar rcs $@ $^
	@echo -e "\033[36mArtic is now ready to be installed !\033[0m"

%.o: %.c
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@ && echo -e "\033[34m[OK] $<\033[0m" || echo -e "\033[34m[KO] $<\033[0m"

%.o: %.cpp
	@$(CXX) -c $(CFLAGS) $(CPPFLAGS) $< -o $@ && echo -e "\033[34m[OK] $<\033[0m" || echo -e "\033[34m[KO] $<\033[0m"

.PHONY: clean
clean:
	@rm -f $(OBJS) libartic.a

.PHONY: check-syntax
check-syntax:
	@$(CC) $(CFLAGS) $(CPPFLAGS) -fsyntax-only $(SRCS)
	@$(CXX) $(CFLAGS) $(CPPFLAGS) -fsyntax-only $(SRCS)

.PHONY: check-errors
check-errors:
	@mkdir -p errors
	@touch errors/errors.log
	@make check-syntax 2> errors/errors.log
	@if [ -s errors/errors.log ]; then echo -e "\033[31mErrors found, check errors/errors.log for details\033[0m"; else echo -e "\033[32mNo errors found\033[0m"; fi
