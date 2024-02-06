chcp 65001
echo off
cls

echo --строка параметров: %*
echo --параметр 1: %1
echo --параметр 2: %2
echo --параметр 3: %3
set /A first = %1
set /A second = %2
set /A thrid = %3
set /A sum = first + second
set /A composition = first * second
set /A del = thrid / second
set /A min = second - thrid
set /A mn1 = second - thrid
set /A mn2 = first - second
set /A composition2 = mn1 * mn2
echo %first% + %second% = %sum%
echo %first% * %second% = %composition%
echo %thrid% / %second% = %del%
echo %second% - %first% = %min%
echo (%second% - %first%) * (%first% - %second%) = %composition2%
pause