import javax.swing.text.*;

class NumericDocument extends PlainDocument
{
	public void insertString(int offs,String str,AttributeSet a) throws BadLocationException
	{
		//System.out.println("saisie: "+str);
		//	System.out.println("txt: "+this.getText(0,getLength()));
		String nstr="";
		Character tmp = ' ';
		if(str != null)
		{
			for(int i=0;i<str.length();i++)
			{
				if(Character.isLetter(str.charAt(i)))
				{
					tmp = Character.toUpperCase(str.charAt(i));
					nstr=nstr+tmp;
				}
			}
			if ( nstr.length() != 0 )
				super.insertString(offs, nstr, a);
		}
		//System.out.println("txt: "+this.getText(0,getLength()));
	}
}
