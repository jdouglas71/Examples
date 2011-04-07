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

package org.mozilla.jrex.event;

import java.util.Hashtable;
import org.mozilla.jrex.ui.JRexCanvas;
import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.JRexFactory;
import org.mozilla.jrex.event.window.WindowEventHandler;
import org.mozilla.jrex.event.history.HistoryEventHandler;
import org.mozilla.jrex.event.progress.ProgressEventHandler;
import org.mozilla.jrex.event.context.ContextMenuEventHandler;
import org.mozilla.jrex.event.tooltip.TooltipEventHandler;
import org.mozilla.jrex.event.observer.ObserverEventHandler;
import org.mozilla.jrex.event.uricontent.URIContentEventHandler;
import org.mozilla.jrex.window.JRexWindowManager;

/**
* The JRex EventManager class. This class maintains a event queue for which jrex event's can be posted.
* All the native events that should be propagated to java are posted to the EventManager via postEvent.
* The Event Manager identifies the event handler according to the event type and dispatches the event.
* It supports synchronus(The event posting thread will block till event is executed)  and asynchronus
* mode event posting. All mouse and key event posted by native engine are not handled by JRex EventManager
* instead the events are pumped into java event queue.
* Note:- If you are posting event manually the notifier object should be of type JRexEventLock
*
* When initialized this class pre-loads all the mozilla event related classes. Classes are
* loaded manually to register method & field signatures for JNI, Helps in speeding up jni
* calls(ie,native to java call). The list of class to be loaded is listed in 'jrex.cls' file.
* If any new mozilla event is added the class should be listed in jrex.cls' file.
*
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see	JRexEventType
*/
public final class JRexEventManager implements Runnable{

	private static final String className 			= JRexEventManager.class.getName();

	static{
		try{
			initIDs();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new RuntimeException(ex);
		}
	}

	/**
	* The varaible to indicate status of EventManager intialization.
	*/
	private static boolean inited= false;

	/**
	* The singleton instance of the JRexEventManager.
	*/
	private static final JRexEventManager instance	= new JRexEventManager();

	/**
	* Loads all the mozilla event related classes. Classes are loaded manually to register
	* method & field signatures for JNI, Helps in speeding up jni calls(ie,native to java call).
	* The list of class to be loaded is listed in 'jrex.cls' file.
	* If any new mozilla event is added the class should be listed in jrex.cls' file.
	*/
	private void loadClasses()throws JRexException{
		try{
			java.io.InputStream in=JRexEventManager.class.getClassLoader().getResourceAsStream("jrex.cls");
			if(in!=null){
				java.io.BufferedReader bin= new java.io.BufferedReader( new java.io.InputStreamReader(in));
				if(JRexL.on)
					JRexL.log(className,"loadClasses()--> **** Loading classes list... ****");

				String temp=null;
				while((temp=bin.readLine())!=null){
					temp=temp.trim();
					if(JRexL.on)
						JRexL.log(className,"loadClasses()--> **** Loading class <"+temp+">****");
					if(temp=="" || temp.startsWith("#"))continue;
					Class.forName(temp);
					if(JRexL.on)JRexL.log(className,"loadClasses()--> **** Loading class <"+temp+"> done!!!****");
				}
				bin.close();
			}
		}catch(Exception ex){
			throw new JRexException("loadClasses FAILED <"+ex.getMessage()+">");
		}
	}

	/**
	* The JRex EventManagers event dispatch thread.
	*/
	private Thread			dispatchThread;

	/**
	* The JRex EventManagers event queue.
	*/
	private JRexEventQueue	eventQueue;

	/**
	* The JRex EventManagers return value table for synchronous events.
	*/
	private Hashtable		retValTable;

	/**
	* The Event Handler's looked up.
	*/
	private WindowEventHandler wEvtHandler=((WindowEventHandler)JRexFactory.getInstance().getImplInstance(JRexFactory.WINDOW_EVENT_HANDLER));
	private HistoryEventHandler hEvtHandler=((HistoryEventHandler)JRexFactory.getInstance().getImplInstance(JRexFactory.HISTORY_EVENT_HANDLER));
	private ProgressEventHandler pEvtHandler=((ProgressEventHandler)JRexFactory.getInstance().getImplInstance(JRexFactory.PROGRESS_EVENT_HANDLER));
	private ContextMenuEventHandler cEvtHandler=((ContextMenuEventHandler)JRexFactory.getInstance().getImplInstance(JRexFactory.CONTEXTMENU_EVENT_HANDLER));
	private TooltipEventHandler ttEvtHandler=((TooltipEventHandler)JRexFactory.getInstance().getImplInstance(JRexFactory.TOOLTIP_EVENT_HANDLER));
	private ObserverEventHandler obEvtHandler=((ObserverEventHandler)JRexFactory.getInstance().getImplInstance(JRexFactory.OBSERVER_EVENT_HANDLER));
	private URIContentEventHandler ucEvtHandler=((URIContentEventHandler)JRexFactory.getInstance().getImplInstance(JRexFactory.URICONTENT_EVENT_HANDLER));
	private JRexWindowManager windowManager=((JRexWindowManager)JRexFactory.getInstance().getImplInstance(JRexFactory.WINDOW_MANAGER));

