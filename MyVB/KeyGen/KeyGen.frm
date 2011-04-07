VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Key Generator"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton OkButton 
      Caption         =   "Generate Key"
      Default         =   -1  'True
      Height          =   495
      Left            =   2880
      TabIndex        =   4
      Top             =   2400
      Width           =   1215
   End
   Begin VB.CommandButton CancelButton 
      Cancel          =   -1  'True
      Caption         =   "Close"
      CausesValidation=   0   'False
      Height          =   495
      Left            =   1560
      TabIndex        =   3
      Top             =   2400
      Width           =   1095
   End
   Begin VB.CommandButton ViewKeyLogButton 
      Caption         =   "&View Log"
      Height          =   495
      Left            =   360
      TabIndex        =   2
      Top             =   2400
      Width           =   975
   End
   Begin VB.TextBox HardwareIdText 
      Height          =   495
      Left            =   360
      TabIndex        =   1
      Top             =   1560
      Width           =   3735
   End
   Begin VB.TextBox NameText 
      Height          =   495
      Left            =   360
      TabIndex        =   0
      Top             =   480
      Width           =   3735
   End
   Begin VB.Label Label2 
      Caption         =   "Name"
      Height          =   255
      Left            =   360
      TabIndex        =   6
      Top             =   240
      Width           =   855
   End
   Begin VB.Label Label1 
      Caption         =   "Hardware Id"
      Height          =   255
      Left            =   360
      TabIndex        =   5
      Top             =   1320
      Width           =   975
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub CancelButton_Click()
    Unload Me
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Set Form1 = Nothing
End Sub

Private Sub OkButton_Click()
    Dim retVal As String

    If (NameText.Text = "") Then
        Call MsgBox("Name must have a value.", vbExclamation, "Error")
        Exit Sub
    End If

    If (IsNumeric("&H" & HardwareIdText.Text) = False) Then
        Call MsgBox("Please Enter a number for the Hardware Id", vbExclamation, "Error")
        Exit Sub
    End If

    retVal = GetTheKey(NameText.Text, CLng(HardwareIdText.Text))

    Call MsgBox(retVal, vbOKOnly, "The Key")

End Sub

