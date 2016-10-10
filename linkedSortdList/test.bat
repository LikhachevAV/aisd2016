set PROGRAM="%~1"

rem проверяем запуск без параметров
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

rem проверка запуска с числом, длиной 33 в качестве параметра
echo run program with argument length owerflow:
%PROGRAM% 111111111111111111111111111111111 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\number_length_owerflow.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверка запуска не с двоичным числом в качестве параметра
echo run program with string as argument:
%PROGRAM% 11a > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\argument_type_error %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверка запуска не с двоичным числом в качестве параметра
echo run program with decimal number as argument:
%PROGRAM% 211 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\argument_type_error %TEMP%\output.txt
if ERRORLEVEL 1 goto err


rem проверка запуска с числом 110010000(b) = 400(dec) в качестве параметра
echo run program with binary number 110010000 as argument:
%PROGRAM% 110010000 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe out_files\400.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверка левой крайней границы (с числом 0 в качестве параметра)
echo run program with "0" as argument:
%PROGRAM% 0 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe out_files\0.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверка правой крайней границы (с числом 11111111111111111111111111111111 в качестве параметра)
echo run program with "MAX_UNSIGNED_LONG" as argument:
%PROGRAM% 11111111111111111111111111111111 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe out_files\ULONG_MAX.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

:success
echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1