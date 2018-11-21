@echo off

rem ##########################################################################
rem Please consult the README file to learn more about this example federate #
rem ##########################################################################

rem ################################
rem # check command line arguments #
rem ################################
:checkargs
if "%1" == "" goto usage

rem ###################
rem # Set up RTI_HOME #
rem ###################
:rtihome
::修改为本地portico安装目录
set RTI_HOME=F:\Program Files\portico-2016.05.28 

::修改为联邦代码目录
cd F:\myCode\HLA_graduation_design\hla13           
echo RTI_HOME environment variable is set to %RTI_HOME%
goto run

:run
if "%1" == "clean" goto clean
if "%1" == "compile" goto compile
if "%1" == "execute" goto execute

rem ############################################
rem ### (target) clean #########################
rem ############################################
:clean
echo Deleting example federate executable and left over logs
del *.obj
del main.exe
rd /S /Q logs
goto finish

############################################
### (target) compile #######################
############################################
:compile
echo Compiling example federate
cl /I"F:\Program Files\portico-2016.05.28\include\hla13" /DRTI_USES_STD_FSTREAM /EHsc main.cpp ExampleCPPFederate.cpp ExampleFedAmb.cpp "F:\Program Files\portico-2016.05.28\lib\vc10\libRTI-NG.lib" "F:\Program Files\portico-2016.05.28\lib\vc10\libFedTime.lib"
goto finish

############################################
### (target) execute #######################
############################################
:execute
SHIFT
set PATH=F:\Program Files\portico-2016.05.28\jre\bin\client;F:\Program Files\portico-2016.05.28\bin\vc10;%PATH%
main %1 %2 %3 %4 %5 %6 %7 %8 %9
goto finish


:usage
echo usage: win32-vc10.bat [compile] [clean] [execute [federate-name]]

:finish
