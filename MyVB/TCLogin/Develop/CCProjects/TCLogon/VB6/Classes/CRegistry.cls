VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CRegistry"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

'//////////////////////////////////////////////////////////////////////////////
' CRegistry
'
' Class acts as a SHELL for the Registry API, opening and closing Keys
' automaticly, ErrorHandling, Removing NULL Characters, etc.
'
'//////////////////////////////////////////////////////////////////////////////

Public Event Error(ByVal Number As Long, _
                   ByVal Description As String, _
                   ByVal Source As String, _
                   ByVal HelpFile As String, _
                   ByVal HelpContext As Long, _
                   ByVal Parameters As Variant)
'
' Parameters are the params given to the function.
' the Variant contains an array with dimensions 0..n-1, 0..2. The
' second dimension contains for each parameter the name, type and value.

' CEnums only has to be referenced. No instance is needed,
' because the class does not contain code.
Private clsEnums As CEnum

'------------------------------------------------------------------------------
' >>> Constants, Types and Declarations for the Registry API Calls          <<<
'------------------------------------------------------------------------------
Private Const ERROR_SUCCESS = 0&

Private Const HKEY_CLASSES_ROOT = &H80000000
Private Const HKEY_CURRENT_CONFIG = &H80000005
Private Const HKEY_CURRENT_USER = &H80000001
Private Const HKEY_DYN_DATA = &H80000006
Private Const HKEY_LOCAL_MACHINE = &H80000002
Private Const HKEY_PERFORMANCE_DATA = &H80000004
Private Const HKEY_USERS = &H80000003

Private Const REG_BINARY = 3                     ' Free form binary
Private Const REG_DWORD = 4                      ' 32-bit number
Private Const REG_DWORD_BIG_ENDIAN = 5           ' 32-bit number Big Endian = High Byte Left (lower address)
Private Const REG_DWORD_LITTLE_ENDIAN = 4        ' 32-bit number (same as REG_DWORD) Little Endian = Low Byte on Low Address
Private Const REG_EXPAND_SZ = 2                  ' Unicode nul terminated string
Private Const REG_LINK = 6                       ' Symbolic Link (unicode)
Private Const REG_MULTI_SZ = 7                   ' Multiple Unicode strings
Private Const REG_NONE = 0                       ' No value type
Private Const REG_RESOURCE_LIST = 8              ' Resource list in the resource map
Private Const REG_SZ = 1                         ' Unicode nul terminated string

Private Const REG_CREATED_NEW_KEY = &H1          ' New Registry Key created
Private Const REG_FULL_RESOURCE_DESCRIPTOR = 9   ' Resource list in the hardware description

Private Const REG_OPTION_BACKUP_RESTORE = 4     ' open for backup or restore
Private Const REG_OPTION_CREATE_LINK = 2        ' Created key is a symbolic link
Private Const REG_OPTION_NON_VOLATILE = 0       ' Key is preserved when system is rebooted
Private Const REG_OPTION_RESERVED = 0           ' Parameter is reserved
Private Const REG_OPTION_VOLATILE = 1           ' Key is not preserved when system is rebooted

Private Const REG_NOTIFY_CHANGE_ATTRIBUTES = &H2
Private Const REG_NOTIFY_CHANGE_LAST_SET = &H4                      ' Time stamp
Private Const REG_NOTIFY_CHANGE_NAME = &H1                      ' Create or delete (child)
Private Const REG_NOTIFY_CHANGE_SECURITY = &H8
Private Const REG_LEGAL_CHANGE_FILTER = (REG_NOTIFY_CHANGE_NAME Or REG_NOTIFY_CHANGE_ATTRIBUTES Or REG_NOTIFY_CHANGE_LAST_SET Or REG_NOTIFY_CHANGE_SECURITY)
Private Const REG_LEGAL_OPTION = (REG_OPTION_RESERVED Or REG_OPTION_NON_VOLATILE Or REG_OPTION_VOLATILE Or REG_OPTION_CREATE_LINK Or REG_OPTION_BACKUP_RESTORE)

