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

package org.mozilla.jrex.dom;

import org.w3c.dom.*;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.JRexFactory;
import org.mozilla.jrex.log.JRexL;


/**
* A class implementing org.w3c.dom.DOMImplementation interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.DOMImplementation
*/
public class JRexDOMImplementationImpl implements DOMImplementation {

	private static final String className	= JRexDOMImplementationImpl.class.getName();

	private static JRexDOMImplementationImpl inst;

    private int peerDOMImpl = 0;


    /** Intended to be used by JNI */
    private JRexDOMImplementationImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexDOMImplementationImpl ****");
	}

	public static boolean initialize(){
		if(JRexL.on)JRexL.log(className,"**** initialize isDOMEnabled<"+JRexFactory.getInstance().isDOMEnabled()+"> ****");
		if(!JRexFactory.getInstance().isDOMEnabled())return false;
		try{
			Initialize();
			return true;
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		return false;
	}

	public static void unInitialize(){
		if(JRexL.on)JRexL.log(className,"**** unInitialize isDOMEnabled<"+JRexFactory.getInstance().isDOMEnabled()+"> ****");
		if(!JRexFactory.getInstance().isDOMEnabled())return;
		try{
			UnInitialize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public static synchronized DOMImplementation getInstance(){
		if(JRexL.on)JRexL.log(className,"**** getInstance isDOMEnabled<"+JRexFactory.getInstance().isDOMEnabled()+"> ****");
		if(!JRexFactory.getInstance().isDOMEnabled())return null;
		if(inst==null){
			inst=new JRexDOMImplementationImpl();
			try{
				inst.CreateInstance();
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
		return inst;
	}

	public Document createDocument(String namespaceURI,
										String qualifiedName, DocumentType doctype)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** createDocument namespaceURI<"+namespaceURI+"> qualifiedName<"+qualifiedName+">  doctype<"+doctype+">****");
		Document doc=null;
		try{
			doc=CreateDocument(namespaceURI, qualifiedName, doctype);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** createDocument doc<"+doc+"> ****");
		return doc;
	}

	public DocumentType createDocumentType(String qualifiedName,
												String publicId, String systemId)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** createDocumentType qualifiedName<"+qualifiedName+"> publicId<"+publicId+">  systemId<"+systemId+">****");
		DocumentType docType=null;
		try{
			docType=CreateDocumentType(qualifiedName, publicId, systemId);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** createDocumentType docType<"+docType+"> ****");
		return docType;
	}

	public boolean hasFeature(String feature, String version){
		if(JRexL.on)JRexL.log(className,"**** hasFeature feature<"+feature+"> version<"+version+"> ****");
		boolean hasFeature=false;
		try{
			hasFeature=HasFeature(feature, version);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** hasFeature hasFeature<"+hasFeature+"> ****");
		return hasFeature;
	}

    public boolean equals(Object obj) {
		if(JRexL.on)JRexL.log(className,"**** equals obj<"+obj+"> ****");
		if(!(obj instanceof JRexDOMImplementationImpl))
			return false;
		return ((JRexDOMImplementationImpl)obj).peerDOMImpl==peerDOMImpl;
	}

    public int hashCode(){
		if(JRexL.on)JRexL.log(className,"**** hashCode ****");
		return peerDOMImpl;
    }

    protected void finalize()throws Throwable{
		if(JRexL.on)JRexL.log(className,"**** finalize ****");
		dispose();
		super.finalize();
	}

	/** Function to explicitly disconnect from native DOM Object */
    public void dispose(){
		if(JRexL.on)JRexL.log(className,"**** dispose ****");
		if(peerDOMImpl!=0)
		try{
			Finalize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}finally{
			peerDOMImpl=0;
		}
	}
	//DOM3
	public Object getFeature(String feature, String version){
		if(JRexL.on)JRexL.log(className,"**** getFeature feature<"+feature+"> version<"+version+">****");
		Object objFeature=null;
		/* Not yet implemented in mozilla
		try{
			objFeature=GetFeature(feature, version);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}*/
		if(JRexL.on)JRexL.log(className,"**** getFeature objFeature<"+objFeature+"> ****");
		return objFeature;
	}

	private static native void Initialize()throws JRexException;
	private static native void UnInitialize()throws JRexException;
	private native void CreateInstance()throws JRexException;
    private native Document	CreateDocument(String namespaceURI, String qualifiedName, DocumentType doctype)throws DOMException, JRexException;;
	private native DocumentType	CreateDocumentType(String qualifiedName, String publicId, String systemId)throws DOMException, JRexException;;
	private native boolean	HasFeature(String feature, String version)throws JRexException;;
	private native void Finalize()throws JRexException;
	//DOM3
	private native Object GetFeature(String feature, String version)throws JRexException;
}
