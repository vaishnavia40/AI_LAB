import java.util.*;

// Node class representing a node in the graph
class Node implements Comparable<Node> {
    int id;            // Identifier of the node
    int cost;          // Cost to reach this node from the start node
    int heuristic;     // Heuristic value of the node (estimated cost from this node to the goal node)
    Node parent;       // Parent node in the shortest path

    // Constructor to initialize a Node object
    public Node(int id, int cost, int heuristic, Node parent) {
        this.id = id;
        this.cost = cost;
        this.heuristic = heuristic;
        this.parent = parent;
    }

    // compareTo method to compare nodes based on their total cost (cost + heuristic)
    @Override
    public int compareTo(Node other) {
        return Integer.compare(cost + heuristic, other.cost + other.heuristic);
    }
}

public class AStarShortestPath {
    // Method to find the shortest path using A* algorithm
    public static List<Integer> findShortestPath(int[][] graph, int start, int goal, int[] heuristic) {
        int numNodes = graph.length;
        boolean[] visited = new boolean[numNodes]; // Array to keep track of visited nodes
        int[] costs = new int[numNodes];           // Array to store cost of reaching each node from start
        Arrays.fill(costs, Integer.MAX_VALUE);     // Initialize costs to infinity
        costs[start] = 0;                          // Set cost of start node to 0

        // Priority queue to store nodes based on their total cost (cost + heuristic)
        PriorityQueue<Node> queue = new PriorityQueue<>();
        queue.add(new Node(start, 0, heuristic[start], null)); // Add start node to queue

        // Main loop of A* algorithm
        while (!queue.isEmpty()) {
            Node current = queue.poll(); // Remove node with lowest total cost from queue
            int currentNode = current.id; // Get identifier of current node

            // If current node is the goal node, reconstruct and return the shortest path
            if (currentNode == goal) {
                List<Integer> path = new ArrayList<>();
                while (current != null) {
                    path.add(current.id);
                    current = current.parent;
                }
                Collections.reverse(path); // Reverse the path to get correct order
                return path;
            }

            // Mark current node as visited
            if (visited[currentNode]) {
                continue;
            }
            visited[currentNode] = true;

            // Iterate over neighbors of current node
            for (int neighbor = 0; neighbor < numNodes; neighbor++) {
                // If neighbor is connected and not visited
                if (graph[currentNode][neighbor] != 0 && !visited[neighbor]) {
                    int newCost = costs[currentNode] + graph[currentNode][neighbor]; // Calculate new cost
                    // If new cost is less than current cost to reach neighbor
                    if (newCost < costs[neighbor]) {
                        costs[neighbor] = newCost; // Update cost
                        // Create new neighbor node and add it to queue
                        Node neighborNode = new Node(neighbor, newCost, heuristic[neighbor], current);
                        queue.add(neighborNode);
                    }
                }
            }
        }

        return null; // If no path is found, return null
    }

    // Main method
    public static void main(String[] args) {
        // Define example weighted graph represented by an adjacency matrix
        int[][] graph = {
            {0, 2, 0, 1, 0},
            {2, 0, 3, 0, 0},
            {0, 3, 0, 0, 4},
            {1, 0, 0, 0, 2},
            {0, 0, 4, 2, 0}
        };
        int start = 0;               // Start node
        int goal = 4;                // Goal node
        int[] heuristic = {6, 3, 2, 4, 0}; // Heuristic values for each node

        // Find shortest path using A* algorithm
        List<Integer> path = findShortestPath(graph, start, goal, heuristic);

        // Print the shortest path or "No path found" if no path exists
        if (path != null) {
            System.out.println("Shortest path: " + path);
        } else {
            System.out.println("No path found");
        }
    }
}