Private Const REG_OPENED_EXISTING_KEY = &H2                      ' Existing Key opened

Private Const REG_REFRESH_HIVE = &H2                      ' Unwind changes to last flush
Private Const REG_RESOURCE_REQUIREMENTS_LIST = 10
Private Const REG_WHOLE_HIVE_VOLATILE = &H1                      ' Restore whole hive volatile

Private Const READ_CONTROL = &H20000
Private Const STANDARD_RIGHTS_READ = (READ_CONTROL)
Private Const STANDARD_RIGHTS_WRITE = (READ_CONTROL)
Private Const STANDARD_RIGHTS_ALL = &H1F0000
Private Const SYNCHRONIZE = &H100000

Private Const KEY_CREATE_LINK = &H20
Private Const KEY_CREATE_SUB_KEY = &H4
Private Const KEY_ENUMERATE_SUB_KEYS = &H8
Private Const KEY_EVENT = &H1     '  Event contains key event record
Private Const KEY_NOTIFY = &H10
Private Const KEY_QUERY_VALUE = &H1
Private Const KEY_SET_VALUE = &H2
Private Const KEY_ALL_ACCESS = ((STANDARD_RIGHTS_ALL Or KEY_QUERY_VALUE Or KEY_SET_VALUE Or KEY_CREATE_SUB_KEY Or KEY_ENUMERATE_SUB_KEYS Or KEY_NOTIFY Or KEY_CREATE_LINK) And (Not SYNCHRONIZE))
Private Const KEY_READ = ((STANDARD_RIGHTS_READ Or KEY_QUERY_VALUE Or KEY_ENUMERATE_SUB_KEYS Or KEY_NOTIFY) And (Not SYNCHRONIZE))

Private Const KEY_EXECUTE = ((KEY_READ) And (Not SYNCHRONIZE))
Private Const KEY_WRITE = ((STANDARD_RIGHTS_WRITE Or KEY_SET_VALUE Or KEY_CREATE_SUB_KEY) And (Not SYNCHRONIZE))


Private Type SECURITY_ATTRIBUTES
  nLength As Long
  lpSecurityDescriptor As Long
  bInheritHandle As Long
End Type

Private Type FILETIME
  dwLowDateTime As Long
  dwHighDateTime As Long
End Type

Private Type ACL
  AclRevision As Byte
  Sbz1 As Byte
  AclSize As Integer
  AceCount As Integer
  Sbz2 As Integer
End Type

Private Type SECURITY_DESCRIPTOR
  Revision As Byte
  Sbz1 As Byte
  Control As Long
  Owner As Long
  Group As Long
  Sacl As ACL
  Dacl As ACL
End Type

Private Declare Function RegCloseKey _
                Lib "advapi32.dll" (ByVal hKey As Long) As Long
                
Private Declare Function RegConnectRegistry _
                Lib "advapi32.dll" Alias "RegConnectRegistryA" _
                (ByVal lpMachineName As String, _
                 ByVal hKey As Long, _
                 phkResult As Long) As Long
                 
Private Declare Function RegCreateKey _
                Lib "advapi32.dll" Alias "RegCreateKeyA" _
                (ByVal hKey As Long, _
                 ByVal lpSubKey As String, _
                 phkResult As Long) As Long
                
Private Declare Function RegCreateKeyEx _
                Lib "advapi32.dll" Alias "RegCreateKeyExA" _
                (ByVal hKey As Long, _
                 ByVal lpSubKey As String, _
                 ByVal Reserved As Long, _
                 ByVal lpClass As String, _
                 ByVal dwOptions As Long, _
                 ByVal samDesired As Long, _
                 lpSecurityAttributes As SECURITY_ATTRIBUTES, _
                 phkResult As Long, _
                 lpdwDisposition As Long) As Long

