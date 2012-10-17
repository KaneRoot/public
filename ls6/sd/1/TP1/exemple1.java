
import visidia.simulation.process.algorithm.Algorithm;
import visidia.simulation.process.edgestate.MarkedState;
import visidia.simulation.process.messages.IntegerMessage;
import visidia.simulation.process.messages.StringMessage;
import visidia.simulation.SimulationConstants.PropertyStatus;

import visidia.simulation.*;
import visidia.misc.*;


import java.awt.*;
import javax.swing.*;

public class exemple1 extends Algorithm {



public void init(){

  

    System.out.println("Mon premier exemple en Visidia.");
  
  
                 

} // fin init

 public Object clone(){
	return new exemple1();
    }
    
} //fin class exemple1
