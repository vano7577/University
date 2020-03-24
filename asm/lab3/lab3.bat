echo on
cd c:\masm32
set /P var=""
dir /s /b %var% > name.tmp
set /p mydir="" < name.tmp
cd c:\masm32\labs
ml /c /coff /Fl "%mydir%"
link /subsystem:console "3-03-IP84-Golubov.obj"