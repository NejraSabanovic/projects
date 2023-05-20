package gui;

import javax.swing.JFrame;

public class MainFrame extends JFrame{
	
	MainPanel panel;
	
	public MainPanel getBreakerPanel() {
		
		return panel;
		
	}
	
	public MainFrame() {
		
		super();
		panel = new MainPanel();
		this.setContentPane(panel);
		this.setBounds(10,10,700,600);
		this.setTitle("Brick Breaker");
		this.setResizable(false);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
		
			
		
	}
	
	
	
	
	

}

