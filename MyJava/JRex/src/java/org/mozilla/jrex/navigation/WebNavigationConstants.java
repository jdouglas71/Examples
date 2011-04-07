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

package org.mozilla.jrex.navigation;

/**
* Interface WebNavigationConstants contains navigation related constants.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public interface WebNavigationConstants{

	public static final int LOAD_FLAGS_MASK = 65535;

	/**
	* loadURI() specific flags
	*/

	/**
	* Normal load flag.
	*/
	public static final int LOAD_FLAGS_NONE = 0;

	/**
	* Meta-refresh flag.  The cache is bypassed.  This type of load is
	*                     usually the result of a meta-refresh tag, or a HTTP
	*                     'refresh' header.
	*/
	public static final int LOAD_FLAGS_IS_REFRESH = 16;

	/**
	* Link-click flag.
	*/
	public static final int LOAD_FLAGS_IS_LINK = 32;

	/**
	* Bypass history flag.
	*/
	public static final int LOAD_FLAGS_BYPASS_HISTORY = 64;

	/**
	* Replace history entry flag.
	*/
	public static final int LOAD_FLAGS_REPLACE_HISTORY = 128;

	public static final int LOAD_FLAGS_BYPASS_CACHE = 256;

	public static final int LOAD_FLAGS_BYPASS_PROXY = 512;

	public static final int LOAD_FLAGS_CHARSET_CHANGE = 1024;

	/**
	* loadStream() specific flags
	*/
	public static final int STREAM_LF_NORMAL = 0;

	public static final int STREAM_LF_REPLACE = 1;

	public static final int STREAM_LF_HISTORY = 2;

	public static final int STREAM_LF_RELOAD_NORMAL = 3;

	public static final int STREAM_LF_RELOAD_BYPASS_CACHE = 4;

	public static final int STREAM_LF_RELOAD_BYPASS_PROXY = 5;

	public static final int STREAM_LF_RELOAD_BYPASS_PROXY_AND_CACHE = 6;

	public static final int STREAM_LF_IS_LINK = 7;

	public static final int STREAM_LF_IS_REFRESH = 8;

	public static final int STREAM_LF_CHARSET_CHANGE = 9;

	public static final int STREAM_LF_BYPASS_HISTORY = 10;

	/**
	* Stop() flags:
	*/
	/**
	* Stop all network activity.  This includes both active network loads and
	* pending meta-refreshes.
	*/
	public static final int STOP_NETWORK = 1;

	/**
	* Stop all content activity.  This includes animated images, plugins and
	* pending Javascript timeouts.
	*/
	public static final int STOP_CONTENT = 2;

	/**
	* Stop all activity.
	*/
	public static final int STOP_ALL = 3;

	/**
	* Indicates information type page-info.
	*/
	public static final short TYPE_PAGE_INFO	= 0;

	/**
	* Indicates information type security-info.
	*/
	public static final short TYPE_SEC_INFO		= 1;


	/**
	* getContentString() specific flags
	*/

	/** Output only the selection (as opposed to the whole document).*/
	public static final int OUTPUT_SELECTION_ONLY = 1;

	/** Plaintext output: Convert html to plaintext that looks like the html.
	* Implies wrap (except inside <pre>), since html wraps.
	* HTML output: always do prettyprinting, ignoring existing formatting.
	* (Probably not well tested for HTML output.)
	*/
	public static final int OUTPUT_FORMATTED     = 2;

	/** OutputRaw is used by copying text from widgets*/
	public static final int OUTPUT_RAW           = 4;

	/**  No html head tags*/
	public static final int OUTPUT_BODY_ONLY      = 8;

	/** Wrap even if we're not doing formatted output (e.g. for text fields)*/
	public static final int OUTPUT_PREFORMATTED  = 16;

	/**  Output as though the content is preformatted
	* (e.g. maybe it's wrapped in a MOZ_PRE or MOZ_PRE_WRAP style tag)
	*/
	public static final int OUTPUT_WRAP          = 32;

	/**  Output for format flowed (RFC 2646). This is used when converting
	* to text for mail sending. This differs just slightly
	* but in an important way from normal formatted, and that is that
	* lines are space stuffed. This can't (correctly) be done later.
	*/
	public static final int OUTPUT_FORMAT_FLOWED  = 64;

	/**  Convert links, image src, and script src to absolute URLs when possible*/
	public static final int OUTPUT_ABSOLUTE_LINKS = 128;

	/**  Attempt to encode entities standardized at W3C (HTML, MathML, etc).
	* This is a catch-all flag for documents with mixed contents. Beware of
	* interoperability issues. See below for other flags which might likely
	* do what you want.
	*/
	public static final int OUTPUT_ENCODE_W3C_ENTITIES = 256;

	/** LineBreak processing: we can do either platform line breaks,
	* CR, LF, or CRLF.  If neither of these flags is set, then we
	* will use platform line breaks.
	*/
	public static final int OUTPUT_CR_LINEBREAK = 512;
	public static final int OUTPUT_LF_LINEBREAK = 1024;

	/** Output the content of noscript elements (only for serializing
	* to plaintext).
	*/
	public static final int OUTPUT_NO_SCRIPT_CONTENT = 2048;

	/** Output the content of noframes elements (only for serializing
	* to plaintext).
	*/
	public static final int OUTPUT_NO_FRAMES_CONTENT = 4096;


	/** Don't allow any formatting nodes (e.g. <br>, <b>) inside a <pre>.
	* This is used primarily by mail.
	*/
	public static final int OUTPUT_NO_FORMATTINGIN_PRE = 8192;

	/** Encode entities when outputting to a string.
	* E.g. If set, we'll output &nbsp; if clear, we'll output 0xa0.
	* The basic set is just &nbsp; &amp; &lt; &gt; &quot; for interoperability
	* with older products that don't support &alpha; and friends.
	* The Latin1 entity set additionally includes 8bit accented letters
	* between 128 and 255.
	* The HTML entity set additionally includes accented letters, greek
	* letters, and other special markup symbols as defined in HTML4.
	*/
	public static final int OUTPUT_ENCODE_BASIC_ENTITIES = 16384;
	public static final int OUTPUT_ENCODE_LATIN1_ENTITIES = 32768;
	public static final int OUTPUT_ENCODE_HTML_ENTITIES = 65536;
}