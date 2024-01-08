#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Graph {
public:
    map<int, set<int>> adjList;

    void addEdge(int from, int to) {
        adjList[from].insert(to);
        adjList[to].insert(from);
    }

    int getNumVertices() {
        return adjList.size();
    }

    int getNumEdges() {
        int edges = 0;
        for (const auto& pair : adjList) {
            edges += pair.second.size();
        }
        return edges / 2; 
    }

    int getMaxDegree() {
        int maxDegree = 0;
        for (const auto& pair : adjList) {
            maxDegree = max(maxDegree, int(pair.second.size()));
        }
        return maxDegree;
    }

    void dfs(int node, map<int, bool>& visited) {
        visited[node] = true;
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited);
            }
        }
    }

    int getNumConnectedComponents() {
        map<int, bool> visited;
        int numComponents = 0;
        for (const auto& pair : adjList) {
            int node = pair.first;
            if (!visited[node]) {
                dfs(node, visited);
                numComponents++;
            }
        }
        return numComponents;
    }

    int countCyclesWith3Vertices() {
        int count = 0;
        for (const auto& pair : adjList) {
            int node = pair.first;
            for (int neighbor : adjList[node]) {
                for (int neighbor2 : adjList[neighbor]) {
                    if (neighbor2 != node) {
                        if (adjList[neighbor2].count(node)) {
                            count++;
                        }
                    }
                }
            }
        }
        return count / 6; // Divide by 6 because each cycle is counted 6 times
    }
};

vector<string> split(const string& line, char delimiter) {
    vector<string> tokens;
    stringstream ss(line);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

bool isCsvFile(const string& file_path) {
    size_t pos = file_path.find_last_of('.');
    if (pos != string::npos) {
        string extension = file_path.substr(pos);
        return (extension == ".csv");
    }
    return false;
}

bool isTxtFile(const string& file_path) {
    size_t pos = file_path.find_last_of('.');
    if (pos != string::npos) {
        string extension = file_path.substr(pos);
        return (extension == ".txt");
    }
    return false;
}

int main() {
    vector<pair<int, int>> edges;
    ofstream outputCSV("C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\output.csv");

    if (!outputCSV) {
        cerr << "Impossible d'ouvrir le fichier!" << endl;
        return 1;
    }

    outputCSV << "Nom du graphe; Nombre de sommets; Nombre d'arêtes; Degré maximal; Nombre de composantes connexes; Nombre de cycles avec 3 sommets\n";

    vector<string> liste_des_graphes = {
        "C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\CA-GrQc.txt",
        "C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\FacebookSites.csv",
        "C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\Github.csv",
        "C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\twitchDE.csv",
        "C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\Wikipedia1.csv"
    };

    for (int i = 0; i < liste_des_graphes.size(); i++) {
        ifstream fichier_cible(liste_des_graphes[i]);

        if (!fichier_cible) {
            cerr << "Impossible d'ouvrir le fichier: " << liste_des_graphes[i] << endl;
        } else {
            Graph graph;
            edges.clear(); // Clear edges for each file

            string line;
            while (getline(fichier_cible, line)) {
                if (isTxtFile(liste_des_graphes[i])) {
                    istringstream iss(line);
                    int from, to;
                    if (iss >> from >> to) {
                        edges.push_back({from, to});
                    } else {
                        cerr << "Invalid line in the file: " << line << endl;
                    }
                } else if (isCsvFile(liste_des_graphes[i])) {
                    vector<string> tokens = split(line, ';');
                    if (tokens.size() == 2) {
                        try {
                            int from = stoi(tokens[0]);
                            int to = stoi(tokens[1]);
                            edges.push_back({from, to});
                        } catch (const std::invalid_argument& e) {
                            cerr << "Invalid integer in the file: " << line << endl;
                        }
                    } else {
                        cerr << "Invalid line in the file: " << line << endl;
                    }
                }
            }
            fichier_cible.close();

            for (const auto& edge : edges) {
                graph.addEdge(edge.first, edge.second);
            }

            // ces donnée on va les collecté et puis les traiter en python pour déssiner un graph
            ofstream degreeDistCSV(liste_des_graphes[i] + "_degree_distribution.csv");
            degreeDistCSV << "Degree;Frequency\n";
            map<int, int> degreeDistribution;
            for (const auto& pair : graph.adjList) {
                int degree = pair.second.size();
                degreeDistribution[degree]++;
            }
            for (const auto& entry : degreeDistribution) {
                degreeDistCSV << entry.first << ";" << entry.second << "\n";
            }
            degreeDistCSV.close();

            // Append the results to the main output CSV file
            outputCSV << liste_des_graphes[i] << "; " << graph.getNumVertices() << "; " << graph.getNumEdges()
                      << "; " << graph.getMaxDegree() << "; " << graph.getNumConnectedComponents()
                      << "; " << graph.countCyclesWith3Vertices() << "\n";
        }
    }

    outputCSV.close();

    return 0;
}
