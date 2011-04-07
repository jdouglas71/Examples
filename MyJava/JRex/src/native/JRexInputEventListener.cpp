/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * Contributor(s):
 *   C.N Medappa <jrex_moz@yahoo.com><>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#include "JRexWindow.h"
#include "JRex_JNI_Event.h"
using namespace JRex_JNI_Event;

//see MouseEvent java class
#define NOBUTTON	0
#define BUTTON1 	1
#define BUTTON2 	2
#define BUTTON3 	3

NS_IMETHODIMP JRexWindow::HandleEvent(nsIDOMEvent* aDOMEvent){
  	return NS_OK;
}

NS_IMETHODIMP JRexWindow::KeyDown(nsIDOMEvent* aDOMEvent){
	return fireKeyEvent(aDOMEvent,KEY_PRESSED);
}

NS_IMETHODIMP JRexWindow::KeyUp(nsIDOMEvent* aDOMEvent){
	return fireKeyEvent(aDOMEvent,KEY_RELEASED);
}

//x11 KeyPress macro causes compilation problem with nsIDOMKeyListener function KeyPress.
#define MyKeyPress KeyPress
#undef KeyPress
NS_IMETHODIMP JRexWindow::KeyPress(nsIDOMEvent* aDOMEvent){
	return fireKeyEvent(aDOMEvent,KEY_TYPED);
}
#define KeyPress MyKeyPress
#undef MyKeyPress

NS_IMETHODIMP JRexWindow::MouseDown(nsIDOMEvent* aDOMEvent){
	return fireMouseEvent(aDOMEvent,MOUSE_PRESSED,0);
}

NS_IMETHODIMP JRexWindow::MouseUp(nsIDOMEvent* aDOMEvent){
	return fireMouseEvent(aDOMEvent,MOUSE_RELEASED,0);
}

NS_IMETHODIMP JRexWindow::MouseClick(nsIDOMEvent* aDOMEvent){
  return fireMouseEvent(aDOMEvent,MOUSE_CLICKED,1);
}

NS_IMETHODIMP JRexWindow::MouseDblClick(nsIDOMEvent* aDOMEvent){
	return fireMouseEvent(aDOMEvent,MOUSE_CLICKED,2);
}

NS_IMETHODIMP JRexWindow::MouseOver(nsIDOMEvent* aDOMEvent){
	return fireMouseEvent(aDOMEvent,MOUSE_ENTERED,0);
}

NS_IMETHODIMP JRexWindow::MouseOut(nsIDOMEvent* aDOMEvent){
	return fireMouseEvent(aDOMEvent,MOUSE_EXITED,0);
}

NS_IMETHODIMP JRexWindow::MouseMove(nsIDOMEvent* aDOMEvent){
	return fireMouseEvent(aDOMEvent,MOUSE_MOVED_OVER,0);
}

NS_IMETHODIMP JRexWindow::DragMove(nsIDOMEvent* aDOMEvent){
	return fireMouseEvent(aDOMEvent,MOUSE_DRAGGED,0);
}



static inline PRUint32 getJKeyCode(PRUint32 keyCode){
	switch(keyCode){
		case 188U:return 0x2C;//DOM_VK_COMMA
		case 190U:return 0x2E;//DOM_VK_PERIOD
		case 191U:return 0x2F;//DOM_VK_SLASH

		case 219U:return 0x5B;//DOM_VK_OPEN_BRACKET
		case 220U:return 0x5C;//DOM_VK_BACK_SLASH
		case 221U:return 0x5D;//DOM_VK_CLOSE_BRACKET
		case 224U:return 0x9D;//DOM_VK_META

		case 124U:return 0xF000;//DOM_VK_F13
		case 125U:return 0xF001;//DOM_VK_F14
		case 126U:return 0xF002;//DOM_VK_F15
		case 127U:return 0xF003;//DOM_VK_F16
		case 128U:return 0xF004;//DOM_VK_F17
		case 129U:return 0xF005;//DOM_VK_F18
		case 130U:return 0xF006;//DOM_VK_F19
		case 131U:return 0xF007;//DOM_VK_F20
		case 132U:return 0xF008;//DOM_VK_F21
		case 133U:return 0xF009;//DOM_VK_F22
		case 134U:return 0xF00A;//DOM_VK_F23
		case 135U:return 0xF00B;//DOM_VK_F24

		case 44U:return 0x9A;//DOM_VK_PRINTSCREEN
		case 45U:return 0x9B;//DOM_VK_INSERT
		case 46U:return 0x7F;//DOM_VK_DELETE

		case 13U:
		case 14U:return '\n';//DOM_VK_ENTER////DOM_VK_RETURN
		case 6U:return 0x9C;//DOM_VK_HELP
		case 8U:return '\b';//DOM_VK_BACK_SPACE
		case 9U:return '\t';//DOM_VK_TAB
		default:
			return keyCode;
	}
}

