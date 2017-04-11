package permgame;

import java.util.ArrayList;
import java.util.Collections;

public class MacroAction implements PuzzleAction
{
	private ArrayList<PuzzleAction> m_actionList;
	private boolean                 m_inverted;

	public MacroAction()
	{
		m_actionList = new ArrayList<PuzzleAction>();
		m_inverted = false;
	}

	@Override
	public void setInverted(boolean inverted)
	{
		m_inverted = inverted;
	}

	public void addAction(PuzzleAction action)
	{
		m_actionList.add(action);
	}

	@Override
	public PuzzleAction cloneAction()
	{
		MacroAction cloneAction = new MacroAction();
		cloneAction.setInverted(m_inverted);
		for (PuzzleAction puzzleAction : m_actionList)
			cloneAction.addAction(puzzleAction);
		return cloneAction;
	}

	@Override
	public void execute(PuzzleData puzzleData, boolean inverted)
	{
		// Make a copy to potentially reverse
		ArrayList<PuzzleAction> tempActionList = new ArrayList<PuzzleAction>(
				m_actionList);
		if (inverted) Collections.reverse(tempActionList);
		for (PuzzleAction puzzleAction : tempActionList)
			puzzleAction.execute(puzzleData, inverted);
	}
}
