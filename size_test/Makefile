COLL_FILES := \
    ../src/collection.c \
    ../src/utils/coll_utils.c \
    ../utest/mock/coll_port_fs_mock.c \
    ../utest/mock/coll_port_linked_list_mock.c \
    ../utest/mock/coll_port_mem_mock.c \
    ../utest/mock/coll_port_serializer_mock.c \
    ../utest/mock/serializer/serializer_pet_decode.c \
    ../utest/mock/serializer/serializer_pet_encode.c \
    ../ext/zcbor/zcbor/src/zcbor_common.c \
    ../ext/zcbor/zcbor/src/zcbor_decode.c \
    ../ext/zcbor/zcbor/src/zcbor_encode.c


COLL_INC_PATHS := \
	-I ../src \
	-I ../src/utils \
	-I ../src/port \
	-I ../utest/mock \
	-I ../utest/mock/serializer \
	-I ../utest/mock/slist \
	-I ../ext/zcbor/zcbor/include

COLL_OBJECTS  := $(COLL_FILES:.c=.o)
COLL_DEPS     := $(COLL_FILES:.c=.d)
COLL_SU       := $(COLL_FILES:.c=.su)

%.o: %.c
	@$(CC) $(INC_PATHS) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(COLL_OBJECTS)
	@rm -f $(COLL_SU)
	@rm -f *.a

coll: INC_PATHS := $(COLL_INC_PATHS)
coll: $(COLL_OBJECTS)
	@$(AR) rcs libcoll.a $(COLL_OBJECTS)
	@$(SIZE) -t libcoll.a

coll_su:
	@echo $(COLL_SU)
