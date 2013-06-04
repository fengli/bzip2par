INST_DIR = ../../open-stream/gcc/install_omp

INSTALL_DIR = ${INST_DIR}
LIB_DIR = ${INSTALL_DIR}/lib64
BIN_DIR = ${INSTALL_DIR}/bin
GCC = ${BIN_DIR}/gcc
LIBWSTREAM_DF_DIR = $(LIB_DIR)

###########################################################################
TEST= bzip2 pbzip2
CFLAGS =  -Wall -std=c99  -ffast-math -Wl,-rpath,$(INST_DIR)/lib64 -g  -DTIMING_OUTPUT#-fdump-tree-all #-Werror
LDFLAGS = -L${LIB_DIR} -lm -lc -rdynamic -Wl,-rpath,$(LIB_DIR)

WSTREAM_LIB=/home/li/tstar/open-stream/libworkstream_df/
CFLAGS_WSTREAM = -Wall -g -std=c99 -O0 -ffast-math #-D_DEBUG
LDFLAGS_WSTREAM = -L$(WSTREAM_LIB) -lm -lc -rdynamic -Wl,-rpath,$(WSTREAM_LIB) -lwstream_df

CFLAGS_DEBUG = -Wall -g

all: $(TEST)

bzip2: compress.c spec.min.c common.h
	gcc $(CFLAGS_DEBUG) -o $@ $^

pbzip2: parallel_compress.c spec.min.c common.h
	gcc $(CFLAGS_DEBUG) -fopenmp -o $@ $^

run: bzip2 pbzip2
	./run.sh
clean:
	rm -f out.*
	rm -f $(TEST)
