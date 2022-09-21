@echo off

set code=1 2 add
set r=(3,0)
call :test

set code=3 4 add 5 add
set r=(12,0)
call :test

set code=6 7 add
set r=(13,0)
call :test

echo This test is supposed to fail.
set code=1 1 add
set r=(3,0)
call :test

set code=-2 -1 add
set r=(-3,0)
call :test

set code=-4 -3 add
set r=(-7,0)
call :test

set code=-6 -5 add
set r=(-11,0)
call :test

set code=-8 -7 add
set r=(-15,0)
call :test

set code=i con
set r=(0,-1)
call :test

set code=2 cis arg
set r=(2,0)
call :test

set code=4 3 i mul add abs
set r=(5,0)
call :test

set code=4 3 sub -1 sub
set r=(2,0)
call :test

set code=5 2 div
set r=(2.5,0)
call :test

set code=2 3 pow
set r=(8,0)
call :test

set code=3 2 pow
set r=(9,0)
call :test

set code=2 7 add sqrt
set r=(3,0)
call :test

set code=16
set r=(0,0)
call :test

del test.asm test.bin test.out

exit /B

:test
echo %code% > test.asm
e8asm test.asm test.bin
e8core test.bin 1>test.out
find "%r%" test.out > nul && ( echo Passed "%code%" returned "%r%". ) || (
echo FAILED! "%code%". Expected "%r%" but got
type test.out
echo .
)
exit /B
