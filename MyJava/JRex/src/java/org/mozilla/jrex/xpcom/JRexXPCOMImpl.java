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

package org.mozilla.jrex.xpcom;

import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
 * The class implementing JRexXPCOM interface. The instance of class
 * is are constructed using the <code>getInstance</code> method.
 * @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
 * @version 1.0
 * @see org.mozilla.jrex.xpcom.JRexXPCOM
 */

public class JRexXPCOMImpl implements JRexXPCOM{

	private static final String className		= JRexXPCOMImpl.class.getName();

	/**
	* The default profile name that will be used if <b>jrex.profile.name</b>
	* property is not specified.
	*/
	private static final String DEFAULT_PROFILE	= ".JRex";

	/**
	* The instance of thread on which xpcom engine runs.
	*/
	private Thread			xpcomThread			= null;

	/**
	* The variable to hold XPCOM startup return value.
	*/
	private int 			xpcomInitRV			= 0;

	/**
	* The static instance for singleton behavior.
	*/
	private static final JRexXPCOM xpcomInst	= new JRexXPCOMImpl();

	private JRexXPCOMImpl(){}

	/**
	* A factory method to get the instance of JRexXPCOM Implementation.
	* @return instance of JRexXPCOM.
	*/
	public static JRexXPCOM getInstance()throws JRexException{
		return xpcomInst;
	}

	/**
	* A function to load native libraries which are listed in <b>jrex.lib</b>.
	* This function also loads the <b>jawt</b> and <b>jrex</b> libraries.
	*/
	private static final void loadLibraries(String greDir){
		try{
			java.io.InputStream in=JRexXPCOMImpl.class.getClassLoader().getResourceAsStream("jrex.lib");
			if(in!=null){
				java.io.BufferedReader bin= new java.io.BufferedReader( new java.io.InputStreamReader(in));
				if(JRexL.on)JRexL.log(className,"loadLibraries()--> **** Loading library list... ****");

				String temp=null;
				while((temp=bin.readLine())!=null){
					temp=temp.trim();
					if(JRexL.on)JRexL.log(className,"loadLibraries()--> **** Library to load<"+temp+">****");
					if(temp=="" || temp.startsWith("#"))continue;

					temp=System.mapLibraryName(temp);
					java.io.File tempFile=new java.io.File(greDir,temp);
					if(!tempFile.exists()){
						if(JRexL.on)JRexL.log(className,"loadLibraries()--> **** Library <"+tempFile+"> does not exsist!!!****");
						continue;
					}
					String libPath=tempFile.getCanonicalPath();
					if(JRexL.on)JRexL.log(className,"loadLibraries()--> **** Loading library <"+libPath+">...****");
					try{
						System.load(libPath);
						if(JRexL.on)JRexL.log(className,"loadLibraries()--> **** Loading library <"+libPath+"> done!!!****");
					}catch(UnsatisfiedLinkError error){
						if(JRexL.on)JRexL.log(className,"loadLibraries()--> **** Loading library <"+libPath+"> FAILED!!! reason<"+error.getMessage()+">****");
					}
				}
				bin.close();
			}
		}catch(Exception ex){
			JRexL.printStackTrace(ex);
		}
		//Required while deployed via WebStart
		try{
			System.loadLibrary("jrex");
		}catch(UnsatisfiedLinkError error){}
		System.loadLibrary("jawt");
	}

