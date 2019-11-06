class Vertex:
    def __init__(self, value=0, to_neighbors:dict=None, from_neighbors:dict=None):
        self.value = value;
        if to_neighbors is None:
            self.to_neighbors = {}
        else:
            self.to_neighbors = to_neighbors
        if from_neighbors is None:
            self.from_neighbors = {}
        else:
            self.from_neighbors = from_neighbors
        self.to_neighbors_sorted = []
        self.to_neighbors_sorted_valid = False
            
    def has_unvisited(self, visited:set):
        if not self.to_neighbors_sorted_valid:
            self.to_neighbors_sorted = sorted(self.to_neighbors.values(), key=lambda v: v.value, reverse=True)
            self.to_neighbors_sorted_valid = True
        set_verticies = set(self.to_neighbors.values())
        if len(set_verticies.intersection(visited)) == len(set_verticies):
            return None
        for v in self.to_neighbors_sorted:
            if v not in visited:
                return v
        return None    
            
    def __eq__(self, other):
        return self.value == other.value
        
    def __str__(self):
        return "{} -> {}\n".format(str(self.value), str([v.value for v in self.to_neighbors.values()]))
        
    def __hash__(self):
        return self.value

class Edge:
    def __init__(self, start:Vertex, end:Vertex):
        self.start = start
        self.end = end
        
    def __eq__(self, other):
        return self.start==other.start and self.end==other.end
        
    def __str__(self):
        return "{} --> {}\n".format(self.start.value, self.end.value)
        
    def __hash__(self):
        return (31*self.start.__hash__() + self.end.__hash__()) 
        
class Graph:
    def __init__(self, verticies:dict=None, edges:set=None):
        self.start_verticies = {}
        if verticies is None :
            self.verticies = {}
        else:
            self.verticies = verticies
        if edges is None:
            self.edges = set()
        else:
            self.edges = edges
            
    def add_vertex(self, v:Vertex):
        if v.value not in self.verticies:
            self.verticies[v.value] = v
            self.start_verticies[v.value] = v
            
            
    def add_edge(self, e:Edge):
        if e not in self.edges:
            self.edges.add(e)
        if e.start.value not in self.verticies and e.end.value not in self.verticies:
            e.start.to_neighbors[e.end.value] = e.end
            e.end.from_neighbors[e.start.value] = e.start
            self.add_vertex(e.start)
            self.add_vertex(e.end)
        elif e.start.value not in self.verticies:
            e.start.to_neighbors[e.end.value] = self.verticies[e.end.value]
            self.verticies[e.end.value].from_neighbors[e.start.value] = e.start
            self.add_vertex(e.start)
        elif e.end.value not in self.verticies:
            e.end.from_neighbors[e.start.value] = self.verticies[e.start.value]
            self.verticies[e.start.value].to_neighbors[e.end.value] = e.end
            self.add_vertex(e.end)
        else:
            self.verticies[e.start.value].to_neighbors[e.end.value] = e.end
            self.verticies[e.end.value].from_neighbors[e.start.value] = e.start
        if e.end.value in self.start_verticies:
            del self.start_verticies[e.end.value]
            
    def topo_sort(self):
        start, finish = self.dfs()
        final_sort = sorted(finish.items(), key=lambda kv:kv[1], reverse=True)
        return final_sort
        
    def dfs(self):
        start = {}
        finish = {}
        visited = set()
        sorted_verticies = sorted(self.start_verticies.values(), key=lambda sv: sv.value, reverse=True)
        count = 0
        for sv in sorted_verticies:
            working = [sv]
            visited.add(sv)
            start[sv] = count
            while(len(working) > 0):
                count += 1
                unvisited = working[len(working)-1].has_unvisited(visited)
                if unvisited is not None:
                    working.append(unvisited)
                    visited.add(unvisited)
                    start[unvisited] = count
                else:
                    finish[working.pop()] = count
            count += 1
        return start, finish
            
            
    def __str__(self):
        r = "**************************\nVerticies:\n"
        for k, v in self.verticies.items():
            r += str(v)
        r += "\nStart Verticies:\n"
        for k, sv in self.start_verticies.items():
            r += str(sv)
        r += "\nEdges:\n"
        for e in self.edges:
            r += str(e)
        r += "**************************\n"
        return r
            
if __name__ == "__main__":
    num_houses = int(input())
    dirs = input()
    graph = Graph()
    for i in range(num_houses-1):
        v1 = Vertex(value=i)
        v2 = Vertex(value=i+1)
        if dirs[i] == 'R':
            e = Edge(v1, v2)
        else:
            e = Edge(v2, v1)
        graph.add_edge(e)
    order = graph.topo_sort()
    for o in order:
        print(o[0].value + 1)
        
