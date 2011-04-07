'Create a form with:
' • Two commands (Command1, Command2)
' • One Drive (Drive1)
' • One label (Label1)
Const RESOURCETYPE_DISK = &H1
Private Type NETRESOURCE
  dwScope As Long
  dwType As Long
  dwDisplayType As Long
  dwUsage As Long
  lpLocalName As String
  lpRemoteName As String
  lpComment As String
  lpProvider As String
End Type

Private Declare Function WNetAddConnection2 Lib "mpr.dll" Alias "WNetAddConnection2A" (lpNetResource As NETRESOURCE, ByVal lpPassword As String, ByVal lpUserName As String, ByVal dwFlags As Long) As Long
Private Declare Function WNetCancelConnection2 Lib "mpr.dll" Alias "WNetCancelConnection2A" (ByVal lpName As String, ByVal dwFlags As Long, ByVal fForce As Long) As Long

Dim theNetResource As NETRESOURCE
Dim UserName As String
Dim UserPassword As String


Private Sub Form_Load()
  'example created by Tim Derdelinckx (tderdelinckx@allgeier.be)
  'visit his site at http://www.allgeier.be
  theNetResource.lpRemoteName = "\\SERVER\ShareName"
  theNetResource.lpLocalName = "Z:"
  UserName = "Username"
  UserPassword = "Password"
  theNetResource.dwType = RESOURCETYPE_DISK
  Label1.Caption = ""
  Command1.Caption = "Add Connection"
  Command2.Caption = "Cancel Connection"
End Sub


Private Sub Command1_Click()
  Dim Result&
    Result = WNetAddConnection2(theNetResource, UserPassword, UserName, 0)
    If Result = 0 Then
      Label1.Caption = "Connection Established."
      Drive1.Drive = theNetResource.lpLocalName
      Drive1.Refresh
    Else
      Label1.Caption = "Connection not possible."
      MsgBox "Connection not possible." & vbCrLf & "(Maybe the drive is allready used or the share doesn't exist)"
    End If
End Sub


Private Sub Command2_Click()
  Dim Result&
    Result = WNetCancelConnection2(theNetResource.lpLocalName, 0, 0)
    If Result = 0 Then
      Label1.Caption = "Connection Closed."
    Else
      Label1.Caption = "Close connection not possible."
    End If
    Drive1.Refresh
End Sub


