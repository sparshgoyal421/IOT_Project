import networkx as nx
g = nx.DiGraph()
nodes = ['J1', 'J2', 'J3', 'J4', 'J5', 'J6', 'J7', 'J8', 'J9', 'J10']
edges = [("J1", "J2"), ("J3", "J2"), ("J3", "J4"), ("J4", "J5"), ("J6", "J2"), ('J2', 'J1'), ('J2', 'J3'), ('J4', 'J3'), ('J5', 'J4'), ('J4', 'J2'), ('J2', 'J6'),
         ("J6", "J7"), ("J7", "J3"), ("J7", "J8"), ("J3", "J9"), ("J9", "J10"), ('J7', 'J6'), ('J3', 'J7'), ('J8', 'J7'), ('J9', 'J3'), ('J10', 'J9'), ("J7", "J9")]
weights = [2, 3, 1, 4, 2, 1, 3, 1, 2, 1, 2, 3, 1, 2, 3, 1, 1, 2, 1, 3, 4, 1]
print(len(edges), len(weights))
g.add_nodes_from(nodes)
# g.add_edges_from(edges)
for i in range(len(edges)):
    g.add_edge(edges[i][0], edges[i][1], weight=weights[i])
pos = {"J1": (-2, 0), "J2": (-1, 0), "J3": (0, 0), "J4": (0, -1), "J5": (0, -2),
       "J6": (-1, 1), "J7": (0, 1), "J8": (0, 2), "J9": (1, 0), "J10": (2, 0)}
# nx.draw(g, pos=pos, with_labels=True, node_color="red")
nx.draw(g, pos=pos, with_labels=False, node_color="red", edge_color="black", width=1)

# Dijsktra 
# for i in range(len(edges)):
    # print(edges[i][0], edges[i][1], weights[i])

path = nx.dijkstra_path(g, "J10", "J1")
# print(path)

# color the nodes in the graph as red if it is in the path
for i in range(len(path)):
    if i == 0:
        nx.draw_networkx_nodes(g, pos, nodelist=[path[i]], node_color='green')
    else:
        nx.draw_networkx_nodes(g, pos, nodelist=[path[i]], node_color='green')
        nx.draw_networkx_edges(g, pos, edgelist=[(path[i-1], path[i])], edge_color='green', width=2)
