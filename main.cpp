#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

struct Flight {
    int node;
    int cost;
    int travelTime;
    int departureTime;
};

// ✔ YOUR ORIGINAL FOOD MENU (UNCHANGED)
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

    void addEdge(int u, int v, int cost, int travelTime, int departureTime) {
        adj[u].push_back({v, cost, travelTime, departureTime});
        adj[v].push_back({u, cost, travelTime, departureTime});
    }

    void display() {
        cout << "\nRoute Map:\n";
        for (int i = 0; i < V; i++) {
            cout << "Airport " << i << " -> ";
            for (auto x : adj[i]) {
                cout << "(" << x.node
                     << ", cost=" << x.cost
                     << ", dep=" << x.departureTime
                     << ", time=" << x.travelTime << ") ";
            }
            cout << endl;
        }
    }

    void dijkstra(int src, int dest, int du, int dv, bool delay) {

        vector<int> dist(V, INT_MAX);
        vector<int> timeArrive(V, INT_MAX);
        vector<int> parent(V, -1);

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        dist[src] = 0;
        timeArrive[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto x : adj[u]) {
                int v = x.node;

                // delay check
                if (delay && ((u == du && v == dv) || (u == dv && v == du)))
                    continue;

                int currentTime = timeArrive[u];

                int waitTime;
                if (x.departureTime >= currentTime)
                    waitTime = x.departureTime - currentTime;
                else
                    waitTime = (24 - currentTime) + x.departureTime;

                int arrivalTime = currentTime + waitTime + x.travelTime;
                int newCost = dist[u] + x.cost;

                if (newCost < dist[v]) {
                    dist[v] = newCost;
                    timeArrive[v] = arrivalTime;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[dest] == INT_MAX) {
            cout << "No route found!\n";
            return;
        }

        cout << "\nShortest Cost: " << dist[dest];
        cout << "\nArrival Time: " << timeArrive[dest] << endl;

        vector<int> path;
        for (int v = dest; v != -1; v = parent[v])
            path.push_back(v);

        cout << "Route: ";
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i];
            if (i != 0) cout << " -> ";
        }
        cout << endl;

        foodMenu(); // ✔ YOUR FOOD MENU CALLED HERE
    }
};

int main() {
    int V;
    cout << "Enter number of airports: ";
    cin >> V;

    Graph g(V);

    while (true) {
        cout << "\n1.Add Flight\n2.Display\n3.Find Route\n4.Exit\nChoice: ";
        int c;
        cin >> c;

        if (c == 1) {
            int u,v,cost,time,dep;
            cout << "u v cost time dep: ";
            cin >> u >> v >> cost >> time >> dep;
            g.addEdge(u,v,cost,time,dep);
        }

        else if (c == 2) {
            g.display();
        }

        else if (c == 3) {
            int s,d,du,dv;
            bool delay;

            cout << "src dest: ";
            cin >> s >> d;

            cout << "Delay? (1/0): ";
            cin >> delay;

            if (delay) {
                cout << "Delayed route u v: ";
                cin >> du >> dv;
            }

            g.dijkstra(s,d,du,dv,delay);
        }

        else break;
    }

    return 0;
}
