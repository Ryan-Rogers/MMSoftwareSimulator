all: program

%: %.c
	gcc $< -o $@

