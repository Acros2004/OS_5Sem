::(echo off)не показываем пути
::(cls)чистим консоль

chcp 65001
echo off
cls

echo --текущий пользователь: %username%
echo --текущие дата и время: %date% %time%
echo --имя компьютера: %computername%
pause


