VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CTCLogIn"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Event LogOnStatus(ByVal LoggedOn As Boolean)

Private Const ERROR_NONE = 0
Private Const ERROR_SUCCESS = 0&

Private Const EnvironVariableSeparator As String = ";"
Private Const PERegistryPath As String = "SOFTWARE\Perkin Elmer"

Private Declare Function GetEnvironmentVariable Lib "kernel32" Alias "GetEnvironmentVariableA" (ByVal lpName As String, ByVal lpBuffer As String, ByVal nSize As Long) As Long
Private Declare Function SetEnvironmentVariable Lib "kernel32" Alias "SetEnvironmentVariableA" (ByVal lpName As String, ByVal lpValue As String) As Long

Private Declare Sub TcAccessInit Lib "TcAccess.dll" Alias "VbTcAccessInit" ()

'If you are not logged onto Turbochrom, you have only read access to files.
'If there is an interactive Turbochrom application running on the workstation
'where your program is running, you are logged on. Determine that there is a
'logon of this type.
Private Declare Function TcLoggedOn Lib "TcAccess.dll" _
    Alias "VbTcAccessLoggedOn" () As Integer

'Authenticate the user using logon name and password.
Private Declare Function TcLogon Lib "TcAccess.dll" _
    Alias "VbTcAccessLogon" (ByVal UserName As String, _
                             ByVal Password As String) As Integer

Private WithEvents mclsRegistry As CRegistry
Attribute mclsRegistry.VB_VarHelpID = -1
Private WithEvents mfrmLogin As frmLogin
Attribute mfrmLogin.VB_VarHelpID = -1
Private mstrTCDataPath As String
Private mstrTCVersion As String

Friend Property Get TCDataPath() As String
  TCDataPath = mstrTCDataPath
End Property

Friend Property Get TCVersion() As String
  TCVersion = mstrTCVersion
End Property

Private Sub Class_Initialize()
  Dim lngResult As Long
  Dim strValue As String
  
  Dim strTotalChromPath As String
  Dim strTotalChromName As String
  
  Set mclsRegistry = New CRegistry
  Set mfrmLogin = New frmLogin
  
  ' Get the place of TotalChrom.
  lngResult = GetTCPath(strTotalChromName, strTotalChromPath)
  
  ' Set the variable table.
  lngResult = FixEnvironmentVariableTable(strTotalChromPath)
  
  ' Initialize the TCAccess DLL.
  lngResult = TCInit
  
  mfrmLogin.FormTitle = strTotalChromName & "  LogIn"
End Sub

Private Sub Class_Terminate()
  Set mfrmLogin = Nothing
  Set mclsRegistry = Nothing
End Sub

Public Property Get LoggedOn() As Boolean
  Dim booLoggedOn As Boolean
  Dim lngResult As Long
  
  On Error GoTo ErrorHandler
  
  lngResult = TcLoggedOn ' ->0=not logged on, 1=logged on
  
  If lngResult = 0 Then
    booLoggedOn = False
  Else
    booLoggedOn = True
  End If
  
  LoggedOn = booLoggedOn
  
ExitHere:
  Exit Property

ErrorHandler:
  booLoggedOn = False
  Resume ExitHere
End Property

Private Function GetTCPath(ByRef strProductName As String, _
                           ByRef strProductPath As String) As Long
