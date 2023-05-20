package gui;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JPanel;
import javax.swing.Timer;

import logika.MainMap;

public class BreakerPanel extends JPanel implements KeyListener,ActionListener{
	
	
	private boolean play = false;
	private int score = 0;
	
	private int totalBricks = 21;
	
	private Timer timer;
	private int delay = 8;
	
	private int ballposX = 120;
	private int ballposY = 350;
	
	private int ballXdir = -2;
	private int ballYdir = -2;
	
	private int playerX = 350; 
	
	
	private MainMap map;
	
	public BreakerPanel(){ //konstruktor
		map = new MainMap(3,7);
		addKeyListener(this);
		setFocusable(true);
		setFocusTraversalKeysEnabled(false);
		
		timer = new Timer(delay,this);
		timer.start();
	}

	
	public void paint(Graphics g) {
		
		g.setColor(Color.black);
		g.fillRect(1, 1, 692, 592);
		
		map.draw((Graphics2D)g);
		
		//borders 
		g.setColor(Color.yellow);
		g.fillRect(0,0, 3, 592);
		g.fillRect(0,0, 692, 3);
		g.fillRect(692,0, 3, 592);
		
		//scores
		
		g.setColor(Color.white);
		g.setFont(new Font("serif",Font.BOLD,25));
		g.drawString("" + score, 590, 30);
		//paddle
		
		g.setColor(Color.red);
		g.drawRect(playerX,550,100, 8);
		
		//ball
		g.setColor(Color.yellow);
		g.fillOval(ballposX, ballposY, 20, 20);
		
		if(totalBricks <= 0) {
			play = false;
			ballXdir = 0;
			ballYdir = 0;
			g.setColor(Color.red);
			g.setFont(new Font("serif",Font.BOLD,30));
			g.drawString("You Won, Scores: " + score,260, 300);
			
			g.setFont(new Font("serif",Font.BOLD,20));
			g.drawString("Press Enter To Restart ",260, 350);
			
		}
		
		if(ballposY > 570) {
			play = false;
			ballXdir = 0;
			ballYdir = 0;
			g.setColor(Color.red);
			g.setFont(new Font("serif",Font.BOLD,30));
			g.drawString("Game Over, Scores: " + score,190, 300);
			
			g.setFont(new Font("serif",Font.BOLD,30));
			g.drawString("Press Enter To Restart ",230, 350);
			
		}
		g.dispose();
		
	}
	
	@Override
	public void keyPressed(KeyEvent e) {
		// TODO Auto-generated method stub
		
		if(e.getKeyCode() == KeyEvent.VK_RIGHT) {
			if(playerX >= 600)
				playerX = 600;
			
			else 
				moveRight();
			
		}	
	
		if(e.getKeyCode() == KeyEvent.VK_LEFT) {
			if(playerX <= 10)
				playerX = 10;
			
			else 
				moveLeft();	
		}	
		
		if(e.getKeyCode() == KeyEvent.VK_ENTER) {
			if(!play) {
				play = true;
				 ballposX = 120;
				 ballposY = 350;	
				 ballXdir = -1;
				 ballYdir = -2;
				 playerX = 310;
				 score = 0;
				 totalBricks = 21;
				 map = new MainMap(3,7);
				 repaint();
				 
			}
		}
}


	private void moveLeft() {
		// TODO Auto-generated method stub
		play = true;
		playerX-=20;
	}


	private void moveRight() {
		// TODO Auto-generated method stub
		play = true;
		playerX+=20;
		
	}


	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		timer.start();
		
		if(play) {
			
			if(new Rectangle(ballposX,ballposY,20,20).intersects(new Rectangle(playerX,550,100,8))) {
				ballYdir = -ballYdir;
				
			}
			
			A:for(int i = 0;i < map.map.length;i++) {
				for(int j = 0;j < map.map[0].length;j++) {
					if(map.map[i][j] > 0) {
						int brickX = j*map.brickWidth + 70;
						int brickY = i * map.brickHeight + 50;
						int brickWidth = map.brickWidth;
						int brickHeight = map.brickHeight;
						
						Rectangle rect = new Rectangle(brickX,brickY,brickWidth,brickHeight);
						Rectangle ballRect = new Rectangle(ballposX,ballposY,20,20);
						Rectangle brickRect = rect;
						
						if(ballRect.intersects(brickRect)) {
							map.setBrickValue(0, i, j);
							totalBricks--;
							score += 5;
							
							if(ballposX + 19 <= brickRect.x || ballposX + 1 >= brickRect.x + brickRect.width ) {
								ballXdir = -ballXdir;
							}
							else
								ballYdir = -ballYdir;
							
							break A;
						}
						
					}
				}
			}
			
			ballposX += ballXdir;
			ballposY += ballYdir;
			
			if(ballposX < 0) {
				ballXdir = -ballXdir;
				System.out.print(ballXdir);
			}
			if(ballposY < 0) {
				ballYdir = -ballYdir;
				System.out.print(ballYdir);
			}
			if(ballposX > 670) {
				ballXdir = -ballXdir;
			}
			
		}
		
		repaint();
		
	}


	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub
	}


	@Override
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub
	}


	


	
	
	

}