	private JRexEventManager(){
		//changes for fixing BUG-ID<6426>, contributed by damon@javasteam.com
		try{
			loadClasses();
			inited=true;
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new RuntimeException(ex);
		}
	}

	/**
	* Method to get instance of JRex EventManager.
	*/
	public static JRexEventManager getInstance(){
		return inited?instance:null;
	}

	/**
	* Method to start EventManager, results in creation of event qeue and starts event dispatch thread.
	*/
	public synchronized void startEventManager() {
		if(eventQueue!=null){
			if(JRexL.on)JRexL.log(className,"**** startEventManager()--> EventManager already started ****");
			return;
		}
		if(JRexL.on)JRexL.log(className,"**** startEventManager()--> Starting EventManager ****");
		eventQueue=new JRexEventQueue();
		retValTable=new Hashtable();
		initDispatchThread();
		if(JRexL.on)JRexL.log(className,"**** startEventManager()--> Starting EventManager Done ****");
	}

	/**
	* Inits event dispatch thread.
	*/
	private void initDispatchThread() {
		if (dispatchThread == null){
			if(JRexL.on)JRexL.log(className,"**** initDispatchThread()-->creating dispatchThread ****");
			dispatchThread=new Thread(this);
			dispatchThread.setPriority(Thread.NORM_PRIORITY + 1);
			dispatchThread.setDaemon(false);
			dispatchThread.start();
			if(JRexL.on)JRexL.log(className,"**** initDispatchThread()-->dispatchThread started****");
		}
	}

	/**
	* Posts the JRexEvent to the internal Queue, no coalescing is done. The call will return
	* without waiting for the event to processed.
	* @param event an instance of <code>org.mozilla.jrex.event.JRexEvent</code>
	*/
	public void postEvent(JRexEvent event){
		if(dispatchThread==null){
			if(JRexL.on)JRexL.log(className,"**** postEvent()--> POST-EVENT DISABLED, NOT POSTING event<"+event+"> ****");
			return;
		}
		if(JRexL.on)JRexL.log(className,"**** postEvent()--> posting event<"+event+"> ****");
		eventQueue.enqueue(event);
	}

	/**
	* Posts the JRexEvent to the internal Queue. The call will wait for the event to processed.
	* @param event an instance of <code>org.mozilla.jrex.event.JRexEvent</code>
	*/
	public Object postSyncEvent(JRexEvent event){
		if(dispatchThread==null){
			if(JRexL.on)JRexL.log(className,"**** postSyncEvent()--> POST-EVENT DISABLED, NOT POSTING event<"+event+"> ****");
			return null;
		}
		if(Thread.currentThread()==dispatchThread){
			if(JRexL.on)JRexL.log(className,"**** postSyncEvent()-->Cannot post SyncEvent<"+event+"> from dispatchThread ****");
			return null;
		}
		if(JRexL.on)JRexL.log(className,"**** postSyncEvent()--> posting event<"+event+"> ****");

        JRexEventLock lock = (JRexEventLock)event.getNotifier();
        int eventType=event.getType();
        //we use lock.notified so that we can avoid blocking XPCOM event queue.
		eventQueue.enqueue(event);
		while(!lock.notified)
			try{
				if(eventType!=JRexEventType.SHUTDOWN_EVENT)//since SHUTDOWN_EVENT is from java thread.
					processNativeEvents();//process events from XPCOM event queue.
			}catch(Exception ex){
				if(JRexL.on)JRexL.log(className,"**** postSyncEvent()-->JRexEvent Lock Exception for event<"+event+"> ****");
				JRexL.printStackTrace(ex);
			}
        return retValTable.remove(event);
	}

	/**
	* Posts the JRexEvent to the internal Queue, used from native side.
	*/
	private static void postEvent(int type, Object eventData){
		if(JRexL.on)JRexL.log(className,"**** postEvent()-->type<"+type+">  eventData<"+eventData+"> ****");
		instance.postEvent(JRexEvent.createEvent(type,eventData,System.currentTimeMillis()));
	}

	/**
	* Posts the sync JRexEvent to the internal Queue, used from native side.
	*/
	private static Object postSyncEvent(int type, Object eventData){
		if(JRexL.on)JRexL.log(className,"**** postSyncEvent()-->type<"+type+">  eventData<"+eventData+"> ****");
        return instance.postSyncEvent(JRexEvent.createSyncEvent(type,eventData,System.currentTimeMillis(),new JRexEventLock()));
	}

	/**
	* Posts key event to java system event queue, used from native side.
	*/
	private static void postKeyEvent(int target, int id, int modifiers,int keyCode, char keyChar){
		if(JRexL.on)JRexL.log(className,"**** postKeyEvent()-->id<"+id+"> modifiers<"+modifiers+"> keyCode<"+keyCode+"> keyChar<"+keyChar+">****");
		JRexCanvas browser=instance.windowManager.getBrowser(target);
		assert browser!=null;
		if(browser==null)return;
		java.awt.Toolkit.getDefaultToolkit().getSystemEventQueue().postEvent(
									new java.awt.event.KeyEvent(browser,id,0,modifiers,keyCode,keyChar));
	}

