//KMeans algorithm
//n-dimensional data points
//m-clusters

//------ALGORITHM------//

//shuffle datapoints (not necessary)
//create m clusters randomly
//assign clusters based on closest distance to cluster
//re-seat m clusters on average of datapoints in such cluster
//assign clusters again
//if no change ouput assignments
//if change continue operations

//------Data_Worker-----//
//each data point has distance from m clusters
//each data point has its cluster that its assigned to
//each data point holds its values in n dimensions
//for spotify:
//[acousticness danceability energy instrumentalness key liveness loudness mode speechiness tempo valence]

//-----Data_Input-------//
//data stored in csv
//data loaded and 

#include "datas.h"

//fix variable amount of data input

int main()
{

    Data_Points datas[numDataPoints];
    

    //Load in data
    InputData(datas);
    
    Cluster clusters[numClusters];

    //Create clusters
    CreateClusters(clusters, datas);


    //Assign Clusters
    Assign(clusters, datas);


    //Loop till no change

    while(!check(datas)){
        RePosClusters(clusters, datas);
        Assign(clusters, datas);
    }

    for(int i = 0; i < numDataPoints; i++){
        std::cout<<"Name:  "<<datas[i].Name<<", Cluster:  "<<datas[i].cluster<<std::endl;
    }

    for(int i = 0; i < numClusters; i++){
        std::cout<<"CLUSTER "<<i<<": "<<"\n";
        for(int j = 0; j < numDataPoints; j++){
            if(datas[j].cluster == clusters[i].id){
                std::cout<<datas[j].Name<<"  "<<datas[j].cluster<<"\n";
            }
        }
        std::cout<<"-----------------------------------"<<"\n";
    }


    return 0;
}