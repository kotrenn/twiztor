package permgame;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

public class PuzzleData
{
	private List<Permutation> m_permutationList;
	private List<Slot>        m_slotList;
	private List<Sticker>     m_stickerList;
	
	public PuzzleData()
	{
		m_permutationList = new CopyOnWriteArrayList<Permutation>();
		m_slotList = new CopyOnWriteArrayList<Slot>();
		m_stickerList = new CopyOnWriteArrayList<Sticker>();
	}
	
	public void addPermutation(Permutation permutation)
	{
		m_permutationList.add(permutation);
	}

	public void addSlot(Slot slot)
	{
		m_slotList.add(slot);
	}

	public void addSticker(Sticker sticker)
	{
		m_stickerList.add(sticker);
	}

	public void clearSlotList()
	{
		m_slotList.clear();
	}

	public void clearStickerList()
	{
		m_stickerList.clear();
	}

	public List<Permutation> getPermutationList()
	{
		return m_permutationList;
	}
	
	public List<Slot> getSlotList()
	{
		return m_slotList;
	}
	
	public List<Sticker> getStickerList()
	{
		return m_stickerList;
	}

	public int getPermutationListSize()
	{
		return m_permutationList.size();
	}

	public int getSlotListSize()
	{
		return m_slotList.size();
	}

	public int getStickerListSize()
	{
		return m_stickerList.size();
	}

	public void setPermutationList(ArrayList<Permutation> permutationList)
	{
		m_permutationList = new CopyOnWriteArrayList<Permutation>(
				permutationList);
	}

	public void setSlotList(ArrayList<Slot> slotList)
	{
		m_slotList = new CopyOnWriteArrayList<Slot>(slotList);
	}
	
	public void setStickerList(ArrayList<Sticker> stickerList)
	{
		m_stickerList = new CopyOnWriteArrayList<Sticker>(stickerList);
	}

	public void makeBasicLevel()
	{
		String[] colorStrings = { "red", "orange", "yellow", "green", "cyan",
		                          "blue", "magenta", "purple" };
		ColorName[] colors = new ColorName[colorStrings.length];
		for (int i = 0; i < colors.length; i++)
			colors[i] = new ColorName(colorStrings[i]);
		
		Slot slot0 = new Slot(new Sticker(colors[0]), 2, 2, colors[0]);
		Slot slot1 = new Slot(new Sticker(colors[1]), 1, 3, colors[1]);
		Slot slot2 = new Slot(new Sticker(colors[2]), 1, 4, colors[2]);
		Slot slot3 = new Slot(new Sticker(colors[3]), 2, 5, colors[3]);
		Slot slot4 = new Slot(new Sticker(colors[4]), 3, 5, colors[4]);
		Slot slot5 = new Slot(new Sticker(colors[5]), 4, 4, colors[5]);
		Slot slot6 = new Slot(new Sticker(colors[6]), 4, 3, colors[6]);
		Slot slot7 = new Slot(new Sticker(colors[7]), 3, 2, colors[7]);

		Slot[] slots = new Slot[] { slot0, slot1, slot2, slot3, slot4, slot5,
		                            slot6, slot7 };
		for (Slot slot : slots)
		{
			addSlot(slot);
			Sticker slotSticker = slot.getSticker();
			slotSticker.setSlot(slot);
			addSticker(slotSticker);
		}

		Permutation p0 = new Permutation(8, new ColorName("red"), 0);
		Permutation p1 = new Permutation(8, new ColorName("green"), 1);
		Permutation p2 = new Permutation(8, new ColorName("blue"), 2);
		
		p0.setCycles(new int[][] { { 0, 1, 2, 3 }, { 4, 5, 6, 7 } });
		p1.setCycles(new int[][] { { 0, 1 }, { 2, 3 }, { 4, 5 }, { 6, 7 } });
		p2.setCycles(new int[][] { { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 } });

		addPermutation(p0);
		addPermutation(p1);
		addPermutation(p2);
	}
}
