INST_DIR = ../../../gcc/install_omp

INSTALL_DIR = ${INST_DIR}
LIB_DIR = ${INSTALL_DIR}/lib64
BIN_DIR = ${INSTALL_DIR}/bin
GCC = ${BIN_DIR}/gcc
LIBWSTREAM_DF_DIR = $(LIB_DIR)

###########################################################################
TEST=df_compress #compress bzip2
CFLAGS =  -Wall -std=c99 -O2  -ffast-math -Wl,-rpath,$(INST_DIR)/lib64 -g  #-fdump-tree-all #-Werror
LDFLAGS = -L${LIB_DIR} -lm -lc -rdynamic -Wl,-rpath,$(LIB_DIR)

CFLAGS_DEBUG = -Wall -g

all: $(TEST)
bzip2:bzip2.c spec.c
	gcc $(CFLAGS_DEBUG) -o $@ $^
compress:compress.c spec.min.c
	gcc $(CFLAGS_DEBUG) -o $@ $^
df_compress: df_spec.min.c #df_compress.c
	$(GCC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -fopenmp -Wl,-rpath,$(LIBWSTREAM_DF_DIR) -L${LIBWSTREAM_DF_DIR} -lwstream_df
run: bzip2 compress
	./run.sh
clean:
	rm out.*
	rm $(TEST)