Private Declare Function RegDeleteKey _
                Lib "advapi32.dll" Alias "RegDeleteKeyA" _
                (ByVal hKey As Long, _
                 ByVal lpSubKey As String) As Long

Private Declare Function RegDeleteValue _
                Lib "advapi32.dll" Alias "RegDeleteValueA" _
                (ByVal hKey As Long, _
                 ByVal lpValueName As String) As Long

Private Declare Function RegEnumKey _
                Lib "advapi32.dll" Alias "RegEnumKeyA" _
                (ByVal hKey As Long, _
                 ByVal dwIndex As Long, _
                 ByVal lpName As String, _
                 ByVal cbName As Long) As Long

Private Declare Function RegEnumKeyEx _
                Lib "advapi32.dll" Alias "RegEnumKeyExA" _
                (ByVal hKey As Long, _
                 ByVal dwIndex As Long, _
                 ByVal lpName As String, _
                 lpcbName As Long, _
                 ByVal lpReserved As Long, _
                 ByVal lpClass As String, _
                 lpcbClass As Long, _
                 lpftLastWriteTime As FILETIME) As Long

Private Declare Function RegEnumValue _
                Lib "advapi32.dll" Alias "RegEnumValueA" _
                (ByVal hKey As Long, _
                ByVal dwIndex As Long, _
                ByVal lpValueName As String, _
                lpcbValueName As Long, _
                ByVal lpReserved As Long, _
                lpType As Long, _
                lpData As Byte, _
                lpcbData As Long) As Long

Private Declare Function RegFlushKey _
                Lib "advapi32.dll" (ByVal hKey As Long) As Long

Private Declare Function RegGetKeySecurity _
                Lib "advapi32.dll" _
                (ByVal hKey As Long, _
                 ByVal SecurityInformation As Long, _
                 pSecurityDescriptor As SECURITY_DESCRIPTOR, _
                 lpcbSecurityDescriptor As Long) As Long

Private Declare Function RegLoadKey _
                Lib "advapi32.dll" Alias "RegLoadKeyA" _
                (ByVal hKey As Long, _
                 ByVal lpSubKey As String, _
                 ByVal lpFile As String) As Long

Private Declare Function RegNotifyChangeKeyValue _
                Lib "advapi32.dll" _
                (ByVal hKey As Long, _
                 ByVal bWatchSubtree As Long, _
                 ByVal dwNotifyFilter As Long, _
                 ByVal hEvent As Long, _
                 ByVal fAsynchronus As Long) As Long

Private Declare Function RegOpenKey _
                Lib "advapi32.dll" Alias "RegOpenKeyA" _
                (ByVal hKey As Long, _
                 ByVal lpSubKey As String, _
                 phkResult As Long) As Long

Private Declare Function RegOpenKeyEx _
                Lib "advapi32.dll" Alias "RegOpenKeyExA" _
                (ByVal hKey As Long, _
                 ByVal lpSubKey As String, _
                 ByVal ulOptions As Long, _
                 ByVal samDesired As Long, _
                 phkResult As Long) As Long

Private Declare Function RegQueryInfoKey _
                Lib "advapi32.dll" Alias "RegQueryInfoKeyA" _
                (ByVal hKey As Long, _
                 ByVal lpClass As String, _
                 lpcbClass As Long, _
                 ByVal lpReserved As Long, _
                 lpcSubKeys As Long, _
                 lpcbMaxSubKeyLen As Long, _
                 lpcbMaxClassLen As Long, _
                 lpcValues As Long, _
                 lpcbMaxValueNameLen As Long, _
                 lpcbMaxValueLen As Long, _
                 lpcbSecurityDescriptor As Long, _
                 lpftLastWriteTime As FILETIME) As Long

Private Declare Function RegQueryValue _
                Lib "advapi32.dll" Alias "RegQueryValueA" _
                (ByVal hKey As Long, _
                 ByVal lpSubKey As String, _
                 ByVal lpValue As String, _
                 lpcbValue As Long) As Long

