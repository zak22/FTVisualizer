#cs ------------
    Copyright (C) 2011 by Zakaria Almatar, Husain Al-Matar, and Osamh Hamali
#ce ------------

#include <GUIConstantsEx.au3>
#include <WindowsConstants.au3>
#include <Array.au3>
#Include <String.au3>

; code start here
Global $msg,$guiW=800,$guiH=550

$gui = GUICreate("FTVisualizer", $guiW, $guiH, -1, -1, -1, $WS_EX_TOPMOST)
GUISetBkColor(0xCCBA96)
GUICtrlCreateLabel("FTVisualizer",10,10,120)
GUICtrlSetFont(-1, 15,800)
; Here is option under Birth
$gBirthH=50
$gBirth = GUICtrlCreateRadio("Birth",10,$gBirthH,150)
GUICtrlSetFont(-1, 10,700)
GUICtrlSetState(-1,$GUI_CHECKED)
GUICtrlCreateLabel("Date",25,$gBirthH+28)
$gBirthDate = GUICtrlCreateInput("",53,$gBirthH+25,65)
GUICtrlCreateLabel("Name",170,$gBirthH+28)
$gBirthName = GUICtrlCreateInput("",205,$gBirthH+25,65)
GUICtrlCreateLabel("Gender",327,$gBirthH+28)
$gBirthGender = GUICtrlCreateInput("",367,$gBirthH+25,65)
GUICtrlCreateLabel("Father",484,$gBirthH+28)
$gBirthFather = GUICtrlCreateInput("",520,$gBirthH+25,65)
GUICtrlCreateLabel("Mother",641,$gBirthH+28)
$gBirthMother = GUICtrlCreateInput("",681,$gBirthH+25,65)

; Here is option under Marriage
$gMarriageH = 120
$gMarriage = GUICtrlCreateRadio("Marriage",10,$gMarriageH,150)
GUICtrlSetFont(-1, 10,700)
GUICtrlCreateLabel("Date",25,$gMarriageH+28)
$gMarriageDate = GUICtrlCreateInput("",53,$gMarriageH+25,65)
GUICtrlCreateLabel("Name",170,$gMarriageH+28)
$gMarriageName = GUICtrlCreateInput("",205,$gMarriageH+25,65)
GUICtrlCreateLabel("Partner",327,$gMarriageH+28)
$gMarriagePartner = GUICtrlCreateInput("",367,$gMarriageH+25,65)
GUICtrlCreateLabel("Birthday",484,$gMarriageH+28)
$gMarriageBirthday = GUICtrlCreateInput("",529,$gMarriageH+25,65)

; Here is option under Divorce
$gDivorceH = 190
$gDivorce = GUICtrlCreateRadio("Divorce",10,$gDivorceH,150)
GUICtrlSetFont(-1, 10,700)
GUICtrlCreateLabel("Date",25,$gDivorceH+28)
$gDivorceDate = GUICtrlCreateInput("",53,$gDivorceH+25,65)
GUICtrlCreateLabel("Name",170,$gDivorceH+28)
$gDivorceName = GUICtrlCreateInput("",205,$gDivorceH+25,65)
GUICtrlCreateLabel("Partner",327,$gDivorceH+28)
$gDivorcePartner= GUICtrlCreateInput("",367,$gDivorceH+25,65)

; Here is option under Death
$gDeathH = 260
$gDeath = GUICtrlCreateRadio("Death",10,$gDeathH,150)
GUICtrlSetFont(-1, 10,700)
GUICtrlCreateLabel("Date",25,$gDeathH+28)
$gDeathDate = GUICtrlCreateInput("",53,$gDeathH+25,65)
GUICtrlCreateLabel("Name",170,$gDeathH+28)
$gDeathName = GUICtrlCreateInput("",205,$gDeathH+25,65)


; Here is the Add button
$gAdd = GUICtrlCreateButton("Add",($guiW/2)-35,330,70)

; here is edited box
$gEdit = GUICtrlCreateEdit("",($guiW/2)-300,360,600,100)

;here is Draw button
$gDraw = GUICtrlCreateButton("Draw",($guiW/2)-35,480,70,50)



GUISetState()
while 1
	$msg = GUIGetMsg()

	Switch $msg
		Case $gAdd
			_add()
		Case $GUI_EVENT_CLOSE
			Exit
        Case $gDraw
           _draw()
	EndSwitch
	sleep(30)
	_update()
WEnd
    GUISetState(@SW_HIDE)

