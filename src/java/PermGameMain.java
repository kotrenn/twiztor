package permgame;

public class PermGameMain implements Runnable
{
	private static PermGameFrame s_frame;

	@Override
	public void run()
	{
		int sleepDelay = 10;
		// sleepDelay = 100;
		while (true)
			try
			{
				PermGameMain.s_frame.repaint();
				Thread.sleep(sleepDelay);
			}
			catch (InterruptedException e)
			{
				
			}
	}

	public static void main(String[] args)
	{
		if (args.length > 0)
			PermGameMain.s_frame = new PermGameFrame(args[0]);
		else
			PermGameMain.s_frame = new PermGameFrame();
		// GameData gameData = new GameData();
		javax.swing.SwingUtilities.invokeLater(() -> PermGameMain.s_frame
		                                       .createAndShowGUI());
		(new Thread(new PermGameMain())).start();
	}
}
