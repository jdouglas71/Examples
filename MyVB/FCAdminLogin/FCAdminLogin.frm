VERSION 5.00
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "msadodc.ocx"
Begin VB.Form FCAdminLogin 
   Caption         =   "FC Admin Login"
   ClientHeight    =   2768
   ClientLeft      =   64
   ClientTop       =   336
   ClientWidth     =   5280
   LinkTopic       =   "Form1"
   ScaleHeight     =   2768
   ScaleWidth      =   5280
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtXMLOut 
      DataField       =   "SERIALIZATION"
      DataSource      =   "adoDataGuy"
      Height          =   4112
      Left            =   512
      MultiLine       =   -1  'True
      TabIndex        =   6
      Text            =   "FCAdminLogin.frx":0000
      Top             =   2944
      Visible         =   0   'False
      Width           =   3600
   End
   Begin VB.CommandButton cancelButton 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   400
      Left            =   2672
      TabIndex        =   4
      Top             =   1920
      Width           =   912
   End
   Begin VB.CommandButton okButton 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   400
      Left            =   1392
      TabIndex        =   3
      Top             =   1920
      Width           =   912
   End
   Begin MSAdodcLib.Adodc adoDataGuy 
      Height          =   560
      Left            =   128
      Top             =   1920
      Visible         =   0   'False
      Width           =   1344
      _ExtentX        =   2363
      _ExtentY        =   975
      ConnectMode     =   0
      CursorLocation  =   3
      IsolationLevel  =   -1
      ConnectionTimeout=   15
      CommandTimeout  =   30
      CursorType      =   3
      LockType        =   3
      CommandType     =   1
      CursorOptions   =   0
      CacheSize       =   50
      MaxRecords      =   0
      BOFAction       =   0
      EOFAction       =   0
      ConnectStringType=   3
      Appearance      =   1
      BackColor       =   -2147483643
      ForeColor       =   -2147483640
      Orientation     =   0
      Enabled         =   -1
      Connect         =   "DSN=FCAdminData"
      OLEDBString     =   ""
      OLEDBFile       =   ""
      DataSourceName  =   "FCAdminData"
      OtherAttributes =   ""
      UserName        =   ""
      Password        =   ""
      RecordSource    =   "select SERIALIZATION from SerializedObjects  where NAME = 'FusionUsers'"
      Caption         =   "Adodc1"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.38
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      _Version        =   393216
   End
   Begin VB.TextBox txtPassword 
      Height          =   304
      IMEMode         =   3  'DISABLE
      Left            =   2156
      PasswordChar    =   "*"
      TabIndex        =   1
      Top             =   1152
      Width           =   2192
   End
   Begin VB.TextBox txtUserName 
      Height          =   304
      Left            =   2156
      TabIndex        =   0
      Top             =   384
      Width           =   2192
   End
   Begin VB.Label lblPassword 
      Caption         =   "Password"
      Height          =   272
      Left            =   768
      TabIndex        =   5
      Top             =   1152
      Width           =   1168
   End
   Begin VB.Label lblUserName 
      Caption         =   "User Name"
      Height          =   272
      Left            =   768
      TabIndex        =   2
      Top             =   384
      Width           =   1296
   End
End
Attribute VB_Name = "FCAdminLogin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub cancelButton_Click()
    Unload Me
End Sub

Private Sub okButton_Click()
    Dim xmlDoc As DOMDocument
    Dim userNode As IXMLDOMNode
    Dim groupNode As IXMLDOMNode
    Dim allUsersNode As IXMLDOMNode
    Dim propNode As IXMLDOMNode
    Dim nodeList As IXMLDOMNodeList
    Dim propList As IXMLDOMNodeList
    Dim theUserNode As IXMLDOMNode
    Dim i As Integer
    Dim j As Integer
    
    Dim userNodeList As IXMLDOMNodeList
    Dim userNameStr As String
    Dim passwordStr As String
    Dim testUserNameStr As String
    Dim testPasswordNameStr As String
    
    On Error GoTo ErrorMan
    
    userNameStr = txtUserName.Text
    passwordStr = txtPassword.Text
    
    Set xmlDoc = New DOMDocument
    
    xmlDoc.loadXML (txtXMLOut.Text)
    
    Set nodeList = xmlDoc.getElementsByTagName(FUSION_USER_GROUP)
    
    'Find the All Users Group
    For i = 0 To (nodeList.length - 1)
        Set groupNode = nodeList.nextNode
        'MsgBox groupNode.Attributes.getNamedItem(FUSION_USER_GROUP_NAME).Text
        If groupNode.Attributes.getNamedItem(FUSION_USER_GROUP_NAME).Text = FUSION_ALL_USERS_GROUP Then
            Set allUsersNode = groupNode
            Exit For
        End If
    Next
    
    'Find a user node with the given name and password
    Set nodeList = allUsersNode.childNodes
    For i = 0 To (nodeList.length - 1)
        Set userNode = nodeList.nextNode
        'MsgBox userNode.nodeName
        Set propList = userNode.childNodes
        For j = 0 To (propList.length - 1)
            Set propNode = propList.nextNode
            'MsgBox propNode.nodeName
            If propNode.Attributes.getNamedItem(FUSION_KEY_ATTRIBUTE).Text = FUSION_USER_NAME Then
                testUserNameStr = propNode.Attributes.getNamedItem(FUSION_VALUE_ATTRIBUTE).Text
            End If
            If propNode.Attributes.getNamedItem(FUSION_KEY_ATTRIBUTE).Text = FUSION_USER_PASSWORD Then
                testPasswordStr = propNode.Attributes.getNamedItem(FUSION_VALUE_ATTRIBUTE).Text
            End If
        Next
        If (testUserNameStr = userNameStr) And (testPasswordStr = passwordStr) Then
            Set theUserNode = userNode
        End If
    Next
    
    'MsgBox ("UserName: " & txtUserName.Text & " Password: " & txtPassword.Text)
    If theUserNode Is Nothing Then
        MsgBox ("Login failed")
    Else
        MsgBox ("Login successful")
    End If
    
    Exit Sub
    
ErrorMan:
    MsgBox ("An Error occurred, you'd better fix it")
    
End Sub

Private Sub Text1_Change()

End Sub
