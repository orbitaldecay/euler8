!include LogicLib.nsh
!include WinCore.nsh
!include Integration.nsh

Outfile "Euler8_0.01_setup_x86-64.exe"
InstallDir $PROGRAMFILES64\Euler8
ShowInstDetails show

Section
  SetOutPath $INSTDIR
  File "e8asm.exe"
  File "euler8.exe"
  File "SDL2.dll"
  File "..\docs\readme.html"
  WriteUninstaller $INSTDIR\Uninstall.exe
SectionEnd

Section "Uninstall"
  Delete $INSTDIR\e8asm.exe
  Delete $INSTDIR\euler8.exe
  Delete $INSTDIR\SDL2.dll
  Delete $INSTDIR\readme.html
  RMDir $INSTDIR
SectionEnd

!define ASSOC_EXT ".e8"
!define ASSOC_PROGID "Euler8.Catridge"
!define ASSOC_VERB "Execute Euler8 Cartridge"
!define ASSOC_APPEXE "euler8.exe"
Section -ShellAssoc
  # Register file type
  WriteRegStr ShCtx "Software\Classes\${ASSOC_PROGID}\DefaultIcon" "" "$InstDir\${ASSOC_APPEXE},0"
  WriteRegStr ShCtx "Software\Classes\${ASSOC_PROGID}\shell\${ASSOC_VERB}\command" "" '"$InstDir\${ASSOC_APPEXE}" "%1"'
  WriteRegStr ShCtx "Software\Classes\${ASSOC_EXT}" "" "${ASSOC_PROGID}"
  ${NotifyShell_AssocChanged}
SectionEnd
