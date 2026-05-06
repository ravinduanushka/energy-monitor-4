#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <iostream>

class RoomGraph {
private:
    std::unordered_map<std::string, std::vector<std::string>> adjList;  

public:
    void addNode(const std::string& nodeId);
    void addEdge(const std::string& node1, const std::string& node2);
    void printConnections(const std::string& startNode) const;
    std::vector<std::string> getConnectedComponent(const std::string& startNode) const;
};
