package permgame;

import java.awt.Color;
import java.awt.Graphics2D;
import java.util.ArrayList;
import java.util.List;

public class Permutation
{
	private int[]     m_mapping;
	private String[]  m_labels;
	private ColorName m_colorName;
	private int       m_index;

	public Permutation(int n, ColorName colorName, int index)
	{
		m_mapping = new int[n];
		m_labels = new String[n];
		m_colorName = colorName;
		m_index = index;

		for (int i = 0; i < n; ++i)
		{
			m_mapping[i] = i;
			m_labels[i] = Integer.toString(i + 1);
		}
	}

	public ColorName getColorName()
	{
		return m_colorName;
	}

	public void setCycles(int[][] cycles)
	{
		for (int[] cycle : cycles)
			for (int i = 0; i < cycle.length; i++)
			{
				int j = (i + 1) % cycle.length;
				m_mapping[cycle[i]] = cycle[j];
			}
	}

	public Permutation multiply(Permutation rhs)
	{
		if (m_mapping.length != rhs.m_mapping.length) return null;

		Permutation ret = new Permutation(m_mapping.length, m_colorName,
		                                  m_index);
		for (int i = 0; i < m_mapping.length; i++)
			ret.m_mapping[i] = m_mapping[rhs.m_mapping[i]];

		return ret;
	}

	public void apply(PuzzleData puzzleData, boolean inverted)
	{
		// Previous lists
		List<Sticker> stickerList = puzzleData.getStickerList();
		List<Slot> slotList = puzzleData.getSlotList();

		// Buffer list to construct the new list without destroying the old list
		ArrayList<Sticker> newStickerList = new ArrayList<Sticker>();
		newStickerList.addAll(stickerList);
		
		// Reorder newStickerList as necessary
		for (int i = 0; i < m_mapping.length; i++)
		{
			int j = m_mapping[i];
			if (inverted)
			{
				Sticker sticker = stickerList.get(j);
				newStickerList.set(i, sticker);
				sticker.setSlot(slotList.get(i));
			}
			else
			{
				Sticker sticker = stickerList.get(i);
				newStickerList.set(j, sticker);
				sticker.setSlot(slotList.get(j));
			}
		}
		
		// Copy the results over into puzzleData
		puzzleData.setStickerList(newStickerList);
	}

	@Override
	public Permutation clone()
	{
		Permutation ret = new Permutation(m_mapping.length, m_colorName,
		                                  m_index);

		for (int i = 0; i < m_mapping.length; i++)
		{
			ret.m_mapping[i] = m_mapping[i];
			ret.m_labels[i] = m_labels[i];
		}

		return ret;
	}

	public void paint(Graphics2D g2d, List<Slot> slotList)
	{
		for (int i = 0; i < m_mapping.length; i++)
		{
			Slot curSlot = slotList.get(i);
			Slot nextSlot = slotList.get(m_mapping[i]);
			
			double x0 = curSlot.getX();
			double y0 = curSlot.getY();
			double x1 = nextSlot.getX();
			double y1 = nextSlot.getY();
			
			double scale = 5;
			x0 += m_index * scale;
			y0 += m_index * scale;
			x1 += m_index * scale;
			y1 += m_index * scale;

			Color color = ColorMap.getColor(m_colorName);
			g2d.setColor(color);
			g2d.drawLine((int)x0, (int)y0, (int)x1, (int)y1);
		}
	}
}
