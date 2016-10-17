set PROGRAM="%~1"

rem проверка запуска без параметров
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

rem проверяем запуск с несуществующим файлом для чтения в качестве параметра 1
echo run program with no file for reading as parameter 1:
%PROGRAM% no_file.txt empty_file.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\no_file_out.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверяем запуск с выводом количества элементов в массиве'
echo run program with number of array elements = 34':
%PROGRAM% 34.txt empty_file.txt > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe out_files\34_out.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1