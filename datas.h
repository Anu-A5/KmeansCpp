#pragma once

#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

#define numFeatures 11
#define numClusters 4
#define numDataPoints 131


struct Data_Points
{
    //[acousticness danceability energy instrumentalness key liveness loudness mode speechiness tempo valence]
    std::vector<float> Features;
    std::string Name;
    int cluster;
    int prevCluster;
};

struct Cluster
{
    std::vector<float> Position;
    int id;
};

struct Comparator
{   
    float ClosestDistance;
    float CurrDistance;
    int Cluster;
};

//Input data
void InputData(Data_Points datas[numDataPoints]);

//Create Clusters
//randomly assign initial values
void CreateClusters(Cluster Clusters[numClusters], Data_Points datas[numDataPoints]);

//Caluclate distance from a cluster
float calculateDistanceSingle(std::vector<float> ClusterFeatures, std::vector<float> DataFeaures[numFeatures]);

void Assign(Cluster Clusters[numClusters], Data_Points datas[numDataPoints]);

//Assign Data to a cluster
void AssignCluster(Data_Points* d, Cluster clusters[numClusters]);

//Recalculate Clusters
void RePosClusters(Cluster Clusters[numClusters], Data_Points datas[numDataPoints]);

int check(Data_Points datas[numDataPoints]);



