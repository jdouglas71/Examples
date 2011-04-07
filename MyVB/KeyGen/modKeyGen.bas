Attribute VB_Name = "modKeyGen"
Option Explicit

'Declarations for CodeGen functions lifted directly from the Armadillo help
'See topic Overview|Keys|Creating Keys
'JGD 2/20/02
Declare Function VBCreateCode Lib "CodeGen.DLL" (ByVal Name$, ByVal EncryptionTemplate$, ByVal HardwareId As Long, ByVal OtherInfo As Integer) As String
Declare Function VBCreateCode2 Lib "CodeGen.DLL" (ByVal Level As Long, ByVal Name$, ByVal EncryptionTemplate$, ByVal HardwareId As Long, ByVal OtherInfo1 As Integer, ByVal OtherInfo2 As Integer, ByVal OtherInfo3 As Integer, ByVal OtherInfo4 As Integer, ByVal OtherInfo5 As Integer) As String
Declare Function MakeDate Lib "CodeGen.DLL" (ByVal Year As Long, ByVal Month As Long, ByVal Day As Long) As Integer

'Global to hold the name of the encryption template. I'd like this to come from
'an INI file as soon as I figure out how to make this stupid environment call
'GetPropertyString.
'JGD 2/20/02
Public Const TheEncryptionTemplate = "this is a test"



'Function for generating the key using the name and hardwareId provided by the user
'TODO: The encryption template name is hardcoded for now, but I would like it to
'TODO: from an INI file.
Function GetTheKey(Name As String, HardwareId As Long) As String

    Dim tmpStr As String
    tmpStr = "Name: " & Name & " HardwareId: " & CStr(HardwareId)
    Call MsgBox(tmpStr)

    GetTheKey = VBCreateCode(Name, HardwareId, TheEncryptionTemplate, 0)

    'GetTheKey = "Fuck off Bastard"

End Function