Private Declare Function RegQueryValueEx _
                Lib "advapi32.dll" Alias "RegQueryValueExA" _
                (ByVal hKey As Long, _
                 ByVal lpValueName As String, _
                 ByVal lpReserved As Long, _
                 lpType As Long, _
                 lpData As Any, _
                 lpcbData As Long) As Long         ' Note that if you declare the lpData parameter as String, you must pass it By Value.

Private Declare Function RegQueryValueExString _
                Lib "advapi32.dll" Alias "RegQueryValueExA" _
                (ByVal hKey As Long, _
                 ByVal lpValueName As String, _
                 ByVal lpReserved As Long, _
                 lpType As Long, _
                 ByVal lpData As String, _
                 lpcbData As Long) As Long
                 
Private Declare Function RegReplaceKey _
                Lib "advapi32.dll" Alias "RegReplaceKeyA" _
                (ByVal hKey As Long, _
                 ByVal lpSubKey As String, _
                 ByVal lpNewFile As String, _
                 ByVal lpOldFile As String) As Long

Private Declare Function RegRestoreKey _
                Lib "advapi32.dll" Alias "RegRestoreKeyA" (ByVal hKey As Long, ByVal lpFile As String, ByVal dwFlags As Long) As Long

Private Declare Function RegSaveKey _
                Lib "advapi32.dll" Alias "RegSaveKeyA" _
                (ByVal hKey As Long, _
                 ByVal lpFile As String, _
                 lpSecurityAttributes As SECURITY_ATTRIBUTES) As Long
 
Private Declare Function RegSetKeySecurity _
                Lib "advapi32.dll" _
                (ByVal hKey As Long, _
                 ByVal SecurityInformation As Long, _
                 pSecurityDescriptor As SECURITY_DESCRIPTOR) As Long

Private Declare Function RegSetValue _
                Lib "advapi32.dll" Alias "RegSetValueA" _
                (ByVal hKey As Long, _
                 ByVal lpSubKey As String, _
                 ByVal dwType As Long, _
                 ByVal lpData As String, _
                 ByVal cbData As Long) As Long

Private Declare Function RegSetValueEx _
                Lib "advapi32.dll" Alias "RegSetValueExA" _
                (ByVal hKey As Long, _
                 ByVal lpValueName As String, _
                 ByVal Reserved As Long, _
                 ByVal dwType As Long, _
                 lpData As Any, _
                 ByVal cbData As Long) As Long         ' Note that if you declare the lpData parameter as String, you must pass it By Value.

Private Declare Function RegUnLoadKey _
                Lib "advapi32.dll" Alias "RegUnLoadKeyA" _
                (ByVal hKey As Long, _
                 ByVal lpSubKey As String) As Long

Public Function QueryValue(ByVal RootKey As regRootKey, _
                           ByVal SubKey As String, _
                           ByVal ValueName As String, _
                           Optional ByVal ValueType As regREGType = regUnKnown, _
                           Optional ByVal Default As Variant) As Variant
