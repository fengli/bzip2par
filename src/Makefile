INST_DIR = ../../../gcc/install_omp

INSTALL_DIR = ${INST_DIR}
LIB_DIR = ${INSTALL_DIR}/lib64
BIN_DIR = ${INSTALL_DIR}/bin
GCC = ${BIN_DIR}/gcc
LIBWSTREAM_DF_DIR = $(LIB_DIR)

###########################################################################

CFLAGS =  -Wall -std=c99 -O2  -ffast-math -Wl,-rpath,$(INST_DIR)/lib64 -g  #-fdump-tree-all #-Werror
LDFLAGS = -L${LIB_DIR} -lm -lc -rdynamic -Wl,-rpath,$(LIB_DIR)

all:bzip2 bzip2.orig df_bzip2
bzip2.orig:bzip2.orig.c spec.c
	gcc bzip2.orig.c spec.c -g -o bzip2.orig
bzip2:bzip2.c spec.c
	gcc bzip2.c spec.c -g -o bzip2
df_bzip2: df_bzip2.c
	$(GCC) $(CFLAGS) $(LDFLAGS) df_bzip2.c -o df_bzip2 -fopenmp -Wl,-rpath,$(LIBWSTREAM_DF_DIR) -L${LIBWSTREAM_DF_DIR} -lwstream_df
run: df_bzip2 bzip2
	./bzip2 test.txt
	./df_bzip2 test.txt
