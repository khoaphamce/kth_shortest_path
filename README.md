# K shortest path
A program for searching k shortest path

# New data type
1. graph
    -   How to use:
        -   Input data require:
            -   ```cpp 
                long int number_of_row 
                ```
                number of row in the matrix.
            -   ```cpp 
                vector<vector<long int>> input_matrix 
                ```
                input matrix that contain edges and weight.
            -   *Example:* 
                ```
                7
                1 2 4
                2 3 7
                1 3 5
                2 4 8
                3 5 7
                1 5 2
                2 5 1
                ```
                Explain: a matrix with 4 rows (or a graph with 4 edges)
                
                ![Example graph](./images/graph_1.png)
                

        -   ```cpp
            graph(vector<vector<long int>> input_matrix, long int number_of_row) 
            ```
            Make a graph out of input matrix.

        -   ```cpp
            graph.dist(long int a, long int b)
            ```
            Return distance between node a and b.
        -   ```cpp
            graph.print()
            ```
            Print graph to terminal (matrix form).


# How to use
Updating..
