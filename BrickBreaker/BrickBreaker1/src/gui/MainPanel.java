package gui;

import java.awt.BorderLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;


public class MainPanel extends JPanel {
	
	BreakerPanel breaker;
	
	public BreakerPanel getBp() {
		return breaker;
	}

	
	public MainPanel() {
		super(new BorderLayout());
		
		breaker = new BreakerPanel();
		this.add(breaker, BorderLayout.CENTER);
	
}
	
}
