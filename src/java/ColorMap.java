package permgame;

import java.awt.Color;
import java.util.HashMap;
import java.util.Map;

public class ColorMap
{
	private static Map<String, Color> s_colorMap;
	private static final Color        sf_DEFAULT_COLOR = Color.BLACK;
	
	public static Color getColor(ColorName colorName)
	{
		String colorString = colorName.getName();
		if (ColorMap.s_colorMap == null) ColorMap.buildColorMap();
		if (!ColorMap.s_colorMap.containsKey(colorString))
			return ColorMap.sf_DEFAULT_COLOR;
		return ColorMap.s_colorMap.get(colorString);
	}
	
	private static void buildColorMap()
	{
		ColorMap.s_colorMap = new HashMap<String, Color>();
		ColorMap.s_colorMap.put("red", Color.RED);
		ColorMap.s_colorMap.put("orange", Color.ORANGE);
		ColorMap.s_colorMap.put("yellow", new Color(200, 200, 0));
		ColorMap.s_colorMap.put("green", Color.GREEN);
		ColorMap.s_colorMap.put("cyan", Color.CYAN);
		ColorMap.s_colorMap.put("blue", Color.BLUE);
		ColorMap.s_colorMap.put("magenta", Color.MAGENTA);
		ColorMap.s_colorMap.put("purple", Color.MAGENTA.darker());
		ColorMap.s_colorMap.put("gray", Color.GRAY);
		ColorMap.s_colorMap.put("grey", Color.GRAY);
		ColorMap.s_colorMap.put("black", Color.BLACK);
		ColorMap.s_colorMap.put("white", Color.WHITE);
		ColorMap.s_colorMap.put("darkgreen", Color.GREEN.darker());
		ColorMap.s_colorMap.put("darkred", Color.RED.darker());
		ColorMap.s_colorMap.put("cornflowerblue", new Color(100, 149, 237));
		ColorMap.s_colorMap.put("brown", new Color(165, 42, 42));
		ColorMap.s_colorMap.put("darkseagreen", new Color(143, 188, 143));
		ColorMap.s_colorMap.put("darkorchid", new Color(153, 50, 204));
		ColorMap.s_colorMap.put("yellowgreen", new Color(154, 205, 50));
		ColorMap.s_colorMap.put("turquoise4", new Color(0, 134, 139));
		ColorMap.s_colorMap.put("violet", new Color(238, 130, 238));
		ColorMap.s_colorMap.put("violetred", new Color(208, 32, 144));
		ColorMap.s_colorMap.put("violetred4", new Color(139, 34, 82));
	}
}
