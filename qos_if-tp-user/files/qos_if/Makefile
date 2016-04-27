OBJGROUP=qos_tp.o
TARGET_NAME=qos_tp

all: $(TARGET_NAME)
LIBS = -lrt -L$(LIBSHARED) -lqos
$(TARGET_NAME): qos_tp.c
	$(CC) -o $@ $< $(LIBS) -I$(BUILDDIR)/include

clean:
	rm -f *.o
	rm -f $(TARGET_NAME)
