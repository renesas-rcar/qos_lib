all:
	$(CP) ../include/qos_public.h $(BUILDDIR)/include/
	${CC} -fPIC -c qos_lib.c -I$(BUILDDIR)/include -Wall
	${CC} -shared -Wl,-soname=libqos.so.1 -o libqos.so.1.0.0 qos_lib.o
	ln -s ./libqos.so.1.0.0 libqos.so.1
	ln -s ./libqos.so.1 libqos.so

clean:
	rm -f qos_lib.o libqos.so libqos.so.1 libqos.so.1.0.0

