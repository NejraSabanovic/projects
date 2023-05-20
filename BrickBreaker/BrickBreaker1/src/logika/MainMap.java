package logika;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.util.Random;

public class MainMap {
	
	public int map[][]; //ovdje su sve ciglice
	public int brickWidth;  //sirina 
	public int brickHeight;
	Random rand;
	
	public MainMap(int row,int col) {
		
		map = new int[row][col];
		for(int i = 0;i < map.length;i++) {
			for(int j = 0;j < map[0].length;j++)
				map[i][j] = 1;
		}
		
		
		brickWidth = 540/col;
		brickHeight = 150/row;
	}
	
	public void draw(Graphics2D g) {
		
		for(int i = 0;i < map.length;i++) {
			for(int j = 0;j < map[0].length;j++) {
				
				if(map[i][j] > 0) {
					//float r1 = rand.nextFloat();
					//float g1 = rand.nextFloat();
					//float b1 = rand.nextFloat();
					g.setColor(new Color(54,22,200));
					//g.setColor(Color.white);
					g.fillRect(j*brickWidth + 70, i*brickHeight + 50, brickWidth, brickHeight);
					
					g.setStroke(new BasicStroke(3));
					g.setColor(Color.black);
					g.drawRect(j*brickWidth + 70, i*brickHeight + 50, brickWidth, brickHeight);
				}
			}
		}
		
	}
	
	public void setBrickValue(int value,int row,int col) {
		map[row][col] = value;
	}

}
