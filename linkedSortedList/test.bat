set PROGRAM="%~1"

rem проверка левой крайней границы (с числом 0 в качестве параметра)
echo run program without arguments:
%PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\parameters_count_error.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверяем запуск c 1м параметром
echo run program with just one parameter:
%PROGRAM% empty_file.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\parameters_count_error.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверяем запуск с несуществующим файлом для чтения в качестве параметра
echo run program with no file for reading as parameter:
%PROGRAM% no_file.txt empty_file.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\parameters_count_error.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

goto success


:success
echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1