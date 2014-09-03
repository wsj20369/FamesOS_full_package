COMPILER    = tcc -c -1 -B -S -ml -w -Ic:\tc\include -I.\..\include
HEADFILE    = ..\include\checkinc App.h AppVer.h 

dstfile     = App.lib

Lib         = $(dstfile)
LibList     = App.obj
LibFile     = +App.obj



App.obj: App.c $(HEADFILE)
	$(COMPILER) App.c



$(Lib):  $(LibList)
	del  $(Lib)
	tlib $(Lib) $(LibFile)
	copy $(Lib) ..



