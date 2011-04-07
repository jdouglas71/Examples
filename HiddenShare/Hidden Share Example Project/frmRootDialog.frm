VERSION 5.00
Begin VB.Form frmHiddenShareDialog 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Fusion AE Files"
   ClientHeight    =   4215
   ClientLeft      =   2760
   ClientTop       =   3360
   ClientWidth     =   8295
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4215
   ScaleWidth      =   8295
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox FusionFileName 
      Height          =   285
      Left            =   1200
      TabIndex        =   5
      Text            =   "defaultFileName"
      Top             =   3240
      Width           =   6975
   End
   Begin VB.DirListBox FusionAEPath 
      Height          =   3015
      Left            =   120
      TabIndex        =   3
      Top             =   120
      Width           =   3855
   End
   Begin VB.FileListBox FusionAEFile 
      Height          =   3015
      Left            =   4080
      ReadOnly        =   0   'False
      System          =   -1  'True
      TabIndex        =   2
      Top             =   120
      Width           =   4095
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   4200
      TabIndex        =   1
      Top             =   3720
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   2520
      TabIndex        =   0
      Top             =   3720
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "File Name:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   3240
      Width           =   855
   End
End
Attribute VB_Name = "frmHiddenShareDialog"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
    ' RJB NOTES:
    '   Need to set current path to selected path!
    '   Assumes that FusionAEPath has been previously mapped.

Option Explicit

Public OK As Boolean



Private Sub CancelButton_Click()
    
    OK = False
    Me.Hide

End Sub

Private Sub FusionAEFile_Click()

    FusionFileName.Text = FusionAEFile.FileName
    
End Sub

Private Sub FusionAEPath_Change()

    FusionAEFile.Path = FusionAEPath.Path
    
End Sub

Private Sub FusionAEPath_Click()

    FusionAEFile.Path = FusionAEPath.List(FusionAEPath.ListIndex)
   
End Sub

Private Sub OKButton_Click()
    
    OK = True
    Me.Hide

End Sub
