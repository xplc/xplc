# Microsoft Developer Studio Project File - Name="xplc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=xplc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "xplc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "xplc.mak" CFG="xplc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xplc - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "xplc - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "xplc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0xc0c /d "NDEBUG"
# ADD RSC /l 0xc0c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "xplc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0xc0c /d "_DEBUG"
# ADD RSC /l 0xc0c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "xplc - Win32 Release"
# Name "xplc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\xplc\factory.cpp
# End Source File
# Begin Source File

SOURCE=.\xplc\servmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\xplc\simpledl.cpp
# End Source File
# Begin Source File

SOURCE=.\xplc\statichandler.cpp
# End Source File
# Begin Source File

SOURCE=.\xplc\xplc.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\xplc\factory.h
# End Source File
# Begin Source File

SOURCE=.\xplc\handlernode.h
# End Source File
# Begin Source File

SOURCE=.\include\xplc\IFactory.h
# End Source File
# Begin Source File

SOURCE=.\include\xplc\IGenericFactory.h
# End Source File
# Begin Source File

SOURCE=.\include\xplc\IObject.h
# End Source File
# Begin Source File

SOURCE=.\include\xplc\IServiceHandler.h
# End Source File
# Begin Source File

SOURCE=.\include\xplc\IServiceManager.h
# End Source File
# Begin Source File

SOURCE=.\include\xplc\ISimpleDynamicLoader.h
# End Source File
# Begin Source File

SOURCE=.\include\xplc\IStaticServiceHandler.h
# End Source File
# Begin Source File

SOURCE=.\xplc\objectnode.h
# End Source File
# Begin Source File

SOURCE=.\xplc\servmgr.h
# End Source File
# Begin Source File

SOURCE=.\xplc\simpledl.h
# End Source File
# Begin Source File

SOURCE=.\xplc\statichandler.h
# End Source File
# Begin Source File

SOURCE=.\include\xplc\utils.h
# End Source File
# Begin Source File

SOURCE=.\include\xplc\uuid.h
# End Source File
# Begin Source File

SOURCE=.\include\xplc\xplc.h
# End Source File
# End Group
# End Target
# End Project
