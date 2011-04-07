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

package org.mozilla.jrex;

import java.io.*;
import java.net.*;
import java.lang.reflect.*;
import java.util.zip.*;

/** A Class to install Mozilla GRE for JRex when JRex is deployed via webstart.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/

public class JRexGreInstaller {

	/**
	* This function Install's the GRE for JRex, supposed to be used when JRex is deployed using webstart.
	* It basically searches for <code>greArchive</code> in classpath, if found it is unzipped to
	* <code>installPath</code>.
	* @param greArchive The name of the GRE archive.
	* @param installPath The path where GRE should be installed, if <code>null</code> defaults to user's home directory.
	* @return <code>true</code> if GRE installation was successfull.
	*/
	public static boolean installGRE(String greArchive, String installPath, Object exService, Method update, Method status){
		log("installGRE() greArchive<"+greArchive+"> installPath<"+installPath+"> ");
		try{
			if(installPath==null)
				installPath=System.getProperty("user.home");
			if(!installPath.endsWith(File.separator))
				installPath += File.separator;
			log("installGRE() installPath<"+installPath+">");
			File installDir=new File(installPath);
			int dotIndex=greArchive.lastIndexOf(".");
			String dirName=greArchive;
			if(dotIndex!=-1)
				dirName=greArchive.substring(0,dotIndex);
			log("installGRE() dirName<"+dirName+">");
			File greDirPath =new File(installDir.getAbsolutePath(), dirName);
			log("installGRE() greDirPath<"+greDirPath+">");

			status.invoke( exService, new String[]{"Using GRE Directory Path <"+greDirPath+">"});
			update.invoke( exService, new Object[]{new Integer(2)});
			if(greDirPath.exists()){
				log("installGRE() GRE ALREADY INSTALLED !!!");
				status.invoke( exService, new String[]{"Found old GRE Directory, Removing...."});
				greDirPath.delete();
			}
			boolean madeDirs=installDir.exists();
			if(!madeDirs)
				madeDirs=installDir.mkdirs();
			log("installGRE() installDir<"+installDir+"> madeDirs <"+madeDirs+">");
			if(madeDirs){
				installToDir(installDir,greArchive, exService, update, status);
				log("installGRE() GRE InsatlledPath<"+greDirPath.getAbsolutePath()+">");
				System.setProperty("jrex.gre.path",greDirPath.getAbsolutePath());
				return true;
			}
		}catch(Exception ex){
			ex.printStackTrace();
		}
		return false;
	}

	private final static void installToDir(File dir, String greArchive, Object exService, Method update, Method status)throws Exception{
		log("installToDir() dir<"+dir+"> greArchive<"+greArchive+">");

		URL resURL= JRexGreInstaller.class.getResource(greArchive);
		log("installToDir() resURL<"+resURL+">");

		status.invoke( exService, new String[]{"Getting GRE Archive From <"+resURL+">"});
		update.invoke( exService, new Object[]{new Integer(3)});

		ZipInputStream zin=new ZipInputStream(new BufferedInputStream(resURL.openStream()));
		ZipEntry ze;

		status.invoke( exService, new String[]{"Got GRE Archive"});
		update.invoke( exService, new Object[]{new Integer(6)});

		double i=0;
		int len=0;
		byte buff[]=new byte[2048];
		while((ze=zin.getNextEntry())!=null){
			log("installToDir() ZipEntry <"+ze+">");
			File destFile =new File(dir.getAbsolutePath()+File.separator+ze.getName().replace('/',File.separatorChar));
			log("installToDir() destFile <"+destFile+">");
			if(ze.isDirectory()){
				log("installToDir() ZipEntry <"+ze+"> is Directory ");
				zin.closeEntry();
				continue;
			}
			log("installToDir() ZipEntry <"+ze+"> Parent <"+destFile.getParent()+">");
			if(destFile.getParent()!=null){
				File destParent =new File(destFile.getParent());
				boolean madeDirs=destParent.mkdirs();
				log("installToDir() destParent <"+destParent+"> madeDirs <"+madeDirs+">");
			}
			status.invoke( exService, new String[]{"Installing file "+destFile.getName()+"...."});
			FileOutputStream fout=new FileOutputStream(destFile);
			while((len=zin.read(buff))!=-1){
				fout.write(buff,0,len);
			}
			fout.close();
			zin.closeEntry();
			update.invoke( exService, new Object[]{new Integer((int)(i+=0.5))});
			log("installToDir() destFile<"+destFile+"> Unzipping done!!!!");
		}
		zin.close();
	}

	private static final void log(String str){
		System.out.println(str);
	}

    public static void main(String [] args)throws Exception{
		log("main() JRexGreInstaller invoked...");
		if(args.length<1)return;
		log("main() JRexGreInstaller args[0]<"+args[0]+">");
		if(args[0].equals("install")){
			log("main() Installing JREX GRE...");
			Class srvMgrClass = Class.forName( "javax.jnlp.ServiceManager");
			log("main() srvMgrClass<"+srvMgrClass+">");
			Method lookup = srvMgrClass.getMethod("lookup", new Class[]{String.class});
			log("main() lookup method<"+lookup+">");
			Object exService = lookup.invoke(null, new Object[]{ "javax.jnlp.ExtensionInstallerService" });
			log("main() exService<"+exService+">");
			Method update = exService.getClass().getMethod("updateProgress", new Class[]{int.class});
			Method status = exService.getClass().getMethod("setStatus", new Class[]{String.class});
			log("main() update<"+update+"> status<"+status+">");

			update.invoke( exService, new Object[]{new Integer(1)});
			boolean success = installGRE("jrex_gre.zip",null,exService, update, status);
			status.invoke( exService, new String[]{"GRE Installation Done."});
			update.invoke( exService, new Object[]{new Integer(100)});
			log("main() Installing JREX GRE success<"+success+">");
			if (success){
				Method installSucceeded = exService.getClass().getMethod("installSucceeded", new Class[]{boolean.class});
				log("main() installSucceeded<"+installSucceeded+">");
				installSucceeded.invoke( exService, new Object[]{new Boolean(false)});

				Method setNativeLibraryInfo = exService.getClass().getMethod("setNativeLibraryInfo", new Class[]{String.class});
				log("main() setNativeLibraryInfo<"+setNativeLibraryInfo+">");
				setNativeLibraryInfo.invoke( exService, new Object[]{System.getProperty("jrex.gre.path")});
			}else{
				Method installFailed = exService.getClass().getMethod("installFailed", null);
				log("main() installFailed<"+installFailed+">");
				installFailed.invoke( exService, null);
			}
		}else{
			log("Invalid Install args passed...");
		}
		System.exit(0);
    }
}


