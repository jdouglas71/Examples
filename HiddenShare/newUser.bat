REM ***************************************
REM  Point to the FusionAEData location
REM  Ideally, this would be replaced with a common dialog to browse to the location instead of typing it.

set /p FusionAEDataParent=Enter the absolute location where 'Fusion AE Data' folder will be created:

REM ***************************************


REM ***************************************
REM  Create FusionAEData share directory

set FusionAEData=%FusionAEDataParent%\Fusion AE Data

REM ***************************************


REM ***************************************
REM *** TEST *** TEST *** TEST *** TEST ***
REM CLEANUP LAST TEST

cacls "%FusionAEData%" /T  /E /G %USERNAME%:F
net share FusionAEData$ /DELETE
net user FusionAE /DELETE

REM TEST READY
REM *** TEST *** TEST *** TEST *** TEST ***
REM ***************************************


REM ***************************************
REM ***************************************
REM ***************************************
REM To successfully execute this batch file the current user must have administrator privileges
REM	to create a new user
REM	to create a new subdirectory
REM	to share the new subdirectory
REM ***************************************


REM ***************************************
REM Create the FusionAE user
REM net user FusionAE smatrix /DOMAIN /add would create the user on the domain vs. the local machine
REM I prefer the local machine because it is more restrictive and allows multiple installations of the product

net user FusionAE smatrix /add

REM ***************************************


REM ***************************************
REM  Create FusionAEData share directory

md "%FusionAEData%"

REM ***************************************


REM ***************************************
REM  Set Permissions to FusionAE user only with full control

cacls "%FusionAEData%" /T  /E /R Everyone
cacls "%FusionAEData%" /T  /E /G FusionAE:F

REM ***************************************


REM ***************************************
REM  Share the FusionAEData as FusionAEData$

net share FusionAEData$="%FusionAEData%" /users:100 /REMARK:"Fusion AE Data Storage"

REM ***************************************


REM ***************************************
REM  Remove current user so only SYSTEM and FusionAE have direct access

cacls "%FusionAEData%" /T  /E /R %USERNAME%

REM ***************************************


REM ***************************************
REM *** TEST *** TEST *** TEST *** TEST ***
REM  Map the drive to prove that we succeeded

REM net use X: \\%COMPUTERNAME%\FusionAEData$ smatrix /USER:%COMPUTERNAME%\FusionAE
REM echo success is great! > X:\succeeded.txt

REM *** TEST *** TEST *** TEST *** TEST ***
REM ***************************************


REM ***************************************
REM ***************************************
REM ***************************************



REM ----------------------------------------------------------------------------------
REM	I would like the share to be only visible to FusionAE user
REM	This example allows anyone to map to the share but then they don't have any permissions to use it.
REM	I am still looking for a way to assign permissions to the share (vs. the share directory)
REM ----------------------------------------------------------------------------------

echo 'FUSION_AE_DATA_SHARE_MACHNE=%COMPUTERNAME%', the COMPUTERNAME environment variable is what needs to be stored in the Fusion Administrator database file.

echo It will be used by Fusion AE to map the share:
echo
echo NET USE X  