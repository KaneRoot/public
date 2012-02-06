public class Chat extends Mammifere
{
	public Chat(String nom)
	{
		super(nom);
	}
	public Chat()
	{
		this("");
	}
	
	@Override
	public String GetPresentation()
	{
		return super.GetPresentation() + "Je suis un chat. ";
	}
}
