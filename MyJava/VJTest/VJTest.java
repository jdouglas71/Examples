/**
 * This class is designed to be packaged with a COM DLL output format.
 * The class has no standard entry points, other than the constructor.
 * Public methods will be exposed as methods on the default COM interface.
 * @com.register ( clsid=AD5B7D09-DB57-421C-8640-D7BE6EEE0875, typelib=91052258-6C2A-4B04-A684-38541C1A513B )
 */
public class VJTest
{
	// TODO: Add additional methods and code here

	/**
	 * NOTE: To add auto-registration code, refer to the documentation
	 * on the following method
	 *   public static void onCOMRegister(boolean unRegister) {}
	 */
	
	public String getName()
	{
		return "Jason was here";
	}
	
	public void setName(String newName)
	{	
		System.out.println(newName);
	}
	
	public int getNumber()
	{
		return 71;	
	}
	
	public void setNumber(int number)
	{
		System.out.println(number);	
	}
	
	public Object getProperty(Object key)
	{
		return null;
	}
	
	public void setProperty(Object key, Object value)
	{
	}
	
}
