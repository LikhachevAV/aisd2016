set PROGRAM="%~1"
rem ��������� ������ ��� ����������
%PROGRAM% > %TEMP%\no_parameters.txt
if NOT ERRORLEVEL 1 goto err
fc.exe parameters_count_error.txt %TEMP%\no_parameters.txt
if ERRORLEVEL 1 goto err

rem �������� ������� � �������������� ������ � �������� ���������
%PROGRAM% not_existing_file.txt > %TEMP%\no_file.txt
if NOT ERRORLEVEL 1 goto err
fc.exe no_file.txt %TEMP%\no_file.txt
if ERRORLEVEL 1 goto err

rem �������� ������� � ������ ������ � �������� ���������
%PROGRAM% empty_file.txt > %TEMP%\empty_file_out.txt
if NOT ERRORLEVEL 1 goto err
fc.exe empty_file_out.txt %TEMP%\empty_file_out.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1