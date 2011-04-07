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

/**
* A class representing JRex Event.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public class JRexEvent{

   /**
    * The type of the event. A Event will be sent to handler according to its type.
    */
	private int 	type;

	/**
	* An arbitrary data of the event. The value of this field
	* depends on the type of event.
	* <code>data</code> has been replaced by event specific property.
	*/
	private Object	data;

	/**
	* The timestamp of when this event occurred.
	*/
	private long 	when;

	/**
	* The Object whose notifyAll() needs to be called after event is processed.
	*/
	private Object	notifier;

	/**
	 * Constructs an JRexEvent object with the specified event data ,
	 * type,when.
	 * @param type 		the event type
	 * @param eventData the event related data.
	 * @param when the 	time the event occurred
	 * @param notifier	the Object whose <code>notifyAll</code>
							method will be called after event is process.
	 */
	protected JRexEvent(int type, Object eventData, long when, Object notifier) {
		this.type		= type;
		this.data		= eventData;
		this.when		= when;
		this.notifier	= notifier;
	}

	/**
	* Factory method to create a jrex event.
	*/
	public static JRexEvent createEvent(int type, Object eventData, long when){
		return new JRexEvent(type, eventData, when,null);
	}

	/**
	* Factory method to create a synchronized jrex event.
	*/
	public static JRexEvent createSyncEvent(int type, Object eventData, long when, Object notifier){
		return new JRexEvent(type, eventData, when,notifier);
	}

	/**
	* Returns the type of the event.
	*/
	public int getType(){
		return type;
	}

	/**
	* Returns the data assoicated with the event.
	*/
	public Object getData(){
		return data;
	}

	/**
	* Returns the timestamp of when this event occurred.
	*/
	public long getWhen(){
		return when;
	}

	/**
	* Returns the notifier associated with the event.
	*/
	public Object getNotifier(){
		return notifier;
	}


	public String toString(){
		StringBuffer buf=new StringBuffer(512);
		buf.append("\ntype <").append(type).append(">\n")
		.append("data <").append(data).append(">\n")
		.append("when <").append(when).append(">\n")
		.append("notifier <").append(notifier).append(">\n");
		return buf.toString();
	}
}