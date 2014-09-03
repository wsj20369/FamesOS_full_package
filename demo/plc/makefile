COMPILER    = tcc -c -1 -B -S -ml -w -Ic:\tc\include -I.\..\os\include
HEADFILE    = ..\os\include\checkinc common.h

dstfile     = demo.lib

Lib         = $(dstfile)
LibList     =  start.obj  plc.obj
LibFile     = +start.obj +plc.obj

start.obj: start.c $(HEADFILE)
	$(COMPILER) start.c

plc.obj: plc.c $(HEADFILE)
	$(COMPILER) plc.c

$(Lib):  $(LibList)
	del  $(Lib)
	tlib $(Lib) $(LibFile)
	copy $(Lib) ..



