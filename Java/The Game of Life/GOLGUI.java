import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class GOLGUI implements MouseListener,MouseMotionListener,ActionListener,ChangeListener {
	public int generation;
	private int screenHeight;
	private int screenWidth;
	public int population;
	public JLabel populationLabel, generationLabel, speedLabel;
	public JButton runButton, autoRunButton, stopButton, clearButton, drawModeButton;
	public DrawingPanel gameOfLifePanel;
	public JSlider timerDelaySlider;
	static final int minDelay = 10;
	static final int maxDelay = 1000;
	static final int initialDelay = 500;
	Timer timer;
	
	GOLGUI() {
		//GUI Stuff
		JFrame mainFrame = new JFrame("Conway's Game of Life");
		
		//Info Panel
		JPanel infoPanel = new JPanel();
		infoPanel.setLayout(new GridBagLayout());
		GridBagConstraints c = new GridBagConstraints();
		Toolkit tk = Toolkit.getDefaultToolkit();
		Dimension screen = tk.getScreenSize();
		screenWidth = screen.width;
		screenHeight = screen.height;
		Font font = new Font(Font.SERIF, Font.PLAIN, screenHeight/50);
		infoPanel.setBounds(screenWidth*4/5, 0, screenWidth/5, screenHeight);
		infoPanel.setBackground(Color.CYAN);
		
		c.fill = GridBagConstraints.BOTH;
		c.gridx = 0;
		c.gridy = 0;
		c.weightx = 1.0;
		c.weighty = 1.0;
		generation = 1;
		generationLabel = new JLabel("Generation #" + generation);
		generationLabel.setFont(font);
		infoPanel.add(generationLabel, c);
		
		c.fill = GridBagConstraints.HORIZONTAL;
		c.gridx = 0;
		c.gridy = 2;
		runButton = new JButton("Run");
		runButton.setFont(font);
		runButton.setAlignmentX(JButton.CENTER);
		runButton.setActionCommand("Run");
		runButton.addActionListener(this);
		infoPanel.add(runButton, c);
		
		c.gridx = 0;
		c.gridy = 3;
		autoRunButton = new JButton("Auto Run");
		autoRunButton.setBounds(10, 2*screenHeight/4 + 10, screenWidth/5, screenHeight/4);
		autoRunButton.setFont(font);
		autoRunButton.setActionCommand("Auto Run");
		autoRunButton.addActionListener(this);
		infoPanel.add(autoRunButton, c);
		
		c.gridx = 1;
		c.gridy = 3;
		stopButton = new JButton("Stop");
		stopButton.setFont(font);
		stopButton.setActionCommand("Stop");
		stopButton.setEnabled(false);
		stopButton.addActionListener(this);
		infoPanel.add(stopButton, c);
		
		c.gridx = 0;
		c.gridy = 1;
		population = 0;
		populationLabel = new JLabel("Population: " + population);
		populationLabel.setBounds(10, 10, screenWidth/10, screenHeight/4);
		populationLabel.setFont(font);
		infoPanel.add(populationLabel, c);
		
		c.gridx = 0;
		c.gridy = 6;
		clearButton = new JButton("Clear Board");
		clearButton.setFont(font);
		clearButton.setActionCommand("Clear");
		clearButton.addActionListener(this);
		infoPanel.add(clearButton, c);
		
		c.gridx = 0;
		c.gridy = 4;
		timerDelaySlider = new JSlider(JSlider.HORIZONTAL,minDelay,maxDelay,initialDelay);
		timerDelaySlider.addChangeListener(this);
		timerDelaySlider.setFont(font);
		timerDelaySlider.addChangeListener(this);
		infoPanel.add(timerDelaySlider, c);
		
		c.gridx = 1;
		c.gridy = 4;
		speedLabel = new JLabel("Speed");
		speedLabel.setFont(font);
		infoPanel.add(speedLabel, c);
		
		c.gridx = 0;
		c.gridy = 5;
		drawModeButton = new JButton("Draw");
		drawModeButton.setFont(font);
		drawModeButton.addActionListener(this);
		drawModeButton.setActionCommand("Mode Change");
		infoPanel.add(drawModeButton, c);
		
		c.gridx = 0;
		c.gridy = 7;
		c.ipady = screenHeight*2/3;
		JLabel EmptyLabel = new JLabel("");
		infoPanel.add(EmptyLabel, c);
		
		mainFrame.add(infoPanel);
		
		//Game of Life Panel
		gameOfLifePanel = new DrawingPanel();
		gameOfLifePanel.setBounds(0, 0, screenWidth*4/5, screenHeight);
		gameOfLifePanel.setBackground(Color.WHITE);
		mainFrame.add(gameOfLifePanel);
		mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		mainFrame.setSize(screenWidth, screenHeight);
		mainFrame.setLayout(null);
		mainFrame.setVisible(true);
		timer = new Timer(minDelay+maxDelay-initialDelay,null);
	}
	
	//Specialized panel for the actual grid
	class DrawingPanel extends JPanel  {
		private int panelWidth;
		private int panelHeight;
		private int gridWidth = screenWidth/100;
		public Cell[][] cells;
		Graphics drawingArea;
		Image display;
		
		public DrawingPanel() {
			setBorder(BorderFactory.createLineBorder(Color.black));
			cells = new Cell[screenWidth/gridWidth + 1][screenHeight/gridWidth + 1];
			addMouseMotionListener(new MouseAdapter() {
				public void mouseDragged(MouseEvent e) {
					Cell c = findCell(e.getX(),e.getY());
					if(c == null)
						return;
					Graphics g = getGraphics();
					if(drawModeButton.getText().equals("Draw")) {
						g.setColor(Color.BLACK);
						g.fillRect(c.getX1() + 1, c.getY1() + 1, gridWidth - 1, gridWidth - 1);
						c.setPopulation(true);
						update();
					}
					else {
						g.setColor(Color.WHITE);
						g.fillRect(c.getX1() + 1, c.getY1() + 1, gridWidth - 1, gridWidth - 1);
						c.setPopulation(false);
						update();
					}
				}
			});
			addMouseListener(new MouseAdapter() {
				public void mouseClicked(MouseEvent e) {
					Graphics g=getGraphics();  
					editCell(e.getX(), e.getY(), g);
					update();
				}
			});
			
			
			display = createImage(screenWidth,screenHeight);
		}
		
		//I thought it would be useful to utilize some functions built into JPanel so that I could initialize certain variables and the grid itself
		public void setBounds(int x, int y, int width, int height) {
			super.setBounds(x, y, width, height);
			panelWidth = width;
			panelHeight = height;
		}
		protected void paintComponent(Graphics g) {
			super.paintComponent(g);
			drawGrid(g);
		}
		private void drawGrid(Graphics g) {
			for(int i = 0; i < panelWidth; i += gridWidth) {
				for(int j = 0; j < panelHeight; j += gridWidth) {
					g.drawRect(i, j, i + gridWidth, j + gridWidth);
					cells[i/gridWidth][j/gridWidth] = new Cell(i,j,i+gridWidth,j+gridWidth);
				}
			}
		}
		
		
		//Fairly simple update to make sure population counts are accurate
		private void update() {
			population = getPopulationCount();
			populationLabel.setText("Population: " + population);
		}
		private int getPopulationCount() {
			int count = 0;
			for(int i = 0; i < cells.length; i++) {
				for(int j = 0; j < cells[i].length; j++) {
					if(cells[i][j] != null)
						if(cells[i][j].isPopulated())
							count++;
				}
			}
			return count;
		}
		

		//This function's sole purpose is to swap between dead/alive when a grid cell is clicked
		private void editCell(int x, int y, Graphics g) {
			Cell c = findCell(x,y);
			if(c == null)
				return;
			if(c.isPopulated()) {
				g.setColor(Color.WHITE);
				g.fillRect(c.getX1() + 1, c.getY1() + 1, gridWidth - 1, gridWidth - 1);
				c.setPopulation(false);
			} 
			else {
				g.setColor(Color.BLACK);
				g.fillRect(c.getX1() + 1, c.getY1() + 1, gridWidth - 1, gridWidth - 1);
				c.setPopulation(true);
			}
		}
		private Cell findCell(int x, int y) {
			for(int i = 0; i < cells.length; i++) {
				for(int j = 0; j < cells[i].length; j++) {
					Cell c = cells[i][j];
					if(c != null) {
						if(containsBetween(c.getX1(),c.getX2(),x) && containsBetween(c.getY1(),c.getY2(),y))
							return c;
					}
				}
			}
			return null;
		}
		private boolean containsBetween(int coord1, int coord2, int point) {
			if(coord1 < coord2)
				return (point >= coord1 && point <= coord2);
			else
				return (point >= coord2 && point <= coord1);
		}
		
		//This function goes through the steps to run a generation of the Game of Life
		public void GOLGeneration() {
			determineAllCellsFates();
			makeAllFatesCurrent();
			generation++;
			generationLabel.setText("Generation #" + generation);
		}
		
		public void determineAllCellsFates() {
			for(int i = 0; i < cells.length; i++) {
				for(int j = 0; j < cells[i].length; j++) {
					if(cells[i][j] != null) {
						Cell[][] neighbors = createNeighbors(i,j);
						cells[i][j].determineFate(neighbors);
					}
				}
			}
		}

		public void makeAllFatesCurrent() {
			for(int i = 0; i < cells.length; i++) {
				for(int j = 0; j < cells[i].length; j++) {
					if(cells[i][j] != null) {
						Cell c = cells[i][j];
						if(c.isPopulated() != c.willBePopulated()) {
							c.setPopulation(c.willBePopulated());
							if(c.isPopulated()) {
								Graphics g = getGraphics();
								g.setColor(Color.BLACK);
								g.fillRect(c.getX1() + 1, c.getY1() + 1, gridWidth - 1, gridWidth - 1);
							}
							else {
								Graphics g = getGraphics();
								g.setColor(Color.WHITE);
								g.fillRect(c.getX1() + 1, c.getY1() + 1, gridWidth - 1, gridWidth - 1);
							}
						}
					}
				}
			}
		}
		public Cell[][] createNeighbors(int x, int y) {
			Cell[][] neighbors = new Cell[3][3];
			for(int i = 0; i < neighbors.length; i++) {
				for(int j = 0; j < neighbors[i].length; j++) {
					try {
						neighbors[i][j] = cells[i+x-1][j+y-1];
					}
					catch(Exception e) {
						neighbors[i][j] = null;
					}
				}
			}
			return neighbors;
		}
		
		//Reset's the board's population and generation
		public void clear() {
			Graphics g = getGraphics();
			for(int i = 0; i < cells.length; i++) {
				for(int j = 0; j < cells[i].length; j++) {
					Cell c = cells[i][j];
					if(c != null) {
						c.setPopulation(false);
						g.setColor(Color.WHITE);
						g.fillRect(c.getX1() + 1, c.getY1() + 1, gridWidth - 1, gridWidth - 1);
					}
				}
			}
			update();
			generation = 1;
			generationLabel.setText("Generation #" + generation);
		}
	}

	public void mouseEntered(MouseEvent e) {}
	public void mouseExited(MouseEvent e) {}
	public void mousePressed(MouseEvent e) {}
	public void mouseReleased(MouseEvent e) {}
	public void mouseMoved(MouseEvent e) {}
	public void mouseDragged(MouseEvent e) {}
	public void mouseClicked(MouseEvent e) {}
	
	public void stateChanged(ChangeEvent e) {
		JSlider source = (JSlider)e.getSource();
		timer.setDelay(minDelay+maxDelay-(int)source.getValue());
	}
	
	public void actionPerformed(ActionEvent e) {
		if(e.getActionCommand().equalsIgnoreCase("Run")) {
			gameOfLifePanel.GOLGeneration();
			gameOfLifePanel.update();
		}
		else if(e.getActionCommand().equalsIgnoreCase("Clear")) {
			gameOfLifePanel.clear();
			if(timer.isRunning()) {
				autoRunButton.setEnabled(true);
				stopButton.setEnabled(false);
				timer.stop();
			}
		}
		else if(e.getActionCommand().equals("Auto Run")) {
			autoRunButton.setEnabled(false);
			stopButton.setEnabled(true);
			ActionListener listener = new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					gameOfLifePanel.GOLGeneration();
					gameOfLifePanel.update();
				}
			};
			int delay = timer.getDelay();
			timer = new Timer(delay,listener);
			timer.start();
		}
		else if(e.getActionCommand().equals("Stop")) {
			autoRunButton.setEnabled(true);
			stopButton.setEnabled(false);
			timer.stop();
		}
		else if(e.getActionCommand().equals("Mode Change")) {
			if(drawModeButton.getText().equals("Draw"))
				drawModeButton.setText("Erase");
			else {
				drawModeButton.setText("Draw");
			}
		}
	}
	
	public static void main(final String args[]) {
		new GOLGUI();
	}
}