; this func to make that unchecked table not writeable
Func _update()
	If GUICtrlRead($gBirth) = $GUI_UNCHECKED  And GUICtrlGetState($gBirthDate) = 80 Then
		GUICtrlSetState($gBirthDate, $GUI_DISABLE)
		GUICtrlSetState($gBirthName, $GUI_DISABLE)
		GUICtrlSetState($gBirthFather, $GUI_DISABLE)
		GUICtrlSetState($gBirthGender, $GUI_DISABLE)
		GUICtrlSetState($gBirthMother, $GUI_DISABLE)
	ElseIf GUICtrlRead($gBirth) = $GUI_CHECKED  And GUICtrlGetState($gBirthDate) <> 80 Then
		GUICtrlSetState($gBirthDate, $GUI_ENABLE)
		GUICtrlSetState($gBirthName, $GUI_ENABLE)
		GUICtrlSetState($gBirthFather, $GUI_ENABLE)
		GUICtrlSetState($gBirthGender, $GUI_ENABLE)
		GUICtrlSetState($gBirthMother, $GUI_ENABLE)
	EndIf
	If GUICtrlRead($gMarriage) = $GUI_UNCHECKED  And GUICtrlGetState($gMarriageDate) = 80 Then
		GUICtrlSetState($gMarriageDate, $GUI_DISABLE)
		GUICtrlSetState($gMarriageName, $GUI_DISABLE)
		GUICtrlSetState($gMarriagePartner, $GUI_DISABLE)
		GUICtrlSetState($gMarriageBirthday, $GUI_DISABLE)
	ElseIf GUICtrlRead($gMarriage) = $GUI_CHECKED  And GUICtrlGetState($gMarriageDate) <> 80 Then
		GUICtrlSetState($gMarriageDate, $GUI_ENABLE)
		GUICtrlSetState($gMarriageName, $GUI_ENABLE)
		GUICtrlSetState($gMarriagePartner, $GUI_ENABLE)
		GUICtrlSetState($gMarriageBirthday, $GUI_ENABLE)
	EndIf
	If GUICtrlRead($gDivorce) = $GUI_UNCHECKED  And GUICtrlGetState($gDivorceDate) = 80 Then
		GUICtrlSetState($gDivorceDate, $GUI_DISABLE)
		GUICtrlSetState($gDivorceName, $GUI_DISABLE)
		GUICtrlSetState($gDivorcePartner, $GUI_DISABLE)
	ElseIf GUICtrlRead($gDivorce) = $GUI_CHECKED  And GUICtrlGetState($gDivorceDate) <> 80 Then
		GUICtrlSetState($gDivorceDate, $GUI_ENABLE)
		GUICtrlSetState($gDivorceName, $GUI_ENABLE)
		GUICtrlSetState($gDivorcePartner, $GUI_ENABLE)
	EndIf
	If GUICtrlRead($gDeath) = $GUI_UNCHECKED  And GUICtrlGetState($gDeathDate) = 80 Then
		GUICtrlSetState($gDeathDate, $GUI_DISABLE)
		GUICtrlSetState($gDeathName, $GUI_DISABLE)
	ElseIf GUICtrlRead($gDeath) = $GUI_CHECKED  And GUICtrlGetState($gDeathDate) <> 80 Then
		GUICtrlSetState($gDeathDate, $GUI_ENABLE)
		GUICtrlSetState($gDeathName, $GUI_ENABLE)
	EndIf
EndFunc


Func _add()
	$results = GUICtrlRead($gEdit)
	If $results <> "" Then $results &= @CRLF

	; birth add it in box
	If GUICtrlRead($gBirth) = $GUI_CHECKED Then
		$results &= GUICtrlRead($gBirthDate) & ",1," & GUICtrlRead($gBirthName) & "," & GUICtrlRead($gBirthGender) & ","
		If GUICtrlRead($gBirthFather) = "" Then
			$results &= "0,"
		Else
			$results &= GUICtrlRead($gBirthFather)&","
		EndIf
		If GUICtrlRead($gBirthMother) = "" Then
			$results &= "0"
		Else
			$results &= GUICtrlRead($gBirthMother)
		EndIf

	; marriage add it in box
	ElseIf GUICtrlRead($gMarriage) = $GUI_CHECKED Then
		$results &= GUICtrlRead($gMarriageDate) & ",2," & GUICtrlRead($gMarriageName) & "," & GUICtrlRead($gMarriagePartner) & ","
		If GUICtrlRead($gMarriageBirthday) = "" Then
			$results &= "0,"
		Else
			$results &= GUICtrlRead($gMarriageBirthday)
		EndIf

	; divorce add it in box
	ElseIf GUICtrlRead($gDivorce) = $GUI_CHECKED Then
		$results &= GUICtrlRead($gDivorceDate) & ",3," & GUICtrlRead($gDivorceName) & "," & GUICtrlRead($gDivorcePartner)

	; death add it in box
	ElseIf GUICtrlRead($gDeath) = $GUI_CHECKED Then
		$results &= GUICtrlRead($gDeathDate) & ",4," & GUICtrlRead($gDeathName)
	EndIf

	GUICtrlSetData($gEdit,$results)

EndFunc


Func _draw()
	$results = GUICtrlRead($gEdit)
	$hfile = FileOpen("events",2)
	FileWrite($hfile, $results)
	Fileclose($hfile)

	ShellExecute("FTVisualizer.exe","events")

EndFunc
