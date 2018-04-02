import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
import java.io.*;
import javax.imageio.*;

/**
 *
 * @author David ALBERT
 *
 */
public class Panneau extends JPanel implements MouseListener{

    public static final Color LED_COLOR = new Color(255,20,20);
    
    private static int nbLigne = 8;
    private static int nbColonne = 8;

    private boolean[][] led;
    private long[] value;


    public Panneau(){
	super();
	led = new boolean[8][8];
	value = new long[8];
	for (int j=0;j< nbColonne;j++){
	    for (int i=0;i< nbLigne;i++){
		this.led[i][j]=false;
	    }
	    this.value[j]=0;
	}
	
	this.addMouseListener(this);
    }
    
    public Panneau(int nbLigne,int nbColonne){
	super();
	this.nbLigne=nbLigne;
	this.nbColonne=nbColonne;
	led = new boolean[nbColonne][nbLigne];
	value = new long[nbColonne];
	
	for (int j=0;j< nbColonne;j++){
	    for (int i=0;i< nbLigne;i++){
		this.led[j][i]=false;
	    }
	    this.value[j]=0;
	}
	
	this.addMouseListener(this);
    }

    public void paintComponent(Graphics g){

	int largeurCase =  this.getWidth()/nbColonne;
	int hauteurCase =  this.getHeight()/(nbLigne+1);

	
	// Dessiner les pixels
	for (int j=0;j< nbColonne;j++){
	    for (int i=0;i< nbLigne;i++){
	    	if (led[j][i]) {
		    g.setColor(this.LED_COLOR);
		    g.fillOval(j*largeurCase,i*hauteurCase,largeurCase,hauteurCase);
		}
		else {
		    g.setColor(GenerateurDessin.BACKGROUND_COLOR);
		    g.fillOval(j*largeurCase,i*hauteurCase,largeurCase,hauteurCase);
		
		}
		g.setColor(new Color(50,50,50));
		g.drawOval(j*largeurCase,i*hauteurCase,largeurCase,hauteurCase);
	
		 
	    }
	}

	calculerValeur();	
	g.setColor(GenerateurDessin.BACKGROUND_COLOR);
	g.fillRect(0,nbLigne*hauteurCase+2,this.getWidth(),hauteurCase);
	// Dessiner les valeurs associées
	for (int c=0;c<nbColonne;c++){
	    g.setFont(new Font("Arial", Font.BOLD,26-nbColonne));
	    g.setColor(this.LED_COLOR);
	    g.drawString(""+value[c]+"",c*largeurCase+largeurCase/6,nbLigne*hauteurCase+hauteurCase/2);
	    if (c==0)
		System.out.print(""+value[c]+"");
	    else
		System.out.print(", "+value[c]+"");
	}	
	System.out.println("");
    }

    
    public void mouseClicked(MouseEvent e){
	int x = e.getX()/((int) this.getWidth()/nbColonne);
	int y = e.getY()/((int) this.getHeight()/(nbLigne+1));
	
	if (led[x][y])
	    led[x][y]=false;
	else
	    led[x][y] = true;

	System.out.println("Coord : "+x+"/"+y+" = "+led[x][y]);
	repaint();
    }

    public void mousePressed(MouseEvent e){}
    public void mouseReleased(MouseEvent e){}
    public void mouseEntered(MouseEvent e){}
    public void mouseExited(MouseEvent e){}

    
    private void calculerValeur(){
	for (int col=0;col< nbColonne;col++){
	    value[col] = 0;
	    for (int l=0;l< nbLigne;l++){
		if (led[col][l])
		    value[col]+=(int) Math.pow(2,l);
	    }
	}
    }
    
}
