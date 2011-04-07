VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CEnum"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Enum regRootKey
  regHKEY_CLASSES_ROOT = &H80000000
  regHKEY_CURRENT_CONFIG = &H80000005
  regHKEY_CURRENT_USER = &H80000001
  regHKEY_DYN_DATA = &H80000006
  regHKEY_LOCAL_MACHINE = &H80000002
  regHKEY_PERFORMANCE_DATA = &H80000004
  regHKEY_USERS = &H80000003
End Enum

Public Enum regREGType
  regUnKnown = -1
  regREG_NONE = 0                       ' No value type
  regREG_SZ = 1                         ' Unicode nul terminated string
  regREG_EXPAND_SZ = 2                  ' Unicode nul terminated string
  regREG_BINARY = 3                     ' Free form binary
  regREG_DWORD = 4                      ' 32-bit number
  regREG_DWORD_LITTLE_ENDIAN = 4        ' 32-bit number (same as REG_DWORD) Little Endian = Low Byte on Low Address
  regREG_DWORD_BIG_ENDIAN = 5           ' 32-bit number Big Endian = High Byte Left (lower address)
  regREG_LINK = 6                       ' Symbolic Link (unicode)
  regREG_MULTI_SZ = 7                   ' Multiple Unicode strings
  regREG_RESOURCE_LIST = 8              ' Resource list in the resource map
End Enum