'//////////////////////////////////////////////////////////////////////////////
' QueryValue
'
' Query a Key in the registry and return the value.
' If no value was found, use default if present
'
' In:         RootKey. The RootKey under which the subkeys are nested.
'             SubKey. The Key path without the rootkey.
'             ValueName. The name of the value to read.
'
' Out:        {QueryValue}. ReturnValue from function. The Value retreived
'                           from the registry. - Long, String or string
'                           with ASCII values (chr(10), chr(3) etc.).
'                           Empty if error.
'                           Empty if no value and no default present.
'
' Events:     Error. In case of Errors (both API and RunTime).
'
' Functions:  KeyType.                Return type of key.
'             AssignHandle.           Seek Constant with enum.
'             RegOpenKeyEx.           API
'             RegQueryValueEx.        API
'             RegQueryValueExString.  API
'             RegCloseKey.            API
'
' Uses:       CAPIError
'             CEnum
'             Err
'
' Notes:      .
'
' Example:    To query HKEY_LOCAL_MACHINE\Software\ControlChrom\TestValue = 4,
'             enter
'             QueryValue(regHKEY_LOCAL_MACHINE, "SoftWare\ControlChrom", "TestValue")
'
'             The returnvalue will be 4. If no ValueType is passed, the registry
'             is enumerated for the type. If the registry value is a string or binary type,
'             and no value is present, the Default is returned, if Default is given.
'             when an error occurs, or no Default and value are present, the return
'             value of the function is empty.
'
' Programmer: Geert Jansen
' Date:       August 02 2001
' CopyRight:  (c) 2000 ControlChrom
'
' Reference:  .
'//////////////////////////////////////////////////////////////////////////////
  Dim lngResult As Long
  Dim varReturn As String
  
  Dim lngRootKey As Long
  Dim lngRegKey As Long
  
  
  Dim varData As Variant
  Dim lngDataLen As Long
  Dim lngData As Long
  Dim lngKeyHandle As Long
  
  Dim strData As String
  
  Dim objCAPIError As CAPIError
  Dim varParaMeters(0 To 4, 0 To 2) As Variant
      '
  On Error GoTo ErrorHandler
      '
  Set objCAPIError = New CAPIError
  
  ' 1) Open the Key. Since RootKey is already the right value, no conversion
  '    from enum to constant is needed.
  
  lngResult = AssignHandle(RootKey, lngRootKey)
  If lngResult <> ERROR_SUCCESS Then
    Err.Raise vbObjectError + 1000, "AssignHandle API", objCAPIError.ErrorString(lngResult)
  End If
  
  lngResult = RegOpenKeyEx(lngRootKey, SubKey, 0&, KEY_READ, lngKeyHandle)
  If lngResult <> ERROR_SUCCESS Then
    Err.Raise vbObjectError + 1000, "RegOpenKeyEx API", objCAPIError.ErrorString(lngResult)
  End If
  

  ' 2) Check the type of the value
  If ValueType = regUnKnown Or ValueType = regREG_NONE Then
    ValueType = KeyType(RootKey, SubKey, ValueName)
  End If
  
  ' 3) Each type needs a different approach.
  Select Case ValueType
    Case regREG_DWORD ' DWORD
      ' 3a) a DWORD value has 4 bytes. it is retreived as long.
      lngDataLen = 4
      lngResult = RegQueryValueEx(lngKeyHandle, ValueName, 0, REG_DWORD, lngData, lngDataLen)
      If lngResult <> ERROR_SUCCESS Then
        Err.Raise vbObjectError + 1000, "RegQueryValueEx API", objCAPIError.ErrorString(lngResult)
      End If
      
      ' 3a-1) a DWORD has always a value.
      varData = lngData
      
    Case regREG_SZ  ' STRING
      ' 3b) a string needs an adjusted RegQueryValueEx.
      
      ' 3b-1) first try to get the value. This will return the size
      '       of the buffer. Then size the buffer and try again.
      lngResult = RegQueryValueExString(lngKeyHandle, ValueName, 0, REG_SZ, strData, lngDataLen)
      If lngResult <> ERROR_SUCCESS Then
        Err.Raise vbObjectError + 1000, "RegQueryValueExString API", objCAPIError.ErrorString(lngResult)
      End If
      
      strData = Space(lngDataLen)
      lngResult = RegQueryValueExString(lngKeyHandle, ValueName, 0, REG_SZ, strData, lngDataLen)
      If lngResult <> ERROR_SUCCESS Then
        Err.Raise vbObjectError + 1000, "RegQueryValueExString API", objCAPIError.ErrorString(lngResult)
      End If
      
      ' 3b-2) The size is including a NULL char. Remove the NULL char.
      '       HOWEVER, If there was no value present, lngDataLen = 0, and
      '       no NULL char is present. In that case, return Default if
      '       Default was passed as an argument (optional!).
      If lngDataLen > 0 Then
        varData = Left$(strData, lngDataLen - 1)
      ElseIf IsMissing(Default) = False Then
        varData = Default
      End If
    
    Case regREG_BINARY  ' BYTES
      ' 3c) a binary row is read as a string.
      
      ' 3c-1) first try to get the value. This will return the size
      '       of the buffer. Then size the buffer and try again.
      lngResult = RegQueryValueExString(lngKeyHandle, ValueName, 0, REG_SZ, strData, lngDataLen)
      If lngResult <> ERROR_SUCCESS Then
        Err.Raise vbObjectError + 1000, "RegQueryValueExString API", objCAPIError.ErrorString(lngResult)
      End If
      
      strData = Space(lngDataLen)
      lngResult = RegQueryValueExString(lngKeyHandle, ValueName, 0, REG_SZ, strData, lngDataLen)
      If lngResult <> ERROR_SUCCESS Then
        Err.Raise vbObjectError + 1000, "RegQueryValueExString API", objCAPIError.ErrorString(lngResult)
      End If
      
      ' 3c-2) Here the string is NOT NULL Terminated. The string characters
      '       are ascii values. to convert, use Asc(character).
      '       HOWEVER, if a value is a zero length binary value, then the
      '       length is 0. in that case, return Default if Default was
      '       passed as an argument (optional!).
      If lngDataLen > 0 Then
        varData = strData
      ElseIf IsMissing(Default) = False Then
        varData = Default
      End If
    Case Else
    
  End Select
  
  lngResult = RegCloseKey(lngKeyHandle)
  If lngResult <> ERROR_SUCCESS Then
    Err.Raise vbObjectError + 1000, "RegCloseKey API", objCAPIError.ErrorString(lngResult)
  End If
  varReturn = varData
      '
