package permgame;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;

public class PuzzlePanel extends JPanel
{
	private static final long serialVersionUID = 6216972460695874867L;
	private PuzzleData        m_puzzleData;
	private PuzzleController  m_puzzleController;
	private JPanel            m_debugButtonPanel;
	private JPanel            m_permutationButtonPanel;
	private JPanel            m_macroButtonPanel;

	public PuzzlePanel(PuzzleData puzzleData, PuzzleController puzzleController)
	{
		// Puzzle shit
		m_puzzleData = puzzleData;
		m_puzzleController = puzzleController;
	}

	public void createAndShowGUI()
	{
		// Debug panel
		m_debugButtonPanel = new JPanel();
		addDebugButtons();
		add(m_debugButtonPanel, BorderLayout.NORTH);

		// Permutation buttons
		m_permutationButtonPanel = new JPanel();
		m_permutationButtonPanel.setLayout(new FlowLayout());
		addPermutationsFromData();
		add(m_permutationButtonPanel, BorderLayout.SOUTH);

		// Macro controls
		m_macroButtonPanel = new JPanel();
		addMacroButtons();
		add(m_macroButtonPanel, BorderLayout.WEST);

		// Key listening
		addKeyListener(m_puzzleController);
		
		// Set the preferred size
		setPreferredSize(new Dimension(420, 420));
	}

	private void addDebugButtons()
	{
		addSolveButton();
		addRandomizeButton();
	}

	private void addSolveButton()
	{
		JButton solveButton = new JButton("Solve");
		solveButton.addActionListener(e -> m_puzzleController.solve());
		m_debugButtonPanel.add(solveButton);
	}
	
	private void addRandomizeButton()
	{
		JButton randomizeButton = new JButton("Randomize");
		randomizeButton.addActionListener(e -> m_puzzleController.randomize());
		m_debugButtonPanel.add(randomizeButton);
	}
	
	private void addMacroButtons()
	{
		addNewMacroButton();
	}
	
	private void addNewMacroButton()
	{
		JButton newMacroButton = new JButton("New Macro");
		newMacroButton.addActionListener(e -> buildNewMacroFrame());
		m_macroButtonPanel.add(newMacroButton);
	}
	
	private void buildNewMacroFrame()
	{
		// Overall macro creation frame
		JFrame selectFrame = new JFrame();

		// Data model to store the macro into
		DefaultListModel<String> actionListModel = new DefaultListModel<String>();

		// Panel for color selection buttons
		JPanel colorPanel = new JPanel();
		for (Permutation permutation : m_puzzleData.getPermutationList())
			for (boolean inverted : new boolean[] { false, true })
			{
				// Include both + and - directions
				String sign = inverted? "-" : "+";
				String colorName = permutation.getColorName().getName();
				String buttonLabel = sign + colorName;
				JButton colorButton = new JButton(buttonLabel);

				colorButton.addActionListener(e -> actionListModel
				        .addElement(((JButton)e.getSource()).getText()));
				colorPanel.add(colorButton);
			}
		selectFrame.add(colorPanel, BorderLayout.NORTH);

		// The GUI element for the macro list
		JList<String> actionList = new JList<String>(actionListModel);
		JScrollPane scrollPane = new JScrollPane(actionList);
		scrollPane.setPreferredSize(new Dimension(100, 600));
		selectFrame.add(scrollPane, BorderLayout.SOUTH);
		
		// Name of the macro
		JTextField nameInput = new JTextField("macroNameHere");
		selectFrame.add(nameInput, BorderLayout.WEST);

		// Control buttons for the macro
		JPanel controlPanel = new JPanel();
		JButton saveButton = new JButton("save");
		saveButton.addActionListener(e -> m_puzzleController
		                             .saveMacro(this, selectFrame, nameInput.getText(),
		                                        actionListModel));
		controlPanel.add(saveButton);
		selectFrame.add(controlPanel, BorderLayout.EAST);

		// Publish the frame
		selectFrame.setVisible(true);
		selectFrame.pack();
	}

	public void addPermutationsFromData()
	{
		for (Permutation permutation : m_puzzleData.getPermutationList())
			addPermutation(permutation);
	}
	
	public void addPermutation(Permutation permutation)
	{
		final int permutationCount = m_puzzleData.getPermutationListSize();
		m_puzzleData.addPermutation(permutation);
		addPermutationButton(permutation, "+", false, permutationCount);
		addPermutationButton(permutation, "-", true, permutationCount);
	}

	private void addPermutationButton(Permutation permutation, String sign,
	                                  boolean inverted, int index)
	{
		String buttonLabel = sign + permutation.getColorName().getName();
		JButton permutationButton = new JButton(buttonLabel);
		permutationButton.addActionListener(e -> m_puzzleController
		        .activatePermutation(index, inverted));
		m_permutationButtonPanel.add(permutationButton);
		repaint();
	}

	public void addMacroButton(String macroName, MacroAction macroAction,
	                           String sign, boolean inverted)
	{
		JButton macroButton = new JButton(sign + macroName);
		macroButton.addActionListener(e -> macroAction.execute(m_puzzleData,
		                                                       inverted));
		m_permutationButtonPanel.add(macroButton);
		repaint();
	}
	
	@Override
	public void paint(Graphics g)
	{
		super.paint(g);
		Graphics2D g2d = (Graphics2D)g;
		
		for (Permutation permutation : m_puzzleData.getPermutationList())
			permutation.paint(g2d, m_puzzleData.getSlotList());
		
		for (Slot slot : m_puzzleData.getSlotList())
			slot.paint(g2d);
		
		for (Sticker sticker : m_puzzleData.getStickerList())
			sticker.paint(g2d);
	}
}
