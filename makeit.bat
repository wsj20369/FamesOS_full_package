@echo off

CD SRC
CALL MAKEALL > ..\t.txt
CD ..

ECHO COPYing

COPY demo.exe DEBUG


ECHO ALL OK. 

notepad t.txt