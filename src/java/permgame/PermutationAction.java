package permgame;


public class PermutationAction implements PuzzleAction
{
	private Permutation m_permutation;
	private boolean     m_inverted;
	
	public PermutationAction()
	{
		m_permutation = null;
		m_inverted = false;
	}
	
	public void setPermutation(Permutation permutation)
	{
		m_permutation = permutation;
	}

	@Override
	public void setInverted(boolean inverted)
	{
		m_inverted = inverted;
	}
	
	/*
	 * (non-Javadoc)
	 *
	 * @see permgame.PuzzleAction#cloneAction()
	 */
	@Override
	public PuzzleAction cloneAction()
	{
		PermutationAction cloneAction = new PermutationAction();
		cloneAction.m_permutation = m_permutation.clone();
		cloneAction.m_inverted = m_inverted;
		return cloneAction;
	}
	
	/*
	 * (non-Javadoc)
	 *
	 * @see permgame.PuzzleAction#execute(java.util.ArrayList,
	 * java.util.ArrayList)
	 */
	@Override
	public void execute(PuzzleData puzzleData, boolean inverted)
	{
		if (m_permutation == null)
			reportError("No permutation applied to BasicAction");
		else
			m_permutation.apply(puzzleData, inverted);
	}

	private void reportError(String message)
	{
		System.err.println("Error: " + message);
	}
}
