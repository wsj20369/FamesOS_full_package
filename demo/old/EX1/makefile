APP_OBJ     = Appmain+Apptask+Timer+c:\lib\c\c0l.obj
APP_LST     = Appmain.obj Apptask.obj FamesOS.obj Task.Obj Event.Obj Timer.obj
STD_LIB     = c:\lib\c\cxc.lib
COMPILER    = tcc -c -1 -B -S -ml -w -Ic:\tc\include
LINKER      = tlink /x
HEADFILE    = Apptask.h All.h Datatype.h Event.h FamesOS.h Includes.h Task.h Version.h Misc.h error.h timer.h

FAMESOSLIB  = FamesOS.LIB
FAMESOSLIST = FamesOS.obj Task.Obj Event.Obj
FAMESOSFILE = +FamesOS.obj +Task.Obj +Event.Obj

EXE_FILE    = appmain.exe
	
Appmain.obj: Appmain.c $(HEADFILE)
	$(COMPILER) Appmain.c

Apptask.obj: Apptask.c $(HEADFILE)
	$(COMPILER) Apptask.c

Timer.obj: Timer.c $(HEADFILE)
	$(COMPILER) Timer.c

FamesOS.obj: FamesOS.c $(HEADFILE)
	$(COMPILER) FamesOS.c

Task.obj: Task.c $(HEADFILE)
	$(COMPILER) Task.c

Event.obj: Event.c $(HEADFILE)
	$(COMPILER) Event.c

$(FAMESOSLIB):  $(FAMESOSLIST)
	del  $(FAMESOSLIB)
	tlib $(FAMESOSLIB) $(FAMESOSFILE)

$(EXE_FILE): $(APP_LST) $(FAMESOSLIB)
	$(LINKER) $(APP_OBJ),,,$(STD_LIB)+$(FAMESOSLIB);

