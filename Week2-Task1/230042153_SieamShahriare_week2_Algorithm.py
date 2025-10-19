import math
from itertools import permutations

def calculateDistance(p1, p2):
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

def calculateTotalDistance(path):
    return sum(calculateDistance(path[i], path[i+1]) for i in range(len(path)-1))

def nearestNeighborTsp(coordinates):
    if len(coordinates) <= 1:
        return coordinates
    
    start = coordinates[0]
    unvisited = set(range(1, len(coordinates)))
    path = [start]
    currentIndex = 0
    
    while unvisited:
        currentPoint = coordinates[currentIndex]
        nearestIndex = min(unvisited, key=lambda i: calculateDistance(currentPoint, coordinates[i]))
        path.append(coordinates[nearestIndex])
        currentIndex = nearestIndex
        unvisited.remove(nearestIndex)
    
    return path

def twoOptLocalSearch(path):
    improved = True
    bestPath = path[:]
    
    while improved:
        improved = False
        for i in range(1, len(bestPath) - 2):
            for j in range(i + 1, len(bestPath)):
                if j - i == 1:
                    continue
                
                currentDist = (calculateDistance(bestPath[i-1], bestPath[i]) +
                             calculateDistance(bestPath[j-1], bestPath[j]))
                newDist = (calculateDistance(bestPath[i-1], bestPath[j-1]) +
                          calculateDistance(bestPath[i], bestPath[j]))
                
                if newDist < currentDist:
                    bestPath[i:j] = reversed(bestPath[i:j])
                    improved = True
                    break
            if improved:
                break
    
    return bestPath

def exactTsp(destinations):
    if len(destinations) <= 1:
        return destinations
    
    start = destinations[0]
    otherPoints = destinations[1:]
    
    bestDistance = float('inf')
    bestPath = None
    
    for perm in permutations(otherPoints):
        currentPath = [start] + list(perm)
        currentDistance = calculateTotalDistance(currentPath)
        
        if currentDistance < bestDistance:
            bestDistance = currentDistance
            bestPath = currentPath
    
    return bestPath

def optimizeNavigation(coordinates):
    if len(coordinates) <= 1:
        return coordinates
    
    if len(coordinates) <= 12:
        optimalPath = exactTsp(coordinates)
    else:
        initialPath = nearestNeighborTsp(coordinates)
        optimalPath = twoOptLocalSearch(initialPath)
    
    return optimalPath

if __name__ == "__main__":
    destinations = [(0, 0), (1, 5), (5, 2), (3, 8), (7, 1)]
    
    optimized = optimizeNavigation(destinations)
    print("Optimized path:", optimized)
