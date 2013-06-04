INST_DIR = ../../open-stream/gcc/install_omp

INSTALL_DIR = ${INST_DIR}
LIB_DIR = ${INSTALL_DIR}/lib64
BIN_DIR = ${INSTALL_DIR}/bin
GCC = ${BIN_DIR}/gcc
LIBWSTREAM_DF_DIR = $(LIB_DIR)
ICC=/opt/intel/bin/icc

###########################################################################
TEST= icc_bzip2 icc_pbzip2
CFLAGS =  -Wall -std=c99  -ffast-math -Wl,-rpath,$(INST_DIR)/lib64 -g  -DTIMING_OUTPUT#-fdump-tree-all #-Werror
LDFLAGS = -L${LIB_DIR} -lm -lc -rdynamic -Wl,-rpath,$(LIB_DIR)

WSTREAM_LIB=/home/li/tstar/open-stream/libworkstream_df/
CFLAGS_WSTREAM = -Wall -g -std=c99 -O0 -ffast-math #-D_DEBUG
LDFLAGS_WSTREAM = -L$(WSTREAM_LIB) -lm -lc -rdynamic -Wl,-rpath,$(WSTREAM_LIB) -lwstream_df

CFLAGS_DEBUG = -Wall -g -O3
ICC_FLAGS = -O3 
all: $(TEST)

stream_bzip2: stream_spec.c stream_bzip2.c common.h
	$(GCC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -fopenmp -Wl,-rpath,$(LIBWSTREAM_DF_DIR) -L${LIBWSTREAM_DF_DIR} -lwstream_df

icc_bzip2: compress.c spec.min.c common.h
	$(ICC) $(ICC_CFLAGS) -o $@ $^

icc_pbzip2: parallel_compress.c spec.min.c common.h
	$(ICC) $(ICC_CFLAGS) -openmp -o $@ $^

run: icc_bzip2 icc_pbzip2
	./run.sh

clean:
	rm -f out.*
	rm -f $(TEST)