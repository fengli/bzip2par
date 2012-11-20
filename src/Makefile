all:bzip2 bzip2.orig
run:    bzip2
	./bzip2 test.txt
bzip2.orig:bzip2.orig.c spec.c
	gcc bzip2.orig.c spec.c -g -o bzip2.orig
bzip2:bzip2.c spec.c
	gcc bzip2.c spec.c -g -o bzip2
