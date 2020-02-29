@echo off
setlocal
cd /d %1
for /f "delims=" %%a in ('dir /s /b en2.asm') do F:\masm32\bin\ml /Bl F:\masm32\bin\link16.exe "%%a"
endlocal 