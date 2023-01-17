SRC_DIRS := src private
INC_DIRS := include

SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c*))
OBJS := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))

CFLAGS := -O0 -g -g3 -ggdb -W -Wall -fPIC -std=c++99 -Wno-write-strings -Wno-unused-result -Wno-format-security -Wno-frame-address -Wno-narrowing -Wno-cast-function-type
CPPFLAGS := $(foreach dir,$(INC_DIRS),-I$(dir))

libartic.a: $(OBJS)
	@ar rcs $@ $^
	@echo -e "\033[36mArtic is now ready to be installed !\033[0m"

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	@rm -f $(OBJS) libartic.a

.PHONY: check-syntax
check-syntax:
	$(CC) $(CFLAGS) $(CPPFLAGS) -fsyntax-only $(CHK_SOURCES)
	$(CXX) $(CFLAGS) $(CPPFLAGS) -fsyntax-only $(CHK_SOURCES)

.PHONY: check-errors
check-errors:
	make check-syntax 2> errors/errors.log
	if [ -s errors/errors.log ]; then echo -e "\033[31mErrors found, check errors/errors.log for details\033[0m"; else echo -e "\033[32mNo errors found\033[0m"; fi
