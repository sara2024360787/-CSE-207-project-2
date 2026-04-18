#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

struct Flight {
    int node;
    int cost;
    int time;
};

void foodMenu() {
    int classChoice;
    cout << "\nSelect Class:\n";
    cout << "1. Business Class\n";
    cout << "2. Economy Class\n";
    cout << "Enter choice: ";
    cin >> classChoice;

    cout << "\n--- Food Menu ---\n";

    if (classChoice == 1) {
        cout << "\n*** Business Class Menu ***\n";

        cout << "\n1. Veg:\n a. Paneer Butter Masala\n b. Veg Biryani\n c. Mixed Vegetables\n";
        cout << "\n2. Non-Veg:\n a. Chicken Roast\n b. Grilled Fish\n c. Mutton Curry\n";
        cout << "\n3. Special Meals:\n a. Vegan Meal\n b. Gluten-Free Meal\n c. Diabetic Meal\n";
        cout << "\n4. Snacks:\n a. Cheese Platter\n b. Fruit Bowl\n c. Nuts Mix\n";
        cout << "\n5. Meals:\n a. Premium Thali\n b. Continental Meal\n c. Asian Cuisine\n";
        cout << "\n6. Beverages:\n a. Fresh Juice\n b. Soft Drinks\n c. Coffee/Tea\n";
    }
    else if (classChoice == 2) {
        cout << "\n*** Economy Class Menu ***\n";

        cout << "\n1. Veg:\n a. Veg Fried Rice\n b. Dal & Rice\n c. Vegetable Curry\n";
        cout << "\n2. Non-Veg:\n a. Chicken Curry\n b. Fried Chicken\n c. Egg Curry\n";
        cout << "\n3. Special Meals:\n a. Light Meal\n b. Low-Calorie Meal\n c. Kids Meal\n";
        cout << "\n4. Snacks:\n a. Biscuits\n b. Chips\n c. Sandwich\n";
        cout << "\n5. Meals:\n a. Standard Meal\n b. Rice Combo\n c. Noodles\n";
        cout << "\n6. Beverages:\n a. Water\n b. Soft Drinks\n c. Tea/Coffee\n";
    }
    else {
        cout << "Invalid choice!\n";
    }
}

class Graph {
    int V;
    vector<vector<Flight>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int cost, int time) {
        adj[u].push_back({v, cost, time});
        adj[v].push_back({u, cost, time});
    }

    void display() {
        cout << "\nRoute Map:\n";
        for (int i = 0; i < V; i++) {
            cout << "Airport " << i << " -> ";
            for (auto x : adj[i]) {
                cout << "(" << x.node 
                     << ", cost=" << x.cost 
                     << ", time=" << x.time << ") ";
            }
            cout << endl;
        }
    }

    void dijkstra(int src, int dest, int maxTime, int du, int dv) {

        vector<int> dist(V, INT_MAX);
        vector<int> timeTaken(V, INT_MAX);
        vector<int> parent(V, -1);

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        dist[src] = 0;
        timeTaken[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto x : adj[u]) {
                int v = x.node;

                if ((u == du && v == dv) || (u == dv && v == du))
                    continue;

                int newCost = dist[u] + x.cost;
                int newTime = timeTaken[u] + x.time;

                if (newCost < dist[v] && newTime <= maxTime) {
                    dist[v] = newCost;
                    timeTaken[v] = newTime;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[dest] == INT_MAX) {
            cout << "No route found within time limit!\n";
            return;
        }

        cout << "\nShortest Cost: " << dist[dest] << endl;
        cout << "Total Time: " << timeTaken[dest] << endl;

        vector<int> path;
        for (int v = dest; v != -1; v = parent[v]) {
            path.push_back(v);
        }

        cout << "Route: ";
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i];
            if (i != 0) cout << " -> ";
        }
        cout << endl;

        foodMenu();
    }
};

int main() {
    int V;
    cout << "Enter number of airports: ";
    cin >> V;

    Graph g(V);

    int choice;
    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1. Add Flight\n";
        cout << "2. Display Route Map\n";
        cout << "3. Find Route (with delay & food)\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int u, v, cost, time;
            cout << "Enter source, destination, cost, time: ";
            cin >> u >> v >> cost >> time;
            g.addEdge(u, v, cost, time);
        }
        else if (choice == 2) {
            g.display();
        }
        else if (choice == 3) {
            int src, dest, maxTime, du, dv;
            int delayChoice;

            cout << "Enter source and destination: ";
            cin >> src >> dest;

            cout << "Enter maximum preferred travel time: ";
            cin >> maxTime;

            cout << "Is there any delayed route? (1 = Yes, 0 = No): ";
            cin >> delayChoice;

            if (delayChoice == 1) {
                cout << "Enter delayed route (u v): ";
                cin >> du >> dv;

                cout << "\nFlight delay detected!\n";
                cout << "Enter NEW preferred maximum travel time: ";
                cin >> maxTime;
            } else {
                du = -1;
                dv = -1;
            }

            g.dijkstra(src, dest, maxTime, du, dv);
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
