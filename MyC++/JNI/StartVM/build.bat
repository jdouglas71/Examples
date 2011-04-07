bcc32 LaunchService.cpp FUtils.cpp jvm_borland.lib

@rem sc delete FusionLaunchService
@rem 
@rem set INCLUDE=c:\program files\Microsoft Visual Studio\VC98\Include;d:\jdk1.6.0_02\include;d:\jdk1.6.0_02\include\win32;  
@rem set LIB=c:\program files\Microsoft Visual Studio\VC98\Lib;d:\jdk1.6.0_02\lib;  
@rem cl LaunchService.cpp FUtils.cpp jvm.lib advapi32.lib
@rem 
@rem copy launchservice.exe e:\launchservice.exe
@rem copy launchservice.exe e:\S-Matrix Project Life Cycle\development\binaries\S-matrix\FusionChrom Administrator
@rem 
@rem 
@rem sc create FusionLaunchService binpath= e:\launchservice.exe

