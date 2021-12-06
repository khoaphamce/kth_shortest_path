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

    // std::cout << "A now:";
    // path_list[0].print(); std::cout << std::endl;

    for (int k = 1; k <= K; k++){
      //std::cout << "K = " << k << std::endl;
        for (int i = 0; i < path_list[k-1].size()-2; i++){
          //std::cout << "i = " << i << std::endl;
            // Make new graph to delete edges and nodes
            ds::graph copy_graph;
            mainGraph.copy(copy_graph);
            // std::cout << "Done making new graph and copy" << std::endl;

            // Define spur_node and make root path (from soure to spur node)
            long int spurNode = path_list[k-1].node(i);
            ds::path rootPath;
            path_list[k-1].copy(rootPath, 0, i+1);
            // std::cout << "Spur node: "; 
            // std::cout << spurNode << std::endl;
          //std::cout << "Root path: ";
           // rootPath.print();
          //std::cout << std::endl;
            // std::cout << "Done define spur node and make root path" << std::endl;
            
            // Delete edge
            for (int ip = 0; ip < path_list.size(); ip++){
                ds::path path_list_path;
                path_list[ip].copy(path_list_path);
    
                // std::cout << "Done copy path from path list" << std::endl;
                ds::path comparePath;
                path_list_path.copy(comparePath,0,i+1);
              //std::cout << "To compare path: "; comparePath.print();
              //std::cout << std::endl;

                if (rootPath.compare(comparePath)){
                    copy_graph.delete_edge(path_list_path.node(i), path_list_path.node(i+1));
                  //std::cout << "Delete edge: " << path_list_path.node(i) << " -> " << path_list_path.node(i+1) << std::endl;
                  //std::cout << "Graph now:" << std::endl;
                    // copy_graph.print();
                }
                // std::cout << "Done delete edge" << std::endl;
            }

            // Delete node
            for (int irp = 0; irp < rootPath.size(); irp++){
                if (rootPath.node(irp) != spurNode)
                    copy_graph.delete_node(rootPath.node(irp));
              //std::cout << "Done delete node at " << irp << std::endl;
            }

            // Find spur path
            dijkstra::DijkstraObject spur_dijkstra;
            spur_dijkstra.Dijkstra(copy_graph, spurNode);
            spur_dijkstra.makePath(finishNode);
            // std::cout << "Done find spur path" << std::endl;

            ds::path spurPath; 
            spur_dijkstra.dPath.copy(spurPath);

            if (spurPath.node(0) != rootPath.node(rootPath.size()-1)){
                continue;
            }
            // std::cout << "Spur path: ";
            // spurPath.print();
            // std::cout << std::endl;
            // std::cout << "Done copy spur path" << std::endl;

            // Merge spur path and total path
            ds::path totalPath;
            totalPath = rootPath.merge(spurPath, false, 0);
          //std::cout << "total path: ";
           // totalPath.print();
          //std::cout << std::endl;

            // std::cout << "Done merge path" << std::endl;

            // check if duplicate in temp path list
            if (tempPathList.size() > 0){
                for (int itpl = 0; itpl < tempPathList.size(); itpl++){
                    if (!tempPathList[itpl].compare(totalPath)){
                      //std::cout << "comparing: " << std::endl;
                        //tempPathList[itpl].print();
                      //std::cout << " not equal to ";
                        //totalPath.print();
                      //std::cout << std::endl;
                        tempPathList.push_back(totalPath);
                    }
                  //std::cout << "Temp path list now:" << std::endl;
                    // for (int itpl = 0; itpl < tempPathList.size(); itpl++){
                    //     tempPathList[itpl].print();
                    //   //std::cout << std::endl;
                    // }
                }
            }
            else{
                tempPathList.push_back(totalPath);
              //std::cout << "Temp path list now:" << std::endl;
                //  for (int itpl = 0; itpl < tempPathList.size(); itpl++){
                //     tempPathList[itpl].print();
                //   //std::cout << std::endl;
                // }
            }
            // std::cout << "Done check dup" << std::endl;
        }
        
        if (tempPathList.size()==0){
            break;
            // std::cout << std::endl;
        }

        std::sort(tempPathList.begin(), tempPathList.end(), comparePath);
        // std::cout << "Done sort list" << std::endl;

        path_list.push_back(tempPathList[0]);
      //std::cout << "Done achive from temp list" << std::endl;
      //std::cout << "path list size: " << path_list.size() << std::endl;

        tempPathList.erase(tempPathList.begin());
      //std::cout << "Done erase first one" << std::endl;
      //std::cout << "temp path list size now: " << tempPathList.size() << std::endl;

        // std::cout << std::endl;
    }
}

std::vector<ds::path> yenObject::getPathList(){
    return path_list;
}

