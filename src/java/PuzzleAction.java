package permgame;


public interface PuzzleAction
{
	public abstract void setInverted(boolean inverted);
	
	public abstract PuzzleAction cloneAction();

	public abstract void execute(PuzzleData puzzleData, boolean inverted);

}
