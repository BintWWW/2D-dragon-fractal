CLIBS= 		-lm -lglut -lGL -lGLU -lX11 -lGLEW # 2016
CPATHS=		-I/usr/include -L/usr/lib # 2016
CFLAGS=		$(CPATHS)$(CLIBS)


second:		second.cpp
		g++ second.cpp -o second $(CFLAGS)



clean:
		rm *.o
