
$(info CROSS_COMPILE=${CROSS_COMPILE})

ifneq (${CROSS_COMPILE},)
CC=${CROSS_COMPILE}gcc
else
CC=gcc
endif

APP_NAME=rrecv
CFLAGS=-I. -lpthread -lrt

OBJ = rrecv.o 

all: $(APP_NAME)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(APP_NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


clean:
	@rm -f *.o
	@rm -f $(APP_NAME)