'//////////////////////////////////////////////////////////////////////////////
' GetTCPath
'
'
'
' In:         .
'
' Out:        {GetTCPath}. ReturnValue from function
'
' Events:     .
'
' Functions:  .
'
' Uses:       .
'
' Notes:      .
'
' Programmer: Geert Jansen
' Date:       August 13 2001
' CopyRight:  (c) 2000 ControlChrom
'
' Reference:  .
'//////////////////////////////////////////////////////////////////////////////
  Dim lngResult As Long
  Dim lngReturn As Long
  
  Dim strProduct As String
  Dim strVersion As String
  Dim strPath As String
  Dim varRegistryValue As Variant
      '
  lngReturn = 0
  
  ' 1) Find KEY = TotalChrom Product in HKEY_LOCAL_MACHINE\SoftWare\Perkin Elmer
  varRegistryValue = mclsRegistry.QueryValue(regHKEY_LOCAL_MACHINE, PERegistryPath, "TotalChrom Product", regREG_SZ)
  If IsEmpty(varRegistryValue) = False Then
    strProduct = CStr(varRegistryValue)
  End If
  
  If Len(strProduct) = 0 Then ' -> see if there is a turbochrom entry.
    ' 1a) Find KEY = Turbochrom Product in HKEY_LOCAL_MACHINE\SoftWare\Perkin Elmer
    varRegistryValue = mclsRegistry.QueryValue(regHKEY_LOCAL_MACHINE, PERegistryPath, "Turbochrom Product", regREG_SZ)
    If IsEmpty(varRegistryValue) = False Then
      strProduct = CStr(varRegistryValue)
    End If
  End If
  
  ' 2) Find KEY = Current Version in HKEY_LOCAL_MACHINE\Software\Perkin Elmer\[TotalChrom Product]
  varRegistryValue = mclsRegistry.QueryValue(regHKEY_LOCAL_MACHINE, PERegistryPath & "\" & strProduct, "Current Version", regREG_SZ)
  If IsEmpty(varRegistryValue) = False Then
    strVersion = CStr(varRegistryValue)
  End If
  
  ' 3) Find KEY = Root Path in HKEY_LOCAL_MACHINE\Software\Perkin Elmer\[TotalChrom Product]\[Current Version]
  varRegistryValue = mclsRegistry.QueryValue(regHKEY_LOCAL_MACHINE, PERegistryPath & "\" & strProduct & "\" & strVersion, "Root Path", regREG_SZ)
  If IsEmpty(varRegistryValue) = False Then
    strPath = CStr(varRegistryValue)
  End If
  
  ' 4) Path = [Root Path] & "\" [TotalChrom Product] & "\" & [Current Version] & "\" & "Bin"
  strPath = strPath & "\" & strProduct & "\" & strVersion & "\Bin"
  
  mstrTCDataPath = strPath
  mstrTCVersion = strVersion
      '
ExitHere:
      '
  strProductName = strProduct
  strProductPath = strPath
      '
  GetTCPath = lngReturn
  Exit Function
End Function

Private Function FixEnvironmentVariableTable(ByRef strPath As String) As Long
'//////////////////////////////////////////////////////////////////////////////
' FixEnvironmentVariableTable
'
'
'
' In:         .
'
' Out:        {FixEnvironmentVariableTable}. ReturnValue from function
'
' Events:     .
'
' Functions:  .
'
' Uses:       .
'
' Notes:      .
'
' Programmer: Geert Jansen
' Date:       August 13 2001
' CopyRight:  (c) 2000 ControlChrom
'
' Reference:  .
'//////////////////////////////////////////////////////////////////////////////
  Dim lngResult As Long
  Dim lngReturn As Long
  
  Dim strBuffer As String
      '
  lngReturn = 0
  
  ' Get the Environment Path.
  strBuffer = Space$(32767)
  lngResult = GetEnvironmentVariable("PATH", strBuffer, Len(strBuffer))
  ' Remove all the spaces left overs.
  strBuffer = Left$(strBuffer, lngResult)
  
  ' Check (and add) the given path in the Envirnment Path
  If InStr(1, UCase$(strBuffer), UCase$(strPath)) = 0 Then
  ' Path is not present. Insert path at start and put back in environment variable.
    strBuffer = strPath & EnvironVariableSeparator & strBuffer
    lngResult = SetEnvironmentVariable("PATH", strBuffer)
  End If
      '
ExitHere:
      '
  FixEnvironmentVariableTable = lngReturn
End Function

Private Function TCInit() As Long
'//////////////////////////////////////////////////////////////////////////////
' TCInit
'
'
'
' In:         .
'
' Out:        {TCInit}. ReturnValue from function
'
' Events:     .
'
' Functions:  .
'
' Uses:       .
'
' Notes:      .
'
' Programmer: Geert Jansen
' Date:       August 13 2001
' CopyRight:  (c) 2000 ControlChrom
'
' Reference:  .
'//////////////////////////////////////////////////////////////////////////////
  Dim lngResult As Long
  Dim lngReturn As Long
      '
  TcAccessInit
  
  TCInit = lngReturn
      '
End Function

Friend Function LogOn(Optional ByVal UserName As String = "", _
                 Optional ByVal Password As String = "", _
                 Optional ByVal SilenLogon As Boolean = False) As Long
'//////////////////////////////////////////////////////////////////////////////
' LogOn
'
'
'
' In:         .
'
'
' Events:     .
'
' Functions:  .
'
' Uses:       .
'
' Notes:      .
'
' Programmer: Geert Jansenr
' Date:       August 13 2001
' CopyRight:  (c) 2000 ControlChrom
'
' Reference:  .
'//////////////////////////////////////////////////////////////////////////////
  Dim lngResult As Long
  Dim lngReturn As Long
  Dim booLoggedOn As Boolean
      '
  ' Check for username which is optional
  If Len(UserName) > 0 Then
    lngResult = TcLogon(UserName, Password) ' -1 = NOT logged on, 0 = logged on.
  End If
  
  booLoggedOn = LoggedOn
   
  Select Case booLoggedOn
    Case False  ' NOT LOGGED ON
      ' SilentLogon is a flag that tells if the code should show a
      ' LogIn form when not logged on.
      If SilenLogon = False Then
        mfrmLogin.Show vbModeless
      Else
        RaiseEvent LogOnStatus(booLoggedOn)
      End If
    Case True ' LOGGED ON
      RaiseEvent LogOnStatus(booLoggedOn)
  End Select
End Function

Private Sub mfrmLogin_LogInCancel()
  Dim booLoggedOn As Boolean
      '
  On Error Resume Next
      '
  Unload mfrmLogin
  booLoggedOn = LoggedOn
  RaiseEvent LogOnStatus(booLoggedOn)
End Sub

Private Sub mfrmLogin_LogIn(ByVal UserName As String, ByVal Password As String)
  Dim lngResult As Long
      '
  On Error Resume Next
      '
  Unload mfrmLogin
  
  LogOn UserName, Password, False
  
End Sub
