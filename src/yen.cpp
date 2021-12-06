#include "yen.h"

using namespace yen;

bool yenObject::comparePath(ds::path path_1, ds::path path_2){
    return (path_1.getDist()) < (path_2.getDist());
}

yenObject::yenObject(){   
}

yenObject::yenObject(ds::graph inGraph){
    mainGraph = inGraph;
}
 
ds::path yenObject::path(long int kth){
    if (path_list.size() <= 0){
      //std::cout << "Error no path generated yet, please makePath" << std::endl;
        ds::path new_path;
        new_path.add_node(-1);
        return new_path;
    }
    return path_list[kth];
}

void yenObject::makePath(long int sourceNode, long int finishNode, long int K){
    K--;
    std::vector<ds::path> tempPathList;

    dijkstra::DijkstraObject dijk_object;
    dijk_object.Dijkstra(mainGraph, sourceNode);
    dijk_object.makePath(finishNode);

    path_list.push_back(dijk_object.dPath);

    for (int k = 1; k <= K; k++){
        for (int i = 0; i < path_list[k-1].size()-2; i++){
            // Make new graph to delete edges and nodes
            ds::graph copy_graph;
            mainGraph.copy(copy_graph);

            // Define spur_node and make root path (from soure to spur node)
            long int spurNode = path_list[k-1].node(i);
            ds::path rootPath;
            path_list[k-1].copy(rootPath, 0, i+1);
          
            // Delete edge
            for (int ip = 0; ip < path_list.size(); ip++){
                ds::path path_list_path;
                path_list[ip].copy(path_list_path);
    
                ds::path comparePath;
                path_list_path.copy(comparePath,0,i+1);
              
                if (rootPath.compare(comparePath)){
                    copy_graph.delete_edge(path_list_path.node(i), path_list_path.node(i+1));
                }
            }

            // Delete node
            for (int irp = 0; irp < rootPath.size(); irp++){
                if (rootPath.node(irp) != spurNode)
                    copy_graph.delete_node(rootPath.node(irp));
            }

            dijkstra::DijkstraObject spur_dijkstra;
            spur_dijkstra.Dijkstra(copy_graph, spurNode);
            spur_dijkstra.makePath(finishNode);

            ds::path spurPath; 
            spur_dijkstra.dPath.copy(spurPath);

            if (spurPath.node(0) != rootPath.node(rootPath.size()-1)){
                continue;
            }
            

            // Merge spur path and total path
            ds::path totalPath;
            totalPath = rootPath.merge(spurPath, false, 0);
          
            // check if duplicate in temp path list
            if (tempPathList.size() > 0){
                for (int itpl = 0; itpl < tempPathList.size(); itpl++){
                    if (!tempPathList[itpl].compare(totalPath)){
                        tempPathList.push_back(totalPath);
                    }
                }
            }
            else{
                tempPathList.push_back(totalPath);
            }
        }
        
        if (tempPathList.size()==0){
            break;
        }

        std::sort(tempPathList.begin(), tempPathList.end(), comparePath);

        path_list.push_back(tempPathList[0]);
    
        tempPathList.erase(tempPathList.begin());
    }
}

std::vector<ds::path> yenObject::getPathList(){
    return path_list;
}

yenObject::~yenObject(){
  path_list.clear();
}