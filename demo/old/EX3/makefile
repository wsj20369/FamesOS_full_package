APP_OBJ     = Appmain+Apptask+Timer+Mutex+Rs232+Tool+Pci+Nic+c:\lib\c\c0l.obj
APP_LST     = Appmain.obj Apptask.obj FamesOS.obj Task.Obj Event.Obj Timer.obj Mutex.obj Rs232.obj Tool.obj Pci.obj Nic.obj
STD_LIB     = c:\lib\c\cxc.lib
COMPILER    = tcc -c -1 -B -S -ml -w -Ic:\tc\include
LINKER      = tlink /x
HEADFILE    = Apptask.h All.h Datatype.h Event.h FamesOS.h Includes.h Task.h Version.h timer.h mutex.h rs232.h tool.h pci.h nic.h

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

Mutex.obj: Mutex.c $(HEADFILE)
	$(COMPILER) Mutex.c

Rs232.obj: Rs232.c $(HEADFILE)
	$(COMPILER) Rs232.c

Tool.obj: Tool.c $(HEADFILE)
	$(COMPILER) Tool.c

Pci.obj: Pci.c $(HEADFILE)
	$(COMPILER) Pci.c

Nic.obj: Nic.c $(HEADFILE)
	$(COMPILER) Nic.c


$(FAMESOSLIB):  $(FAMESOSLIST)
	del  $(FAMESOSLIB)
	tlib $(FAMESOSLIB) $(FAMESOSFILE)

$(EXE_FILE): $(APP_LST) $(FAMESOSLIB)
	$(LINKER) $(APP_OBJ),,,$(STD_LIB)+$(FAMESOSLIB);

