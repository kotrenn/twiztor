package permgame;

import java.awt.Color;
import java.awt.Graphics2D;

public class Sticker
{
	private ColorName         m_colorName;
	private Slot              m_slot;
	private Slot              m_previousSlot;
	private long              m_previousTime;
	private static final long sf_MOVE_DURATION = 1200000000; // 1.2 seconds

	public Sticker(ColorName colorName)
	{
		m_colorName = colorName;
		m_slot = null;
		m_previousSlot = null;
		m_previousTime = 0;
	}
	
	public void setSlot(Slot slot)
	{
		m_previousSlot = m_slot;
		m_previousTime = System.nanoTime();
		m_slot = slot;
	}
	
	public ColorName getColorName()
	{
		return m_colorName;
	}

	public void paint(Graphics2D g2d)
	{
		
		Color color = ColorMap.getColor(m_colorName);
		g2d.setColor(color);

		if (color != Color.BLACK)
		{
			double size = 20;
			double size2 = size / 2;
			double size175 = 1.2 * size2;
			
			double x1 = m_slot.getX() - size2 + (size2 - size175 / 2);
			double y1 = m_slot.getY() - size2 + (size2 - size175 / 2);
			double interpX = x1;
			double interpY = y1;
			if (m_previousSlot != null)
			{
				double x0 = m_previousSlot.getX() - size2
						+ (size2 - size175 / 2);
				double y0 = m_previousSlot.getY() - size2
						+ (size2 - size175 / 2);
				long currentTime = System.nanoTime();
				long diffTime = currentTime - m_previousTime;
				if (diffTime > Sticker.sf_MOVE_DURATION)
				    diffTime = Sticker.sf_MOVE_DURATION;
				double percentage = (double)diffTime
				                    / (double)Sticker.sf_MOVE_DURATION;
				interpX = x0 + (int)(percentage * (x1 - x0));
				interpY = y0 + (int)(percentage * (y1 - y0));
			}
			g2d.fillRect((int)interpX, (int)interpY, (int)size175, (int)size175);
		}
		else
			g2d.drawString(m_colorName.getName(), (int)m_slot.getX(),
			               (int)m_slot.getY());
	}
}
