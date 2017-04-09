package permgame;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.WindowEvent;
import java.util.Arrays;
import java.util.Random;

import javax.swing.DefaultListModel;
import javax.swing.JFrame;

public class PuzzleController implements KeyListener
{
	private PuzzleData          m_puzzleData;
	private PuzzleActionStorage m_puzzleActionStorage;

	public PuzzleController(PuzzleData puzzleData)
	{
		m_puzzleData = puzzleData;
		m_puzzleActionStorage = new PuzzleActionStorage();
	}

	public void activatePermutation(int index)
	{
		activatePermutation(index, false);
	}

	public void activatePermutation(int index, boolean inverted)
	{
		if (index >= m_puzzleData.getPermutationListSize()) return;

		Permutation permutation = m_puzzleData.getPermutationList().get(index);
		permutation.apply(m_puzzleData, inverted);
	}
	
	public void solve()
	{
		m_puzzleData.clearStickerList();

		for (Slot slot : m_puzzleData.getSlotList())
		{
			Sticker newSticker = new Sticker(slot.getColorName());
			newSticker.setSlot(slot);
			slot.setSticker(newSticker);
			m_puzzleData.addSticker(newSticker);
		}
	}
	
	public void randomize()
	{
		Random random = new Random();
		for (int i = 0; i < 10000; i++)
		{
			PuzzleAction randomAction = m_puzzleActionStorage
					.getRandomAction(random);
			boolean randomInverted = random.nextBoolean();
			randomAction.execute(m_puzzleData, randomInverted);
		}
	}
	
	public void saveMacro(PuzzlePanel puzzlePanel, JFrame selectFrame,
	                      String macroName,
	                      DefaultListModel<String> actionListModel)
	{
		System.out.println("Saving the following macro [" + macroName + "]:");
		for (Object actionString : Arrays.asList(actionListModel.toArray()))
			System.out.println(actionString);
		MacroAction macroAction = new MacroAction();
		for (Object actionNameObject : actionListModel.toArray())
		{
			String rawActionName = (String)actionNameObject;
			String colorName = rawActionName.substring(1);
			PermutationAction basicAction = new PermutationAction();
			for (Permutation permutation : m_puzzleData.getPermutationList())
				if (permutation.getColorName().getName().equals(colorName))
				    basicAction.setPermutation(permutation);
			if (rawActionName.charAt(0) == '+') basicAction.setInverted(false);
			if (rawActionName.charAt(0) == '-') basicAction.setInverted(true);
			macroAction.addAction(basicAction);
		}
		m_puzzleActionStorage.addPuzzleAction(macroName, macroAction);
		addMacro(puzzlePanel, macroName, macroAction);

		selectFrame.dispatchEvent(new WindowEvent(selectFrame,
		                                          WindowEvent.WINDOW_CLOSING));
	}
	
	public void addMacro(PuzzlePanel puzzlePanel, String macroName,
	                     MacroAction macroAction)
	{
		m_puzzleActionStorage.addPuzzleAction(macroName, macroAction);
		puzzlePanel.addMacroButton(macroName, macroAction, "+", false);
		puzzlePanel.addMacroButton(macroName, macroAction, "-", true);
	}

	@Override
	public void keyPressed(KeyEvent e)
	{
		if (e.getKeyCode() == KeyEvent.VK_1) activatePermutation(0);
		if (e.getKeyCode() == KeyEvent.VK_2) activatePermutation(1);
		if (e.getKeyCode() == KeyEvent.VK_3) activatePermutation(2);
		if (e.getKeyCode() == KeyEvent.VK_4) activatePermutation(3);
		if (e.getKeyCode() == KeyEvent.VK_5) activatePermutation(4);
		if (e.getKeyCode() == KeyEvent.VK_6) activatePermutation(5);
		if (e.getKeyCode() == KeyEvent.VK_7) activatePermutation(6);
		if (e.getKeyCode() == KeyEvent.VK_8) activatePermutation(7);
		if (e.getKeyCode() == KeyEvent.VK_9) activatePermutation(8);
		if (e.getKeyCode() == KeyEvent.VK_0) activatePermutation(9);
	}

	@Override
	public void keyReleased(KeyEvent arg0)
	{
		// TODO Auto-generated method stub

	}

	@Override
	public void keyTyped(KeyEvent arg0)
	{
		// TODO Auto-generated method stub

	}
}
