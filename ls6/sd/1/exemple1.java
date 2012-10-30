import visidia.simulation.process.algorithm.Algorithm;
import visidia.simulation.process.edgestate.MarkedState;
import visidia.simulation.process.messages.IntegerMessage;
import visidia.simulation.process.messages.StringMessage;
import visidia.simulation.SimulationConstants.PropertyStatus;

import visidia.simulation.*;
import visidia.misc.*;

import visidia.simulation.process.messages.Door;

import java.awt.*;
import javax.swing.*;

public class exemple1 extends Algorithm 
{
	public void init()
	{
		//System.out.print("\n");	
		int nbNeighbors = getArity();
		int id = getId();
		int arity = getNetSize();

		switch(id)
		{
			case 0 : 
				System.out.print("Nombre de voisin du noeud  "+id+" = "+nbNeighbors+"\n");
				System.out.print("Nombre de noeud dans le système "+arity+"\n");
				putProperty("label","O"); 
				sendAll(new StringMessage("Message"));
				break;
			default :
				putProperty("label","T");//,SimulationConstants.PropertyStatus.DISPLAYED);
				StringMessage message = (StringMessage) receive(new Door()); 
				System.out.print("Message recu\n");
				break;
		}
		/*
		for (int i=0;i<nbNeighbors;i++)
		{
			StringMessage message = (StringMessage) receiveFrom(i);
			System.out.print("Message recu\n");
		}
		*/
	}

	public Object clone()
	{
		return new exemple1();
	}
}
