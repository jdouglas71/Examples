VERSION 5.00
Begin VB.Form frmStart 
   Caption         =   "TC Logon"
   ClientHeight    =   1785
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   1785
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CheckBox chkSilentLogon 
      Caption         =   "SilentLogon"
      Height          =   255
      Left            =   0
      TabIndex        =   2
      Top             =   840
      Width           =   1455
   End
   Begin VB.TextBox txtUserName 
      Height          =   285
      Left            =   1200
      TabIndex        =   0
      Top             =   120
      Width           =   3375
   End
   Begin VB.TextBox txtPassword 
      Height          =   285
      Left            =   1200
      TabIndex        =   1
      Top             =   480
      Width           =   3375
   End
   Begin VB.CommandButton cmdLogOn 
      Caption         =   "LogOn"
      Default         =   -1  'True
      Height          =   495
      Left            =   3360
      TabIndex        =   4
      Top             =   840
      Width           =   1215
   End
   Begin VB.Label lblLoggedOn 
      Height          =   255
      Left            =   0
      TabIndex        =   6
      Top             =   1320
      Width           =   4575
   End
   Begin VB.Label Label2 
      Caption         =   "UserName"
      Height          =   255
      Left            =   0
      TabIndex        =   5
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "PassWord"
      Height          =   255
      Left            =   0
      TabIndex        =   3
      Top             =   480
      Width           =   1215
   End
End
Attribute VB_Name = "frmStart"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private WithEvents mclsTCLogin As CTCLogIn
Attribute mclsTCLogin.VB_VarHelpID = -1
Private Const constMessage As String = "User LogOn is: "

Private Sub cmdLogOn_Click()
  Dim booSilentLogon As Boolean
  
  Select Case chkSilentLogon.Value
    Case vbUnchecked
      booSilentLogon = False
    Case vbChecked
      booSilentLogon = True
    Case Else
      booSilentLogon = False
  End Select
  
  mclsTCLogin.LogOn txtUserName.Text, txtPassword.Text, booSilentLogon
End Sub

Private Sub Form_Initialize()
  Set mclsTCLogin = New CTCLogIn
End Sub

Private Sub Form_Load()
  lblLoggedOn.Caption = constMessage & mclsTCLogin.LoggedOn
End Sub

Private Sub Form_Terminate()
  Set mclsTCLogin = Nothing
End Sub

Private Sub mclsTCLogin_LogOnStatus(ByVal LoggedOn As Boolean)
  lblLoggedOn.Caption = constMessage & LoggedOn
End Sub