	/**
	* Posts mouse event to java system event queue, used from native side.
	*/
	private static void postMouseEvent(int target, int id, int modifiers,int x, int y, int clickCount,int button){
		if(JRexL.on)JRexL.log(className,"**** postMouseEvent()-->id<"+id+"> modifiers<"+modifiers+"> x<"+x+"> y<"+y+"> clickCount<"+clickCount+">  button<"+button+">****");
		JRexCanvas browser=instance.windowManager.getBrowser(target);
		assert browser!=null;
		if(browser==null)return;
		java.awt.Toolkit.getDefaultToolkit().getSystemEventQueue().postEvent(
				new java.awt.event.MouseEvent(browser,id,0,modifiers,x, y, clickCount,false,button));
	}

	/**
	* Method to stop EventManager.
	*/
	public synchronized void stopEventManager() {
		if(JRexL.on)JRexL.log(className,"**** stopEventManager()-->I AM HERE ****");
		postSyncEvent(JRexEventType.SHUTDOWN_EVENT,null);
	}


	/**
	* Returns event handler for given event type.
	*/
	private JRexEventHandler getHandler(int eventType){
		switch(eventType){
			case JRexEventType.WINDOW_EVENT:
				return wEvtHandler;
			case JRexEventType.HISTORY_EVENT:
				return hEvtHandler;
			case JRexEventType.PROGRESS_EVENT:
				return pEvtHandler;
			case JRexEventType.CONTEXT_MENU_EVENT:
				return cEvtHandler;
			case JRexEventType.TOOL_TIP_EVENT:
				return ttEvtHandler;
			case JRexEventType.OBSERVER_EVENT:
				return obEvtHandler;
			case JRexEventType.URICONTENT_EVENT:
				return ucEvtHandler;
			default:
				if(JRexL.on)JRexL.log(className,"**** UNKNOWN eventType<"+eventType+"> ****");

		};
		return null;
	}

	/**
	* The event dispatch threads run method.
	*/
	public void run(){
		if(JRexL.on)JRexL.log(className,"**** run()-->I AM HERE ****");

		JRexEvent event;
		while(true){
			try{
				event = eventQueue.dequeue();
            }catch(InterruptedException ex){
				if(JRexL.on)JRexL.log(className,"**** run()--> Thread Interrupted in dequeue ***");
				dispatchThread=null;
				return;
			}
			if(JRexL.on)JRexL.log(className,"**** run()--> Processing event<"+event+"> ***");

			int type=event.getType();
			JRexEventLock notifier=(JRexEventLock)event.getNotifier();

			if(type==JRexEventType.SHUTDOWN_EVENT){
				if(JRexL.on)JRexL.log(className,"**** run()--> SHUTDOWN_EVENT recieved exiting ***");
				dispatchThread=null;
				if(notifier!=null){
					if(JRexL.on)JRexL.log(className,"**** run()--> SHUTDOWN_EVENT Notifying  notifier<"+notifier+"> ***");
					notifier.notified=true;
				}
				return;
			}
			JRexEventHandler handler=getHandler(type);
			if(JRexL.on)JRexL.log(className,"**** run()--> Using Eventhandler<"+handler+"> ***");
			try{
				Object rv=handler.handleEvent(event);
				if(JRexL.on)JRexL.log(className,"**** run()--> handleEvent  rv<"+rv+"> ***");
				if(rv!=null)retValTable.put(event,rv);
			}catch(Throwable ex){
				if(JRexL.on)JRexL.log(className,"**** run()--> handleEvent failed ***");
				JRexL.printStackTrace(ex);
			}finally{
				if(notifier!=null){
					if(JRexL.on)JRexL.log(className,"**** run()--> Notifying  notifier<"+notifier+"> ***");
					notifier.notified=true;
				}
			}
		}
	}

	private static native void initIDs()throws JRexException;
	private static native void processNativeEvents()throws JRexException;

	public static class JRexEventLock{
		volatile boolean notified=false;
	}
}

/**
* The event queue class of JRex event manager.
*/
class JRexEventQueue {
	int length=0;
	EventQueueItem head = null;
	EventQueueItem tail = null;

	JRexEventQueue(){}

	public synchronized void enqueue(JRexEvent event) {
		EventQueueItem newEvent = new EventQueueItem(event);
		if (head == null) {
			head = tail= newEvent;
			length = 1;
		} else {
			tail.next = newEvent;
			tail = newEvent;
			length++;
		}
		notify();
	}

	public synchronized JRexEvent dequeue()throws InterruptedException{
		while (head == null)
			wait();
		EventQueueItem temp=head;
		head=temp.next;
		length--;
		return temp.getEvent();
	}

	public synchronized boolean noEvents() {
		return head == null;
	}

	public int getLength() {
		return length;
	}

	private static class EventQueueItem {
		EventQueueItem next;
		JRexEvent event;

		EventQueueItem(JRexEvent event) {
			this.event = event;
		}

		JRexEvent getEvent(){
			return event;
		}
	}
}



