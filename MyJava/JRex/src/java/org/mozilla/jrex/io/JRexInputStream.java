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

package org.mozilla.jrex.io;

import java.io.*;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* JRexInputStream is java wrapper arround native nsIInputStream.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/

public class JRexInputStream extends InputStream{
	private static final String className	= JRexInputStream.class.getName();

	static{
		try{
			initIDs();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new RuntimeException(ex);
		}
	}
	/**
	* The varaible representing handle to the native nsIInputStream instance.
	*/
    private int streamPeer=0;

    /**
     * Creates a <code>JRexInputStream</code> given peer stream handle.
     * @param      streamPeer handle to the native nsIInputStream instance
     * @exception  JRexException if <code>streamPeer</code> is invalid.
     */
    public JRexInputStream(int streamPeer)throws JRexException {
		if(JRexL.on)JRexL.log(className,"**** JRexInputStream() -->streamPeer<"+streamPeer+">****");
		if(streamPeer<1)throw new JRexException("Invalid native stream handle.");
		this.streamPeer = streamPeer;
    }

	/**
	* Returns the number of bytes that can be read from this native inputstream without blocking.
	* @return     the number of bytes that can be read from this native inputstream without blocking.
	* @exception  IOException  if an I/O error or JRexException occurs.
	*/
    public int available() throws IOException{
		if(JRexL.on)JRexL.log(className,"**** available() -->I AM HERE****");
		try{
			return Available();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new IOException("JRexException <"+ex.getMessage()+"> Occured");
		}
	}


    /**
     * Reads a byte of data from this input stream. This method blocks if no input is yet available.
     * @return     the next byte of data, or <code>-1</code> if the end of the stream is reached.
     * @exception  IOException  if an I/O error or JRexException occurs.
     */
    public int read() throws IOException {
		if(JRexL.on)JRexL.log(className,"**** read() -->I AM HERE****");
		try{
			return Read();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new IOException("JRexException <"+ex.getMessage()+"> Occured");
		}
    }

    /**
     * Reads up to <code>buff.length</code> bytes of data from this input
     * stream into an array of bytes. This method blocks until some input
     * is available.
     *
     * @param      buff   the buffer into which the data is read.
     * @return     the total number of bytes read into the buffer, or
     *             <code>-1</code> if there is no more data because the end of
     *             the stream has been reached.
     * @exception  IOException  if an I/O error or JRexException occurs.
     */

    public int read(byte buff[], int off, int len) throws IOException {
		if(JRexL.on)JRexL.log(className,"**** read() --> buff<"+buff+"> off<"+off+"> len<"+len+"> ****");
		if (buff == null)
			throw new NullPointerException();
        else
        if ((off < 0) || (len < 0) || (off > buff.length)  ||((off + len) > buff.length))
            throw new IndexOutOfBoundsException();

        try{
			return Read(buff,off,len);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new IOException("JRexException <"+ex.getMessage()+"> Occured");
		}
    }

	/**
	* Reads up to <code>b.length</code> bytes of data from this input
	* stream into an array of bytes. This method blocks until some input
	* is available.
	*
	* @param      buff   the buffer into which the data is read.
	* @return     the total number of bytes read into the buffer, or
	*             <code>-1</code> if there is no more data because the end of
	*             the stream has been reached.
	* @exception  IOException  if an I/O error or JRexException occurs.
	*/
    public int read(byte buff[]) throws IOException {
		if (buff == null)
			throw new NullPointerException();
		return read(buff, 0, buff.length);
    }

	/**
	* Mark is not supported, hence this function does nothing.
	*/
    public synchronized void mark(int readlimit) {
		if(JRexL.on)JRexL.log(className,"**** mark() --> readlimit<"+readlimit+"> Mark Not Supported!!! ****");
    }

	/**
	* Since mark is not supported, this throws IOException.
	*/
    public synchronized void reset() throws IOException {
		throw new IOException("Mark Not Supported!!!");
    }

	/**
	* skip is not supported, hence return <code>-1</code>.
	*/
    public long skip(long n) throws IOException {
		if(JRexL.on)JRexL.log(className,"**** skip() --> n<"+n+"> skip Not Supported!!! ****");
		return -1;
    }

	/**
	* Mark is not supported.
	*/
    public boolean markSupported() {
		return false;
    }

	/**
	* Closes this input stream and releases any system resources
	* associated with the stream.
	* @exception  IOException  if an I/O error or JRexException occurs.
	*/
	public void close() throws IOException {
		if(JRexL.on)JRexL.log(className,"**** close() --> streamPeer<"+streamPeer+">****");
		if(streamPeer>0)
		try{
			Close();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new IOException("JRexException <"+ex.getMessage()+"> Occured");
		}finally{
			streamPeer=0;
		}
	}

	/**
	* Ensures that the <code>close</code> method of this input stream is
	* called when there are no more references to it.
	*
	* @see        #close()
	*/
    protected void finalize() throws IOException  {
		if(JRexL.on)JRexL.log(className,"**** finalize() --> streamPeer<"+streamPeer+">****");
		if(streamPeer>0)
			try{
				close();
			}catch(IOException ioex){
				JRexL.printStackTrace(ioex);
			}
    }

    private static native void initIDs()throws JRexException;
    private native int Available()throws JRexException;
    private native int Read() throws JRexException;
    private native int Read(byte b[], int off, int len) throws JRexException;
    private native void Close()throws JRexException;

}
