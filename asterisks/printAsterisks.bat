@echo off

setlocal EnableDelayedExpansion

set /a n=%1
set "str="
echo n: %n%
for /l %%i in (1,1,%n%) do (
	set "str="
	for /l %%j in (1,1,%%i) do (
		set "str=!str!*"
	)
	echo !str!
)
echo.

for /l %%i in (%n%,-1,1) do (
	set "str="
	for /l %%j in (1,1,%%i) do (
		set "str=!str!*"
	)
	echo !str!
)
echo.

for /l %%i in (1,1,%n%) do (
	set "str="
	set /a step = %n%-%%i
	for /l %%j in (!step!,-1,1) do (
		set "str=!str! "
	)
	for /l %%j in (1,1,%%i) do (
		set "str=!str!*"
	)
	echo !str!
)
echo.

::(2n - 1 rows): n + (n - 1)
for /l %%i in (1,1,!n!) do (
    set /a step=!n!-%%i
    set "str1="
    for /l %%j in (1,1,!step!) do (
        set "str1=!str1! "
    )
    set /a step=2*%%i-1
    set "str2="
    for /l %%k in (1,1,!step!) do (
        set "str2=!str2!*"
    )
    echo !str1!!str2!
)
set /a upper=!n!-1
for /l %%i in (1,1,!upper!) do (
    set "str1="
    for /l %%j in (1,1,%%i) do (
        set "str1=!str1! "
    )
    set /a step=2*!upper!-2*%%i+1
    set "str2="
    for /l %%k in (1,1,!step!) do (
        set "str2=!str2!*"
    )
    echo !str1!!str2!
)