ExitHere:
      '
  Set objCAPIError = Nothing
  QueryValue = varReturn
  Exit Function
      '
ErrorHandler:
    
  varParaMeters(0, 0) = "RootKey"
  varParaMeters(0, 1) = "regRootKey"
  varParaMeters(0, 2) = RootKey
  
  varParaMeters(1, 0) = "SubKey"
  varParaMeters(1, 1) = "String"
  varParaMeters(1, 2) = SubKey
  
  varParaMeters(2, 0) = "ValueName"
  varParaMeters(2, 1) = "String"
  varParaMeters(2, 2) = ValueName
  
  varParaMeters(3, 0) = "ValueType"
  varParaMeters(3, 1) = "regREGType"
  varParaMeters(3, 2) = ValueType
  
  varParaMeters(4, 0) = "Default"
  varParaMeters(4, 1) = "Variant"
  varParaMeters(4, 2) = Default
  
  RaiseEvent Error(Err.Number, Err.Description, Err.Source & "\QueryValue", Err.HelpFile, Err.HelpContext, varParaMeters)
  
  Resume ExitHere
      '
End Function

Private Function AssignHandle(ByVal enmRootKey As regRootKey, _
                              ByRef lngRootKey As Long) As Long
'//////////////////////////////////////////////////////////////////////////////
' AssignHandle
'
' Convert a enum to a constant value. The API can't use enum values directly
' as input, even if the value of the enum is correct and enums are stored
' as long.
'
' In:         enmRootKey. The enum to convert
'
' Out:        {GetRootKey}. ReturnValue from function. 0 = OK, else err.nr
'             lngRootKey. The converted enmRootKey
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
' Date:       August 02 2001
' CopyRight:  (c) 2000 ControlChrom
'
' Reference:  .
'//////////////////////////////////////////////////////////////////////////////
  Dim lngResult As Long
  Dim lngReturn As Long
  
  Dim lngHKEY As Long
      '
  On Error GoTo ErrorHandler
      '
  lngReturn = ERROR_SUCCESS
  
  Select Case enmRootKey
    Case regHKEY_CLASSES_ROOT
      lngHKEY = HKEY_CLASSES_ROOT
    Case regHKEY_CURRENT_USER
      lngHKEY = HKEY_CURRENT_USER
    Case regHKEY_LOCAL_MACHINE
      lngHKEY = HKEY_LOCAL_MACHINE
    Case regHKEY_USERS
      lngHKEY = HKEY_USERS
    Case regHKEY_CURRENT_CONFIG
      lngHKEY = HKEY_CURRENT_CONFIG
    Case regHKEY_DYN_DATA
      lngHKEY = HKEY_DYN_DATA
    Case regHKEY_PERFORMANCE_DATA
      lngHKEY = HKEY_PERFORMANCE_DATA
    Case Else
      lngHKEY = 0
  End Select
      '
