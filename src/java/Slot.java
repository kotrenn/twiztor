package permgame;

import java.awt.Color;
import java.awt.Graphics2D;

public class Slot
{
	private Sticker   m_sticker;
	private double    m_x;
	private double    m_y;
	private ColorName m_colorName;
	private int       m_scale;

	public Slot(Sticker sticker, double x, double y, ColorName colorName)
	{
		m_sticker = sticker;
		m_x = x;
		m_y = y;
		m_colorName = colorName;
		m_scale = 30;
	}

	public void setSticker(Sticker sticker)
	{
		m_sticker = sticker;
	}
	
	public Sticker getSticker()
	{
		return m_sticker;
	}

	public double getX()
	{
		return m_x * m_scale;
	}
	
	public double getY()
	{
		return m_y * m_scale;
	}
	
	public ColorName getColorName()
	{
		return m_colorName;
	}
	
	public void paint(Graphics2D g2d)
	{
		int size = 20;
		int size2 = size / 2;
		
		double x = getX() - size2;
		double y = getY() - size2;
		
		Color color = ColorMap.getColor(m_colorName);
		g2d.setColor(color);
		g2d.drawRect((int)x, (int)y, size, size);
		g2d.drawRect((int)(x + 1), (int)(y + 1), size - 2, size - 2);
	}
}
