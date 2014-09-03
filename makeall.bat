@echo off

CD SRC
CALL MAKEALL
CD ..

COPY demo.exe DEBUG
COPY demo.exe SLC\slc.exe


ECHO ALL OK. 
