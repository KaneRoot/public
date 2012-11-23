import java.io.* ;
import org.omg.CORBA.* ;

public class Client
{
  static public void afficheMatrice (int [][] mat)
  {
    for (int i = 0 ; i < mat.length ; ++i)
    { 
      for (int j=0 ; j < mat[0].length ; ++j)
        System.out.print(mat[i][j] + " ") ;
      System.out.println() ;
    }
  }

  public static void main( String args[] ) 
  {
    if (args.length != 0)
    {
      System.out.println("Usage: java Client") ;
      System.exit( 1 ) ;
    }

    // initialiser l'ORB.
    try
    {
      ORB orb = ORB.init(args, null ) ;
      System.out.println("0) ORB initialise") ;

      FileReader file = new FileReader(iorfile.value) ;
      BufferedReader in = new BufferedReader(file) ;
      String ior = in.readLine() ;
      file.close() ;

      System.out.println( "1) IOR lue : " + ior ) ;

      org.omg.CORBA.Object obj = orb.string_to_object(ior) ;
      OpMatrice service = OpMatriceHelper.narrow(obj) ;
      System.out.println("2) Reference obtenue a partir de l'IOR") ;

      int[][] a = { {1, 0, 0, 0}, {0, 3, 0, 0}, {0, 1, 3, 0}, {0, 4, 0, 7} } ;
      int[][] b = { {1, 4}, {1, 8}, {2, 3}, {1, 0} } ;
      int res [][] = new int [4][2] ;

      res = service.multiplicationMatrice(a,b) ;
      afficheMatrice(res) ;
    }
    catch( org.omg.CORBA.SystemException ex ) {  ex.printStackTrace() ; }
    catch( java.io.IOException ex) {  ex.printStackTrace() ; }
  }
}

