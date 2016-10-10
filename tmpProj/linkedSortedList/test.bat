set PROGRAM="%~1"

rem проверяем запуск без параметров
%PROGRAM% > %TEMP%\no_parameters.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\parameters_count_error.txt %TEMP%\no_parameters.txt
if ERRORLEVEL 1 goto err

rem проверка запуска с несуществующим файлом в качестве параметра
%PROGRAM% not_existing_file.txt > %TEMP%\no_file.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\no_file.txt %TEMP%\no_file.txt
if ERRORLEVEL 1 goto err

rem проверка запуска с пустым файлом в качестве параметра
%PROGRAM% empty_file.txt > %TEMP%\empty_file_out.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\empty_file_out.txt %TEMP%\empty_file_out.txt
if ERRORLEVEL 1 goto err

rem проверяем запуск со строкой в listSize
%PROGRAM% str_in_listSize.txt > %TEMP%\str_in_listSize_out.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\str_in_listSize_out.txt %TEMP%\str_in_listSize_out.txt
if ERRORLEVEL 1 goto err


echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1