/*==============================================(PROJET ISTY C++)=======================================*/


#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <future>
#include <ctime>

using namespace std;
class Graph {
public:
    map<int, set<int>> adjList;

    void addArets(int from, int to) {
        adjList[from].insert(to);
        adjList[to].insert(from);
    }

    int getNumSommets() {
        return adjList.size();
    }

    int getNumAretes() {
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

    int getNumConnexeComponents() {
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

    int NbrCycles3Sommet() {
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
        return count / 6; 
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

bool isCsvFile(const std::string& file_path) {
    size_t pos = file_path.find_last_of('.');
    if (pos != std::string::npos) {
        std::string extension = file_path.substr(pos);
        return (extension == ".csv");
    }
    return false;
}
// verifier si le fichier est .txt 
bool isTxtFile(const std::string& file_path) {
    size_t pos = file_path.find_last_of('.');
    if (pos != std::string::npos) {
        std::string extension = file_path.substr(pos);
        return (extension == ".txt");
    }
    return false;
}
// fonction pour calculer dégénérescence
int calculateDegeneracy(map<int, set<int>>& adjList) {
    int degeneracy = 0; 
    while (!adjList.empty()) {
        int minDegree = INT_MAX;
        int minDegreeNode = -1;
        // trouver le noeud au degré minimal.
        for (const auto& pair : adjList) {
            int node = pair.first;
            int degree = pair.second.size();
            if (degree < minDegree) {
                minDegree = degree;
                minDegreeNode = node;
            }
        }
        // supprimer les nodes avec degré minimal
        adjList.erase(minDegreeNode);
        // Retirez le noeud des listes d'adjacence de ses voisins.
        for (const auto& pair : adjList) {
            int node = pair.first;
            adjList[node].erase(minDegreeNode);
        }
        
        degeneracy = max(degeneracy, minDegree);
    }
    return degeneracy;
}

void processGraphFile(const string& graphFile, ofstream& outputCSV) {
    vector<pair<int, int>> edges;
    ifstream fichier_cible(graphFile);

    if (!fichier_cible) {
        cerr << "Impossible d'ouvrir le fichier: " << graphFile << endl;
    } else {
        Graph graph;
        edges.clear(); // Clear edges for each file
        string line;
        while (getline(fichier_cible, line)) {
            if (isTxtFile(graphFile)) {
                istringstream iss(line);
                int from, to;
                if (iss >> from >> to) {
                    edges.push_back({from, to});
                } else {
                    cerr << "Invalid line in the file: " << line << endl;
                }
            } else if (isCsvFile(graphFile)) {
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
            graph.addArets(edge.first, edge.second);
        }
        
        ofstream degreeDistCSV(graphFile + "_degree_distribution.csv");
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

        
        int numVertices = graph.getNumSommets();
        int numEdges = graph.getNumAretes();
        int maxDegree = graph.getMaxDegree();
        int numConnectedComponents = graph.getNumConnexeComponents();
        int numCyclesWith3Vertices = graph.NbrCycles3Sommet();

        
        int degeneracy = calculateDegeneracy(graph.adjList);

        // ajouter les resultat au fichier .csv
        outputCSV << graphFile << "; " << numVertices << "; " << numEdges
                  << "; " << maxDegree << "; " << numConnectedComponents
                  << "; " << numCyclesWith3Vertices << "; " << degeneracy << endl;
    }
}

int main() {
    clock_t start_time = clock();
    ofstream outputCSV("C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\output2.csv");

    if (!outputCSV) {
        cerr << "Impossible d'ouvrir le fichier!" << endl;
        return 1;
    }

    outputCSV << "Nom du graphe; Nombre de sommets; Nombre d'arêtes; Degré maximal; Nombre de composantes connexes; Nombre de cycles avec 3 sommets; dégénérescence\n";

    vector<string> liste_des_graphes = {
        "C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\CA-GrQc.txt",
        "C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\FacebookSites.csv",
        "C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\Github.csv",
        "C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\twitchDE.csv",
        "C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\Wikipedia1.csv"
    };

    vector<future<void>> futures; //  store tache asynchrone 

    for (const string& graphFile : liste_des_graphes) {
        // tâche asynchrone pour chaque fichier de graphe.
        futures.push_back(async([graphFile, &outputCSV]() {
            processGraphFile(graphFile, outputCSV);
        }));
    }

    
    for (auto& future : futures) {
        future.get();
    }

    outputCSV.close();
    clock_t end_time = clock();
    double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Temps d'exécution : " << elapsed_time << " secondes" << std::endl;

    return 0;
}






