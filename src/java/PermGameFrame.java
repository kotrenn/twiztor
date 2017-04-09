package permgame;

import javax.swing.JFrame;

public class PermGameFrame extends JFrame
{
	private static final long serialVersionUID = 9166502739395188929L;

	private PuzzleData        m_puzzleData;
	private PuzzleController  m_puzzleController;
	private PuzzlePanel       m_puzzlePanel;
	private boolean           m_loadedFromFile;
	private String            m_puzzleFileName = "";

	public PermGameFrame()
	{
		m_puzzleData = new PuzzleData();
		m_puzzleData.makeBasicLevel();
		m_puzzleController = new PuzzleController(m_puzzleData);
		m_loadedFromFile = false;
	}

	public PermGameFrame(String fileName)
	{
		m_puzzleData = new PuzzleData();
		new PuzzleReader().readFromFile("puzzles/" + fileName, m_puzzleData);
		m_puzzleController = new PuzzleController(m_puzzleData);
		m_loadedFromFile = true;
		m_puzzleFileName = fileName;
	}
	
	public void createAndShowGUI()
	{
		// Set the title
		String title = "Permutation Game";
		if (m_loadedFromFile) title += " - " + m_puzzleFileName;
		setTitle(title);
		
		// What to do on close
		if (!m_loadedFromFile) setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// Initialize the puzzle panel and key input
		m_puzzlePanel = new PuzzlePanel(m_puzzleData, m_puzzleController);
		m_puzzlePanel.createAndShowGUI();
		add(m_puzzlePanel);
		addKeyListener(m_puzzleController);
		
		// Show time
		setVisible(true);
		pack();
	}
}
