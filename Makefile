
sharedrstack:stackarrary.c
	gcc -o $@ $^

.PHONY:clean
	clean:
		rm -f stackarrary
