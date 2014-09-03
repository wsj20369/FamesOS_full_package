COMPILER    = tcc -c -1 -B -S -ml -w -Ic:\tc\include -I.\..\os\include
HEADFILE    = ..\os\include\checkinc common.h

dstfile     = demo.lib

Lib         = $(dstfile)
LibList     =  start.obj  plc.obj  gui.obj  net.obj  xms.obj  font.obj
LibFile     = +start.obj +plc.obj +gui.obj +net.obj +xms.obj +font.obj

start.obj: start.c $(HEADFILE)
	$(COMPILER) start.c

plc.obj: plc.c $(HEADFILE)
	$(COMPILER) plc.c

gui.obj: gui.c $(HEADFILE)
	$(COMPILER) gui.c

net.obj: net.c $(HEADFILE)
	$(COMPILER) net.c

xms.obj: xms.c $(HEADFILE)
	$(COMPILER) xms.c

font.obj: font.c $(HEADFILE)
	$(COMPILER) font.c

$(Lib):  $(LibList)
	del  $(Lib)
	tlib $(Lib) $(LibFile)
	copy $(Lib) ..



