#include "RoomGraph.h"

void RoomGraph::addNode(const std::string& nodeId) {
    if (adjList.find(nodeId) == adjList.end()) {
        adjList[nodeId] = std::vector<std::string>();
    }
}

void RoomGraph::addEdge(const std::string& node1, const std::string& node2) {
    addNode(node1);
    addNode(node2);
    adjList[node1].push_back(node2);
    adjList[node2].push_back(node1);
}

void RoomGraph::printConnections(const std::string& startNode) const {
    if (adjList.find(startNode) == adjList.end()) {
        std::cout << "Node " << startNode << " not found in graph.\n";
        return;
    }

    std::unordered_set<std::string> visited;
    std::queue<std::string> q;
    
    q.push(startNode);
    visited.insert(startNode);
    
    std::cout << "Connections for " << startNode << ":\n";
    
    while (!q.empty()) {
        std::string current = q.front();
        q.pop();
        std::cout << " -> " << current << "\n";
        if (adjList.count(current)) {
            for (const std::string& neighbor : adjList.at(current)) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
    }
}

std::vector<std::string> RoomGraph::getConnectedComponent(const std::string& startNode) const {
    std::vector<std::string> component;
    if (adjList.find(startNode) == adjList.end()) return component;

    std::unordered_set<std::string> visited;
    std::stack<std::string> s;
    
    s.push(startNode);
    
    while (!s.empty()) {
        std::string current = s.top();
        s.pop();
        
        if (visited.find(current) == visited.end()) {
            visited.insert(current);
            component.push_back(current);
            
            if (adjList.count(current)) {
                for (const std::string& neighbor : adjList.at(current)) {
                    if (visited.find(neighbor) == visited.end()) {
                        s.push(neighbor);
                    }
                }
            }
        }
    }
    return component;
}
