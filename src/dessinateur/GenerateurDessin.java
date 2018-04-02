import javax.swing.*;
import java.awt.*;
import java.lang.*;

/**
 * Description
 *
 * @author David ALBERT
 * 
 */

public class GenerateurDessin extends JFrame {

    public static final Color BACKGROUND_COLOR = new Color(0,0,0);

    GenerateurDessin(){
	super("Generateur de dessins pixellisés");
        this.setSize(new Dimension(800,800));

	Panneau pan = new Panneau();
	this.setBackground(BACKGROUND_COLOR);

	this.setContentPane(pan);
	
	this.setLocationRelativeTo(null); //au centre
	this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //arrête le programme quand on appuie sur la croix
	this.setResizable(true); //possibilité de redimensionner la fenêtre

	//Afficher la fenêtre
	this.setVisible(true);
	
    }
    
    GenerateurDessin(int w, int h){
	super("Generateur de dessins pixellisés");
        this.setSize(new Dimension(40*h,40*w));

	Panneau pan = new Panneau(w,h);
	this.setBackground(BACKGROUND_COLOR);

	this.setContentPane(pan);
	
	this.setLocationRelativeTo(null); //au centre
	this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //arrête le programme quand on appuie sur la croix
	this.setResizable(true); //possibilité de redimensionner la fenêtre

	//Afficher la fenêtre
	this.setVisible(true);
	
    }
    
    public static void main(String[] args){
	GenerateurDessin fenetre,fenetre2;
        if (args.length==0)
	    fenetre = new GenerateurDessin(8, 8);
    
	else
	    fenetre = new GenerateurDessin(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
	}
    
}
