
import visidia.simulation.process.algorithm.Algorithm;
import visidia.simulation.process.edgestate.MarkedState;
import visidia.simulation.process.messages.IntegerMessage;
import visidia.simulation.process.messages.StringMessage;
import visidia.simulation.SimulationConstants.PropertyStatus;
import visidia.simulation.process.messages.Door;
import visidia.simulation.process.messages.Message;

import visidia.simulation.*;
import visidia.misc.*;


import java.awt.*;
import javax.swing.*;

public class exemple2 extends Algorithm {

public void init(){

    System.out.println("Je suis : " + this.getId() + ", j'ai " + this.getArity() + " noeuds et il y a " + this.getNetSize() + " noeuds en tout.");
	// Ne fonctionne pas
	//putProperty("B" , this.getId(), SimulationConstants.PropertyStatus.DISPLAYED);
	

	Message m2;
	StringMessage m = new StringMessage("Je suis : " + this.getId());
	sendAll(m);
	// j'en suis à l'exo 8

	for(int i = 0 ; i < this.getArity() ; i++)
	{
		Door d = new Door(i);
		m2 = receive(d);
		System.out.println(m2);
	}

} // fin init

public Object clone(){
	return new exemple2();
}

} //fin class exemple2
