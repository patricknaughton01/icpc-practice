class Graph:
    def __init__(self, edges=[], verticies=None):
        self.edges = edges
        if verticies is not None:
            self.verticies = verticies
        else:
            self.verticies = {}
    
    def topo_sort(self):
        discovered_time = {}
        finished_time = {}
        for v, vertex in self.verticies.items():
            discovered_time[vertex] = None
            finished_time[vertex] = None
        stack = list()
        start = None
        for val, vertex in self.verticies.items():
            if vertex.in_degree == 0 and start is not None:
                return "multiple starts"
            elif vertex.in_degree == 0:
                start = vertex
        if start == None:
            return "cycle"
        stack.append(start)
        counter = 0
        discovered_time[start] = counter
        visited = [start]
        while len(stack) > 0:
            unvisited = self.vertex_has_unvisited_neighbors(stack[len(stack)-1], visited)
            while unvisited is not None:
                counter += 1
                if(self.detect_cycle(unvisited, discovered_time, finished_time)):
                    return "cycle"
                to_visit = unvisited
                visited.append(to_visit)
                discovered_time[to_visit] = counter
                stack.append(to_visit)
                unvisited = self.vertex_has_unvisited_neighbors(to_visit, visited)
            counter += 1
            to_remove = stack.pop()
            finished_time[to_remove] = counter
        finish_sorted = sorted(finished_time.items(), key = lambda kv: kv[1], reverse=True)
        return finish_sorted
         
    def detect_cycle(self, vertex, discover_times, finish_times):
        for v in vertex.to_neighbors:
            if(discover_times[v] != None and finish_times[v] == None):
                return True
        return False
            
    def vertex_has_unvisited_neighbors(self, vertex, visited):
        for v in vertex.to_neighbors:
            if v not in visited:
                return v
        return None
        
    def contains_edge(self, edge):
        for e in self.edges:
            if e == edge:
                return True
        return False
            
    def __str__ (self):
        rstr = ""
        for edge in self.edges:
            rstr += str(edge) + "\n"
        for val, vertex in self.verticies.items():
            rstr += str(vertex) + "\n"
        return rstr
        
class Edge:
    def __init__(self, verticies=[]):
        self.verticies = verticies
        
    def __eq__(self, other):
        return (self.verticies[0] == other.verticies[0] 
                and self.verticies[1] == other.verticies[1])
        
    def __str__ (self):
        return(str(self.verticies[0]) + "-->" + str(self.verticies[1]))
        
class Vertex:
    def __init__(self, value, to_neighbors=None, from_neighbors=None, in_degree=0, out_degree=0):
        self.value = value
        if to_neighbors is not None:
            self.to_neighbors = to_neighbors
        else:
            self.to_neighbors = set()
        if from_neighbors is not None:
            self.from_neighbors = from_neighbors
        else:
            self.from_neighbors = set()
        self.in_degree = in_degree
        self.out_degree = out_degree
    
    def __str__(self):
        rstr= ("(" + str(self.value) + 
                ":" + str(self.in_degree) + 
                "," + str(self.out_degree) + ")")
        rstr += "To Neighbors: ["
        for v in self.to_neighbors:
            rstr += str(v.value)
        rstr += "]"
        return rstr

graph = Graph()       
meta = input().split(" ")
numWords = int(meta[1])
numLetters = int(ord(meta[0])) - int(ord('a')) + 1
words = []
# Read in words
for i in range(numWords):
    words.append(input())

# Each letter is a vertex
for i in range(numLetters):
    graph.verticies[chr(i + ord('a'))] = Vertex(chr(i + ord('a')))
            
# Initialize degrees to 0           
for vertex in graph.verticies:
    graph.verticies[vertex].in_degree = 0
    graph.verticies[vertex].out_degree = 0

# Add edges
for i in range(numWords-1):
    ind = 0
    while(ind < len(words[i]) and ind < len(words[i+1])):
        if(words[i][ind] != words[i+1][ind]):
            v1 = graph.verticies[words[i][ind]]
            v2 = graph.verticies[words[i+1][ind]]
            myedge = Edge([v1, v2])
            if not graph.contains_edge(myedge):
                graph.edges.append(myedge)
            v1.out_degree += 1
            v2.in_degree += 1
            v1.to_neighbors.add(v2)
            v2.from_neighbors.add(v1)
            ind = len(words[i])
            break
        else:
            ind += 1
topo_list = graph.topo_sort()
if topo_list == "multiple starts":
    print("AMBIGUOUS")
elif topo_list == "cycle":
    print("IMPOSSIBLE")
else:
    for v in topo_list:
        print(str(v[0].value), end="")
    print()
