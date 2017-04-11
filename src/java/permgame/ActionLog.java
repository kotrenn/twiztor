package permgame;

import java.util.ArrayList;

public class ActionLog
{
	private PuzzleData              m_puzzleData;
	private ArrayList<PuzzleAction> m_actionList;
	private int                     m_currentIndex;

	public ActionLog(PuzzleData puzzleData)
	{
		m_puzzleData = puzzleData;
		m_actionList = new ArrayList<PuzzleAction>();
		m_currentIndex = 0;
	}
	
	public void execute(PuzzleAction puzzleAction)
	{
		puzzleAction.execute(m_puzzleData, false);
		while (m_currentIndex + 1 < m_actionList.size())
			m_actionList.remove(m_currentIndex + 1);
		m_actionList.add(puzzleAction);
		m_currentIndex++;
	}

	public void undo()
	{
		if (m_currentIndex < 1) return;
		PuzzleAction previousAction = m_actionList.get(m_currentIndex - 1);
		previousAction.execute(m_puzzleData, true);
		m_currentIndex--;
	}

	public void redo()
	{
		if (m_currentIndex + 1 >= m_actionList.size()) return;
		PuzzleAction nextAction = m_actionList.get(m_currentIndex);
		nextAction.execute(m_puzzleData, false);
		m_currentIndex++;
	}
}
