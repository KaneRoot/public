public class Test
{
	public static void main(String[] args)
	{
		Animal[] animaux = new Animal[6];
		animaux[0] = new Chat("Webcam");
		animaux[1] = new Homme("Jonathan");
		animaux[2] = new Requin();
		animaux[3] = new Saumon();
		animaux[4] = new Chat();
		animaux[5] = new Requin("MegaShark");
		for(int i = 0 ; i < 6 ; i++)
			System.out.println(animaux[i].GetPresentation());

	}
}
