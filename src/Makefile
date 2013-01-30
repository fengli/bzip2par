INST_DIR = ../../open-stream/gcc/install_omp

INSTALL_DIR = ${INST_DIR}
LIB_DIR = ${INSTALL_DIR}/lib64
BIN_DIR = ${INSTALL_DIR}/bin
GCC = ${BIN_DIR}/gcc
LIBWSTREAM_DF_DIR = $(LIB_DIR)

###########################################################################
TEST= bzip2o bzip2k bzip2
CFLAGS =  -Wall -std=c99  -ffast-math -Wl,-rpath,$(INST_DIR)/lib64 -g  -DTIMING_OUTPUT#-fdump-tree-all #-Werror
LDFLAGS = -L${LIB_DIR} -lm -lc -rdynamic -Wl,-rpath,$(LIB_DIR)

CFLAGS_DEBUG = -Wall -g

all: $(TEST)

bzip2:bzip2.c spec.c common.h
	gcc $(CFLAGS_DEBUG) -o $@ $^

bzip2o:bzip2.o.c spec.c common.h
	gcc $(CFLAGS_DEBUG) -o $@ $^

stream_bzip2: stream_spec.c stream_bzip2.c common.h
	$(GCC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -fopenmp -Wl,-rpath,$(LIBWSTREAM_DF_DIR) -L${LIBWSTREAM_DF_DIR} -lwstream_df

bzip2k: compress.c spec.min.c common.h
	gcc $(CFLAGS_DEBUG) -o $@ $^

run: bzip2k bzip2
	./run.sh
clean:
	rm out.*
	rm $(TEST)