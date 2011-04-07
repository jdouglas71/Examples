Private Sub DecodeXMLStringFromDOMObject(xmlString As String)

  Dim indx As Integer
  Dim indx2 As Integer
  Dim tempVariable As Variable
  Dim numSteps As Long
  Dim numVariables As Long

  Dim xmlDOMDocObject As DOMDocument
  Dim myNode As IXMLDOMNode
  Dim MSADataNode As IXMLDOMNode
  Dim variablesNode As IXMLDOMNode
  Dim variableNode As IXMLDOMNode
  Dim originalLevelSettingsNode As IXMLDOMNode

  Set xmlDOMDocObject = New DOMDocument

  xmlDOMDocObject.async = False
  Call xmlDOMDocObject.loadXML(xmlString)

  Set MSADataNode = xmlDOMDocObject.documentElement

  m_strTargetSource = MSADataNode.selectSingleNode("Target_Source").Text
  m_strTargetResult = MSADataNode.selectSingleNode("Target_Result").Text
  numSteps = CInt(MSADataNode.selectSingleNode("Number_Of_Steps").Text)

  m_strStepDirection = MSADataNode.selectSingleNode("Step_Direction").Text
  StepDirection = m_strStepDirection

  Call LoadNumStepsComboWithValues(2, 50, numSteps)

  'Cycle through the child nodes for 'Variables'
  Set variablesNode = MSADataNode.selectSingleNode("Variables")

  numVariables = variablesNode.childNodes.length

  ReDim m_varMSAVarLevels(1 To numVariables)
  ReDim m_varOriginalMSAVarLevels(1 To numVariables)
  ReDim m_varMSARatios(1 To numVariables)
  ReDim m_varMSAVarIDs(1 To numVariables)

  For indx = 1 To numVariables

    Set variableNode = variablesNode.childNodes.Item(indx - 1)

    m_varMSAVarIDs(indx) = variableNode.selectSingleNode("Var_ID").Text
    m_varMSARatios(indx) = variableNode.selectSingleNode("MSA_Ratio").Text
    m_varMSAVarLevels(indx) = variableNode.selectSingleNode("Coeff_Value").Text
    m_varOriginalMSAVarLevels(indx) = variableNode.selectSingleNode("Coeff_Value").Text

  Next indx


End Sub

Private Sub CreateXMLDOMObject()

  Dim indx As Integer
  Dim indx2 As Integer
  Dim tempVariable As Variable

  Dim xmlDOMDocObject As DOMDocument
  Dim processingInstruction As IXMLDOMProcessingInstruction
  Dim documentNode As IXMLDOMElement
  Dim myNode As IXMLDOMElement
  Dim variablesNode As IXMLDOMElement
  Dim variableNode As IXMLDOMElement
  Dim originalLevelSettingsNode As IXMLDOMElement

  Set xmlDOMDocObject = New DOMDocument

  xmlDOMDocObject.async = False

  '1. Create the Processing Instruction Node
  Set processingInstruction = xmlDOMDocObject.createProcessingInstruction("xml", " version=""1.0""")
  Call xmlDOMDocObject.appendChild(processingInstruction)

  '2. Create the MSAData Document node
  Set documentNode = xmlDOMDocObject.createElement("MSAData")
  Call xmlDOMDocObject.appendChild(documentNode)

  '3. Create Child Nodes
  Call CreateXMLNodeElement(xmlDOMDocObject, documentNode, "Target_Source", m_strTargetSource, myNode)
  Call CreateXMLNodeElement(xmlDOMDocObject, documentNode, "Target_Result", m_strTargetResult, myNode)
  Call CreateXMLNodeElement(xmlDOMDocObject, documentNode, "Number_Of_Steps", CStr(m_lngNumStepsPreviousValue), myNode)
  Call CreateXMLNodeElement(xmlDOMDocObject, documentNode, "Step_Direction", m_strStepDirection, myNode)

  Call CreateXMLNodeElement(xmlDOMDocObject, documentNode, "Variables", "", myNode)
  Set variablesNode = myNode

  For indx = 1 To UBound(m_varMSAVarIDs)

    Set tempVariable = m_clsSMXFileObject.Variables.Item(m_varMSAVarIDs(indx))

    Call CreateXMLNodeElement(xmlDOMDocObject, variablesNode, "Variable", "", myNode)
    Set variableNode = myNode

    Call CreateXMLNodeElement(xmlDOMDocObject, variableNode, "Var_Name", tempVariable.Name, myNode)
    Call CreateXMLNodeElement(xmlDOMDocObject, variableNode, "Var_ID", tempVariable.ID, myNode)
    Call CreateXMLNodeElement(xmlDOMDocObject, variableNode, "VType", CStr(tempVariable.VType), myNode)
    Call CreateXMLNodeElement(xmlDOMDocObject, variableNode, "Coeff_Value", CStr(m_varMSAVarLevels(indx)), myNode)
    Call CreateXMLNodeElement(xmlDOMDocObject, variableNode, "MSA_Ratio", CStr(m_varMSARatios(indx)), myNode)
    Call CreateXMLNodeElement(xmlDOMDocObject, variableNode, "Number_Of_Levels", CStr(tempVariable.NumberOfLevels), myNode)

    Call CreateXMLNodeElement(xmlDOMDocObject, variableNode, "Original_Level_Settings", "", myNode)
    Set originalLevelSettingsNode = myNode

    For indx2 = 1 To tempVariable.NumberOfLevels
      Call CreateXMLNodeElement(xmlDOMDocObject, originalLevelSettingsNode, "Level_Value", CStr(tempVariable.Level(indx2)), myNode, "Level", CStr(indx2))
    Next indx2

  Next indx

  '4. Save the XML Data String to the Extended Properties of the Design Class
  If m_clsSMXFileObject.Design.ExtendedProperties.DoesPropertyExist("XML_MSADataString") = True Then
    m_clsSMXFileObject.Design.ExtendedProperties("XML_MSADataString").Value = xmlDOMDocObject.xml
  Else
    Call m_clsSMXFileObject.Design.ExtendedProperties.Append("XML_MSADataString", xmlDOMDocObject.xml, vbString)
  End If

End Sub

Private Sub CreateXMLNodeElement(oDomObj As DOMDocument, oParentNode As IXMLDOMElement, sNodeName As String, sNodeValue As String, _
    oTempNode As IXMLDOMElement, Optional sAttributeName As String = "", Optional sAttributeValue = "")

  Set oTempNode = oDomObj.createElement(sNodeName)

  If sNodeValue <> "" Then
    oTempNode.Text = sNodeValue
  End If

  If sAttributeName <> "" Then
    Call oTempNode.setAttribute(sAttributeName, sAttributeValue)
  End If

  Call oParentNode.appendChild(oTempNode)

End Sub

