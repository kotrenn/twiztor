package permgame;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class PuzzleActionStorage
{
	private Map<String, PuzzleAction> m_puzzleActionMap;

	public PuzzleActionStorage()
	{
		m_puzzleActionMap = new HashMap<String, PuzzleAction>();
	}
	
	public void addPuzzleAction(String actionName, PuzzleAction puzzleAction)
	{
		m_puzzleActionMap.put(actionName, puzzleAction);
	}
	
	public PuzzleAction getActionByName(String actionName)
	{
		return m_puzzleActionMap.get(actionName);
	}

	public PuzzleAction getRandomAction(Random random)
	{
		// String[] nameArray = (String[])m_puzzleActionMap.keySet().toArray();
		String[] nameArray = new String[m_puzzleActionMap.size()];
		int count = 0;
		for (String key : m_puzzleActionMap.keySet())
			nameArray[count++] = key;
		return m_puzzleActionMap.get(random.nextInt() % nameArray.length);
	}
}
