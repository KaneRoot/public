import org.omg.CORBA.*;
import org.omg.CosNaming.*;
import java.io.*;

public class Client2
{
  static void explore_arborescence(NamingContext nc)
	{
		BindingListHolder blh = new BindingListHolder() ; 
		BindingIteratorHolder bih= new BindingIteratorHolder() ;
		Binding bl[] ;
		NameComponent name[] ;
		nc.list(100,blh,bih) ;
		bl = blh.value ;

		for (int i=0; i < bl.length ; ++i)
		{
	    name = bl[i].binding_name ;
      for (int j=0; j < name.length ; ++j)
      {
        System.out.println("-" + name[j].id + "-" + name[j].kind + "-") ;
	    }
	  }
  }
  
  public static void main(String args[])
  { 
	  try
    {
	    String [] argv = {"-ORBInitialHost", args[1], "-ORBInitialPort",args[2] } ;
	    ORB orb = ORB.init( argv, null ) ; 
	    org.omg.CORBA.Object obj = null ;
	    obj = orb.resolve_initial_references("NameService") ; 
	    if (obj == null)
      { 
        System.out.println("Ref nil sur NameService") ;
        System.exit(1) ;
	    }

	    // ETAPE 2
	    org.omg.CosNaming.NamingContext nc=NamingContextHelper.narrow(obj) ;
	    System.out.println("A la racine :") ;
	    explore_arborescence(nc) ;

	    NameComponent[] aName = new NameComponent[1] ;
	    aName[0] = new NameComponent(args[0],"") ;
	    obj = nc.resolve(aName) ;

	    NamingContext nc1 = NamingContextHelper.narrow(obj) ;
	    System.out.println("Acces au chemin : " + args[0]) ;
	    explore_arborescence(nc1) ;
    }
    catch( Exception ex )
    {
	    System.err.println( "Erreur !!" ) ;
	    ex.printStackTrace() ;
    }
  }
}

