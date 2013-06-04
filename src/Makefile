INST_DIR = ../../open-stream/install

INSTALL_DIR = ${INST_DIR}
LIB_DIR = ${INSTALL_DIR}/lib64
BIN_DIR = ${INSTALL_DIR}/bin
GCC = ${BIN_DIR}/gcc
LIBWSTREAM_DF_DIR = $(LIB_DIR)

OPENSTREAM_GCC = /home/li/tstar/open-stream/install/bin/gcc
###########################################################################
TEST= openbzip2 bzip2 
CFLAGS =  -Wall -std=c99  -ffast-math -Wl,-rpath,$(INST_DIR)/lib64 -g  -DTIMING_OUTPUT#-fdump-tree-all #-Werror
LDFLAGS = -L${LIB_DIR} -lm -lc -rdynamic -Wl,-rpath,$(LIB_DIR)

WSTREAM_LIB=/home/li/tstar/open-stream/libworkstream_df/
CFLAGS_WSTREAM = -Wall -g -std=c99 -O0 -ffast-math #-D_DEBUG
LDFLAGS_WSTREAM = -L$(LIB_DIR) -lm -lc -rdynamic -Wl, -rpath, $(LIB_DIR) -Wl,-rpath,$(LIBWSTREAM_DF_DIR) -L$(LIBWSTREAM_DF_DIR) -lwstream_df

CFLAGS_DEBUG = -Wall -g -O0

all: $(TEST)

stream_bzip2: stream_spec.c stream_bzip2.c common.h
	$(GCC) $(CFLAGS) $(LDFLAGS_WSTREAM) $^ -o $@ -fopenmp -Wl,-rpath,$(LIBWSTREAM_DF_DIR) -L${LIBWSTREAM_DF_DIR} -lwstream_df

bzip2: compress.c spec.min.c common.h
	gcc $(CFLAGS_DEBUG) -o $@ $^

openbzip2: parallel_compress.c spec.min.c common.h
	$(OPENSTREAM_GCC) $(CFLAGS_DEBUG) $(LDFLAGS) -fopenmp -o $@ $^  -Wl,-rpath,$(LIBWSTREAM_DF_DIR) -L${LIBWSTREAM_DF_DIR} -lwstream_df

run: 
	./run.sh
clean:
	rm -f out.*
	rm -f $(TEST)