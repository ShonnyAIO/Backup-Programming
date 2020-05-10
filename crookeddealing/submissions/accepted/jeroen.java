import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		String[] ps = in.readLine().split(" ");
		int n = Integer.valueOf(ps[0]);
		int h = Integer.valueOf(ps[1]);
		ps = in.readLine().split(" ");
		int[] v = new int[n];
		for(int i = 0; i < n; i++)
			v[i] = Integer.valueOf(ps[i]);

		// First count how much we have for each card
		Map<Integer,Integer> count = new TreeMap<Integer,Integer>();
		for(int i = 0; i < n; i++)
			count.put(v[i], count.containsKey(v[i]) ? count.get(v[i]) + 1 : 1);

		// Sort by count by swapping key and value
		TreeSet<Pair> cards = new TreeSet<Pair>();
		for(Map.Entry<Integer,Integer> e : count.entrySet())
			cards.add(new Pair(e.getValue(), e.getKey())); // sort by count

		// Greedy approach, take the cards from highest piles first
		ArrayList<List<Integer>> ret = new ArrayList<List<Integer>>();
		while(true) {
			List<Integer> hand = new ArrayList<Integer>();
			TreeSet<Pair> nextcards = new TreeSet<Pair>();

			// Keep adding new cards to our hand
			while(!cards.isEmpty() && hand.size() < h) {
				// Get cards with highest count
				Pair best = cards.pollLast();
				hand.add(best.second);
				if(--best.first > 0)
					nextcards.add(best);
			}

			// Not enough different cards, so we're done
			if(hand.size() < h) break;

			// This is a solution, so add it and continue
			ret.add(hand);
			cards.addAll(nextcards);
		}

		// Print answer
		if(ret.size() == 0)
			System.out.println("impossible");
		for(List<Integer> hand : ret) {
			for(int c : hand) System.out.print(c + " ");
			System.out.println();
		}
	}
}


// Ugh, why is this nowhere to be found in the libs
class Pair implements Comparable<Pair> {
	public int first;
	public int second;
	
	public Pair(int first, int second) {
		this.first = first;
		this.second = second;
	}

	@Override
    public boolean equals(Object other) {
		if(!(other instanceof Pair)) return false;
		Pair o = (Pair)other;
		return o.first == first && o.second == second;
	}
	
	@Override
    public int hashCode() {
		return first * 31 + second;
	}

	public int compareTo(Pair other) {
		return first != other.first
			? first - other.first
			: second - other.second;
	}
}
