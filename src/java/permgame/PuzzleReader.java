package permgame;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;

public class PuzzleReader
{
	public PuzzleReader()
	{
	}

	public void readFromFile(String filename, PuzzleData puzzleData)
	{
		Path path = Paths.get(filename);
		Charset charset = Charset.forName("US-ASCII");
		try (BufferedReader reader = Files.newBufferedReader(path, charset))
		{
			ArrayList<String> nodeList = new ArrayList<String>();
			int numPermutations = 0;
			String rawLine;
			while ((rawLine = reader.readLine()) != null)
			{
				System.out.println("rawLine = " + rawLine);
				String header = rawLine.split(" ")[0];
				if (header.equals("node"))
					readNode(puzzleData, nodeList, rawLine);
				else if (header.equals("permutation"))
					numPermutations = readPermutation(puzzleData, nodeList,
					                                  numPermutations, rawLine);
				
			}
			reader.close();
		}
		catch (IOException e)
		{
			System.err.format("IOException: %s%n", e);
		}
	}

	private void readNode(PuzzleData puzzleData, ArrayList<String> nodeList,
	                      String rawLine)
	{
		String[] vals = rawLine.split(" ");
		String nodeName = vals[1];
		String nodeColor = vals[2];
		double nodeX = Double.valueOf(vals[3]);
		double nodeY = Double.valueOf(vals[4]);
		String nodeSticker = nodeColor;
		Sticker newSticker = new Sticker(new ColorName(nodeSticker));
		Slot newSlot = new Slot(newSticker, nodeX, nodeY,
		                        new ColorName(nodeColor));
		newSticker.setSlot(newSlot);
		puzzleData.addSlot(newSlot);
		puzzleData.addSticker(newSticker);
		nodeList.add(nodeName);
		System.out.println("Added node " + nodeName + ": " + nodeColor + " "
				+ nodeX + " " + nodeY + " " + nodeSticker);
	}

	private int readPermutation(PuzzleData puzzleData,
	                            ArrayList<String> nodeList,
	                            int numPermutations, String rawLine)
	{
		String[] vals = rawLine.split(" ", 3);
		String permutationColor = vals[1];
		ColorName permutationColorName = new ColorName(permutationColor);
		// now build a cycle
		String cycleList = vals[2];
		System.out.println("Found cycle list: " + vals[2]);
		int[][] cycles = buildCycleList(cycleList, nodeList);
		int numSlots = nodeList.size();
		Permutation newPermutation = new Permutation(numSlots,
		                                             permutationColorName,
		                                             numPermutations);
		numPermutations++;
		newPermutation.setCycles(cycles);
		puzzleData.addPermutation(newPermutation);
		System.out.println("Added permutation: " + permutationColor);
		return numPermutations;
	}
	
	private int[][] buildCycleList(String cycleInput, ArrayList<String> nodeList)
	{
		ArrayList<int[]> cycleList = new ArrayList<int[]>();
		ArrayList<Integer> currentCycle = new ArrayList<Integer>();
		int bracketCount = 0;
		for (int i = 0; i < cycleInput.length(); i++)
		{
			char curChar = cycleInput.charAt(i);
			if (curChar == '[')
			{
				System.out.println("Found [ @" + i);
				bracketCount++;
				if (bracketCount > 1) currentCycle = new ArrayList<Integer>();
			}
			else if (curChar == ']')
			{
				System.out.println("Found ]");
				bracketCount--;
				if (bracketCount > 0)
				{
					int[] cycleArray = currentCycle.stream().mapToInt(j -> j)
							.toArray();
					cycleList.add(cycleArray);
					currentCycle = null;
					String cycleStr = "";
					for (int val : cycleArray)
						cycleStr += Integer.toString(val) + " ";
					System.out.println("Added basic cycle " + cycleStr);
				}
			}
			else if (curChar != ' ' && curChar != '\n')
			{
				if (bracketCount == 1) continue;
				String currentLabel = "";
				while (cycleInput.charAt(i) != ','
						&& cycleInput.charAt(i) != ']')
				{
					currentLabel += cycleInput.charAt(i);
					i++;
				}
				int index = nodeList.indexOf(currentLabel);
				currentCycle.add(index);
				System.out.println("Added node " + currentLabel + " @" + index);
				System.out.println("i = " + i);
				System.out.println("str[i] = " + cycleInput.charAt(i));
				if (cycleInput.charAt(i) == ']') i--;
			}
		}
		return cycleList.toArray(new int[cycleList.size()][]);
	}
}
