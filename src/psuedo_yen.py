function YenKSP(Graph, source, sink, K):
    # Determine the shortest path from the source to the sink.
    A[0] = Dijkstra(Graph, source, sink);
    # Initialize the set to store the potential kth shortest path.
    B = [];
    
    for k from 1 to K:
        # The spur node ranges from the first node to the next to last node in the previous k-shortest path.
        for i from 0 to size(A[k − 1]) − 2:
            
            # Spur node is retrieved from the previous k-shortest path, k − 1.
            spurNode = A[k-1].node(i);
            # The sequence of nodes from the source to the spur node of the previous k-shortest path.
            rootPath = A[k-1].nodes(0, i);
            
            for each path p in A:
                if rootPath == p.nodes(0, i):
                    # Remove the links that are part of the previous shortest paths which share the same root path.
                    remove p.edge(i,i + 1) from Graph;
            
            for each node rootPathNode in rootPath except spurNode:
                remove rootPathNode from Graph;
            
            # Calculate the spur path from the spur node to the sink.
            # Consider also checking if any spurPath found
            spurPath = Dijkstra(Graph, spurNode, sink);
            
            # Entire path is made up of the root path and spur path.
            totalPath = rootPath + spurPath;
            # Add the potential k-shortest path to the heap.
            if (totalPath not in B):
                B.append(totalPath);
            
            # Add back the edges and nodes that were removed from the graph.
            restore edges to Graph;
            restore nodes in rootPath to Graph;
                    
        if B is empty:
            # This handles the case of there being no spur paths, or no spur paths left.
            # This could happen if the spur paths have already been exhausted (added to A), 
            # or there are no spur paths at all - such as when both the source and sink vertices 
            # lie along a "dead end".
            break;
        # Sort the potential k-shortest paths by cost.
        B.sort();
        # Add the lowest cost path becomes the k-shortest path.
        A[k] = B[0];
        # In fact we should rather use shift since we are removing the first element
        B.pop();
    
    return A;