nsresult JRexWindow::fireKeyEvent(nsIDOMEvent* aDOMEvent, PRUint16 eventID){

	nsresult rv;
	nsCOMPtr <nsIDOMKeyEvent> keyEvent= do_QueryInterface(aDOMEvent,&rv);
	if(NS_FAILED(rv))return NS_OK;

	PRUint32 charCode=0;
	keyEvent->GetCharCode(&charCode);

	PRUint32 keyCode=0;
	keyEvent->GetKeyCode(&keyCode);
	PRUint32 jkeyCode=getJKeyCode(keyCode);

	PRUint32 modifiers=0;
	PRBool isModifier=PR_FALSE;
	keyEvent->GetShiftKey(&isModifier);
	if(isModifier)modifiers|=SHIFT_MASK;
	keyEvent->GetCtrlKey(&isModifier);
	if(isModifier)modifiers|=CTRL_MASK;
	keyEvent->GetMetaKey(&isModifier);
	if(isModifier)modifiers|=META_MASK;
	keyEvent->GetAltKey(&isModifier);
	if(isModifier)modifiers|=ALT_MASK;

	JREX_LOGLN("fireKeyEvent()--> **** modifiers<"<<modifiers<<">,keyCode<"<<keyCode<<">, charCode<"<<charCode<<">****")
	rv= postJavaKeyEvent((PRUint32)this,eventID, modifiers,jkeyCode, charCode);
	JREX_LOGLN("fireKeyEvent()--> **** postJavaKeyEvent rv<"<<rv<<"> ****")
	return NS_OK;
}

nsresult JRexWindow::fireMouseEvent(nsIDOMEvent* aDOMEvent, PRUint16 eventID, PRUint16 clickCount ){

	nsresult rv;
	nsCOMPtr <nsIDOMMouseEvent> mouseEvent= do_QueryInterface(aDOMEvent,&rv);
	if(NS_FAILED(rv))return NS_OK;
	PRInt32 cX=0;
	mouseEvent->GetClientX(&cX);

	PRInt32 cY=0;
	mouseEvent->GetClientY(&cY);

	PRUint16 button=10;
	mouseEvent->GetButton(&button);
	switch(button){
		case 0:
			button=BUTTON1;
			break;
		case 1:
			button=BUTTON2;
			break;
		case 2:
			button=BUTTON3;
			break;
		default:
			button=NOBUTTON;
	}

	PRUint32 modifiers=0;
	PRBool isModifier=PR_FALSE;
	mouseEvent->GetShiftKey(&isModifier);
	if(isModifier)modifiers|=SHIFT_MASK;
	mouseEvent->GetCtrlKey(&isModifier);
	if(isModifier)modifiers|=CTRL_MASK;
	mouseEvent->GetMetaKey(&isModifier);
	if(isModifier)modifiers|=META_MASK;
	mouseEvent->GetAltKey(&isModifier);
	if(isModifier)modifiers|=ALT_MASK;

	JREX_LOGLN("fireMouseEvent()--> **** modifiers<"<<modifiers<<">,cX<"<<cX<<">, cY<"<<cY<<">, clickCount<"<<clickCount<<">,button<"<<button<<"> ****")
	rv=postJavaMouseEvent((PRUint32)this,eventID, modifiers,cX, cY, clickCount,button);
	JREX_LOGLN("fireMouseEvent()--> **** postJavaMouseEvent rv<"<<rv<<"> ****")
	return NS_OK;
}

