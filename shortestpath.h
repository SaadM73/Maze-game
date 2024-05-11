#pragma once
#include <vector>
#include <cmath> // For abs()
#include <SFML/Graphics.hpp>


struct PathNode {
    int x, y;           // Node coordinates
    int gCost, hCost, fCost;  // Costs for A* algorithm
    PathNode* parent;   // Pointer to parent node for path tracing

    PathNode(int x, int y) : x(x), y(y), gCost(0), hCost(0), fCost(0), parent(nullptr) {}

    void calculateCosts(PathNode* end) {
        hCost = abs(x - end->x) + abs(y - end->y);  // Manhattan distance heuristic
        gCost = parent ? parent->gCost + 1 : 1;
        fCost = gCost + hCost;
    }
};

std::vector<PathNode*> findShortestPath(PathNode* start, PathNode* end, const std::vector<std::vector<bool>>& walkable) {
    std::vector<PathNode*> openSet, closedSet, path;
    openSet.push_back(start);

    while (!openSet.empty()) {
        // Find the node with the lowest fCost
        PathNode* current = nullptr;
        size_t currentIndex = 0;
        for (size_t i = 0; i < openSet.size(); i++) {
            if (!current || openSet[i]->fCost < current->fCost) {
                current = openSet[i];
                currentIndex = i;
            }
        }

        // Remove the current node from the open set
        openSet.erase(openSet.begin() + currentIndex);
        closedSet.push_back(current);

        // Check if we have reached the end
        if (current == end) {
            while (current) {
                path.push_back(current);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        // Process all neighbors
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0) continue; // Skip self

                int nx = current->x + dx;
                int ny = current->y + dy;

                if (nx >= 0 && ny >= 0 && nx < walkable[0].size() && ny < walkable.size() && walkable[ny][nx]) {
                    PathNode* neighbor = new PathNode(nx, ny);
                    neighbor->calculateCosts(end);

                    // Check if neighbor is in closed set
                    bool isInClosedSet = false;
                    for (auto& closedNode : closedSet) {
                        if (closedNode->x == nx && closedNode->y == ny) {
                            isInClosedSet = true;
                            break;
                        }
                    }
                    if (isInClosedSet) continue;

                    // Calculate costs and set parent
                    neighbor->parent = current;
                    neighbor->calculateCosts(end);

                    // Check if neighbor is in open set
                    bool isInOpenSet = false;
                    for (auto& openNode : openSet) {
                        if (openNode->x == nx && openNode->y == ny) {
                            isInOpenSet = true;
                            if (openNode->gCost > neighbor->gCost) {
                                openNode->gCost = neighbor->gCost;
                                openNode->parent = current;
                            }
                            break;
                        }
                    }

                    if (!isInOpenSet) {
                        openSet.push_back(neighbor);
                    }
                }
            }
        }
    }

    return path; // Return empty path if no path is found
}

void visualizePath(sf::RenderWindow& window, const std::vector<PathNode*>& path, int cellSize) {
    sf::RectangleShape shape(sf::Vector2f(cellSize - 2, cellSize - 2)); // Subtracting 2 for visual padding
    shape.setFillColor(sf::Color::Green); // Color the path green

    for (auto node : path) {
        shape.setPosition(node->x * cellSize, node->y * cellSize);
        window.draw(shape);
    }
}