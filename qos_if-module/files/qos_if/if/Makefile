QOS_MODULE =

all:
	${CC} -fPIC -c qos_lib.c -I$(INCSHARED)/$(QOS_MODULE) -Wall
	${CC} -shared -Wl,-soname=libqos.so.1 -o libqos.so.1.0.0 qos_lib.o
	ln -s ./libqos.so.1.0.0 libqos.so.1
	ln -s ./libqos.so.1 libqos.so

clean:
	rm -f qos_lib.o libqos.so libqos.so.1 libqos.so.1.0.0

install:
	$(CP) ../include/qos_public.h $(INCSHARED)/$(QOS_MODULE)