	/**
	* A function to start mozilla XPCOM engine.
	* The function uses following system properties.
	* <ul>
	* <li><b>jrex.gre.path</b> Path to the mozilla bin or GRE directory.</li>
	* <li><b>jrex.profile.name</b> The name of profile to load.</li>
	* <li><b>jrex.profile.path</b> The path where the profile should be created if it does not exsist.
	* 	If not specified defaults to java <i>user.home</i> system property.</li>
	* <li><b>jrex.force.noprofile</b> Setting this property to true will result in not using any profile.
	*  This overrides <code>jrex.profile.name</code> and <code>jrex.profile.path</code> property.
	*  Note:- Presently https will not work if this property is set.
	* </ul>
	*/
	public synchronized void startXPCOM()throws JRexException{
		if(xpcomThread!=null){
			if(JRexL.on)JRexL.log(className,"startXPCOM()--> **** XPCOM ALL READY INSTANCIATED BY THREAD <"+xpcomThread+"> ****");
			return;
		}

		final JRexException jrexExp=new JRexException();
		xpcomThread=new Thread(){
			public void run(){
				try{
					String grePath=System.getProperty("jrex.gre.path");
					assert grePath!=null;
					if(grePath==null)throw new Exception("<jrex.gre.path> is set to null!!!");
					java.io.File temp=new java.io.File(grePath);
					if(!temp.exists() || !temp.isDirectory())
						throw new JRexException("startXPCOM()--> **** INVALID GRE-PATH SPECIFIED,GRE-PATH SHOULD BE SET TO VALID DIRECTORY ***");
					try{
						grePath=temp.getCanonicalPath();
					}catch(java.io.IOException ioex){
						if(JRexL.on)JRexL.printStackTrace(ioex);
					}
					if(JRexL.on)JRexL.log(className,"startXPCOM()--> **** USING GRE_PATH <"+grePath+"> ***");
					loadLibraries(grePath);

					String noprofile=System.getProperty("jrex.force.noprofile");
					boolean forceNoProfile=noprofile==null?false:noprofile.trim().equals("true");
					if(JRexL.on)JRexL.log(className,"startXPCOM()--> **** USING forceNoProfile <"+forceNoProfile+"> ***");

					String profileName=System.getProperty("jrex.profile.name");
					if(profileName==null)profileName=DEFAULT_PROFILE;
					if(JRexL.on)JRexL.log(className,"startXPCOM()--> **** USING profileName <"+profileName+"> ***");

					String profilePath=System.getProperty("jrex.profile.path");
					if(profileName!=null && profilePath==null)profilePath=System.getProperty("user.home");
					if(JRexL.on)JRexL.log(className,"startXPCOM()--> **** USING profilePath <"+profilePath+"> ***");

					InitXPCOM(grePath,forceNoProfile?null:profileName,profilePath);
				}catch(Throwable exp){
					jrexExp.initCause(exp);
					notifyXPCOMInited(-1);
					if(JRexL.on)JRexL.log(className,"startXPCOM()--> **** XPCOM INIT FAILED <"+exp.getMessage()+">");
				}
			}
		};
		xpcomThread.setPriority(Thread.NORM_PRIORITY+1);
		xpcomThread.start();
		try{
			wait();
		}catch(InterruptedException ex){
			if(JRexL.on)JRexL.log(className,"startXPCOM()--> **** InterruptedException <"+ex.getMessage()+"> occured while wait");
		}
		if(JRexL.on)JRexL.log(className,"startXPCOM()--> **** xpcomInitRV <"+xpcomInitRV+">");
		if(xpcomInitRV!=1)
			throw jrexExp;
	}

	/**
	* This function will be called from native, indicating the status of XPCOM start up.
	*/
	private void notifyXPCOMInited(int xpcomInitRV){
		if(JRexL.on)JRexL.log(className,"notifyXPCOMInited()--> **** xpcomInitRV<"+xpcomInitRV+">***");
		this.xpcomInitRV=xpcomInitRV;
		synchronized(this){
			notify();
		}
	}

	public void stopXPCOM()throws JRexException{
		if(JRexL.on)JRexL.log(className,"stopXPCOM()--> **** xpcomThread<"+xpcomThread+">***");
		ShutDownXPCOM();
		try{
			xpcomThread.join();
		}catch(InterruptedException ex){
			if(JRexL.on)JRexL.log(className,"stopXPCOM()--> **** InterruptedException <"+ex.getMessage()+"> occured while join");
		}
	}

	private native void InitXPCOM(String grePath, String profileName, String profilePath)throws JRexException;
	private native void ShutDownXPCOM()throws JRexException;
}