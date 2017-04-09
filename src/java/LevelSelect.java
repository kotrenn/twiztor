package permgame;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.SwingUtilities;

public class LevelSelect implements ActionListener
{
	private static JFrame s_selectionFrame;
	JList<String>         s_puzzleList;

	public LevelSelect()
	{
		File puzzleDirectory = new File("puzzles");
		File[] puzzleFileList = puzzleDirectory.listFiles();
		DefaultListModel<String> puzzleListModel = new DefaultListModel<String>();
		for (File puzzleFile : puzzleFileList)
			if (puzzleFile.isFile())
			    if (puzzleFile.getName().contains(".puz"))
			        puzzleListModel.addElement(puzzleFile.getName());
		
		LevelSelect.s_selectionFrame = new JFrame("Select a puzzle");
		LevelSelect.s_selectionFrame
		.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		s_puzzleList = new JList<String>(puzzleListModel);
		s_puzzleList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		s_puzzleList.setSelectedIndex(0);
		JScrollPane scrollPane = new JScrollPane(s_puzzleList);
		scrollPane.setPreferredSize(new Dimension(100, 600));
		LevelSelect.s_selectionFrame.add(scrollPane);

		JButton selectButton = new JButton("Play!");
		selectButton.addActionListener(this);
		LevelSelect.s_selectionFrame.add(selectButton, BorderLayout.SOUTH);

		LevelSelect.s_selectionFrame.pack();
		LevelSelect.s_selectionFrame.setVisible(true);
	}
	
	@Override
	public void actionPerformed(ActionEvent e)
	{
		String puzzleName = s_puzzleList.getSelectedValue();
		System.out.println("The puzzle selected is <" + puzzleName + ">");
		SwingUtilities.invokeLater(() -> PermGameMain
		        .main(new String[] { puzzleName }));
	}

	public static void main(String[] args)
	{
		new LevelSelect();
	}
}