ExitHere:
      '
  lngRootKey = lngHKEY
  AssignHandle = lngReturn
  Exit Function
      '
ErrorHandler:
  lngReturn = Err.Number
  Resume ExitHere
      '
End Function

Private Function KeyType(ByVal enmRootKey As regRootKey, _
                         ByVal strSubKey As String, _
                         ByVal strValueName As String) As Long
'//////////////////////////////////////////////////////////////////////////////
' KeyType
'
' Return the Type of the value (REG_SZ, REG_BINARY, REG_DWORD)
'
' In:         .
'
' Out:        {KeyType}. ReturnValue from function
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
' Date:       August 02 2001
' CopyRight:  (c) 2000 ControlChrom
'
' Reference:  .
'//////////////////////////////////////////////////////////////////////////////
  Dim lngResult As Long
  Dim lngReturn As Long
  
  Dim lngRootKey As Long
  Dim lngKeyHandle As Long
  
  Dim strClassName As String
  Dim lngClassNameLength As Long
  Dim lngNrOfSubKeys As Long
  Dim lngMaxSubKeyLen As Long
  Dim lngMaxClassLen As Long
  Dim lngNrOfValues  As Long
  Dim lngMaxValueNameLen As Long
  Dim lngMaxValueLen As Long
  Dim typLastWriteTime As FILETIME
  
  Dim lngIndex As Long
  Dim strTempValueName As String
  Dim lngTempValueNameLen As Long
  Dim lngType As Long
  
  Dim bytData(0 To 254) As Byte
  Dim lngDataLen As Long
      '
  On Error GoTo ErrorHandler
      '
  lngReturn = 0
  
  ' Open the Key
  lngResult = AssignHandle(enmRootKey, lngRootKey)
  lngResult = RegOpenKeyEx(lngRootKey, strSubKey, 0&, KEY_READ, lngKeyHandle)
  
  'See that there are Values in the SubKey.
  lngResult = RegQueryInfoKey(lngKeyHandle, strClassName, lngClassNameLength, 0, lngNrOfSubKeys, lngMaxSubKeyLen, lngMaxClassLen, lngNrOfValues, lngMaxValueNameLen, lngMaxValueLen, 0, typLastWriteTime)
  
  lngIndex = 0
  Do Until lngResult <> ERROR_SUCCESS Or lngIndex >= lngNrOfValues
  
    strTempValueName = Space(255)
    lngTempValueNameLen = 255
    lngDataLen = 255
    
    lngResult = RegEnumValue(lngKeyHandle, lngIndex, strTempValueName, lngTempValueNameLen, 0, lngType, bytData(0), lngDataLen)
    If lngResult = ERROR_SUCCESS Then
      ' Value is NULL terminated.
      strTempValueName = Left$(strTempValueName, lngTempValueNameLen)
      
      If UCase$(strTempValueName) = UCase$(strValueName) Then
        KeyType = lngType
      End If
      
    End If
    lngIndex = lngIndex + 1
  Loop
  
  lngResult = RegCloseKey(lngKeyHandle)
      '
ExitHere:
      '
  KeyType = lngReturn
  Exit Function
      '
ErrorHandler:
  ' [ Handle your error here]
  Resume ExitHere
      '
End Function

Private Sub Class_Initialize()
'
End Sub

Private Sub Class_Terminate()
'
End Sub
