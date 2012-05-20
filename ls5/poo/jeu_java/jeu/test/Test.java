package test;

import modele.*;
import modele.elements.*;

import vue.*;

import util.Point2d;
import controleur.ControlerMap;

public class Test
{
	public static void main (String[] arg)
	{
		E_perso e = new E_perso(10,200,10);
		Map m = new Map(1000,300,e);
		
		m.addPoint(new Point2d(0,250));
		m.addPoint(new Point2d(200,200));
		m.addPoint(new Point2d(400,250));
		m.addPoint(new Point2d(600,200));
		m.addPoint(new Point2d(650,250));
		m.addPoint(new Point2d(800,250));
		
		m.getPerso().setPosition(m.getPerso().getPosition().getX(),
						m.getYSol(m.getPerso().getPosition().getX()));
		
		ControlerMap ctrl = new ControlerMap(m);
		ctrl.go();
	}
	
}
