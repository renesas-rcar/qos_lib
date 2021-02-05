OBJGROUP=qos_tp.o
TARGET_NAME=qos_tp
QOS_MODULE =

all: $(TARGET_NAME)
LIBS = -lrt -L$(LIBSHARED) -lqos
$(TARGET_NAME): qos_tp.c
	$(CC) -o $@ $< $(LIBS) -I$(INCSHARED)/$(QOS_MODULE) -O2

clean:
	rm -f *.o
	rm -f $(TARGET_NAME)
