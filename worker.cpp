#include "datas.h"
#include <time.h>


void InputData(Data_Points datas[numDataPoints])
{
    std::vector<std::vector<std::string>> content;
    std::vector<std::string> row;
    std::string line, word;

    std::fstream file ("data.csv", std::ios::in);

    if(file.is_open())
    {
        while(std::getline(file, line))
        {
            row.clear();

            std::stringstream str(line);

            while(std::getline(str, word, ','))
            {
                row.push_back(word);
            }
            
            content.push_back(row);
            
        }
    }
    else{
        std::cout<<"Could not open the file\n";
    }

    std::vector<float> Feature;

    int count = 0;

    for(int i=1;i<content.size();i++){
    
        for(int j=0;j<content[i].size();j++){

            if(j == 0){
                datas[count].Name = content[i][j];

            }
            
            else{
                Feature.push_back(std::stof(content[i][j]));
            }

        }

        datas[count].cluster = 0;

        datas[count++].Features = Feature;
        
        Feature.clear();
        
    }
    
}

float calculateDistanceSingle(std::vector<float> ClusterFeatures, std::vector<float> DataFeaures)
{
    float sum = 0;

    for(int i = 0; i < numFeatures; i++){
        sum = sum + ((DataFeaures[i]-ClusterFeatures[i])*(DataFeaures[i]-ClusterFeatures[i]));
    }

    return(std::sqrt(sum));
}

void Assign(Cluster Clusters[numClusters], Data_Points datas[numDataPoints])
{

    Comparator c;
    c.ClosestDistance = 10000;
    c.Cluster = 0;

    for(int i = 0; i < numDataPoints; i++){
        for(int j = 0; j < numClusters; j++){
            
            c.CurrDistance = calculateDistanceSingle(Clusters[j].Position, datas[i].Features);

            if(c.CurrDistance <= c.ClosestDistance){
                c.ClosestDistance = c.CurrDistance;
                c.Cluster = Clusters[j].id;
            }

        }

        datas[i].prevCluster = datas[i].cluster;
        datas[i].cluster = c.Cluster;

        c.ClosestDistance = 10000;
        c.Cluster = 0;
        c.CurrDistance = 0;

    }
}

void CreateClusters(Cluster Clusters[numClusters], Data_Points datas[numDataPoints])
{
    int seed = time(0);

    for(int i = 0; i < numClusters; i++){

        srand(seed+i+25);

        int RandIndex = rand() % numDataPoints;

        Clusters[i].Position = datas[RandIndex].Features;

        Clusters[i].id = i;
    }

}

void RePosClusters(Cluster Clusters[numClusters], Data_Points datas[numDataPoints])
{

    std::vector<float> Feature(numFeatures, 0);
    int count = 0;

    //Loop through all clusters
    for(int i = 0; i < numClusters; i++){

        
        for(int j = 0; j < numDataPoints; j++){


            //If data is in cluster
            if(Clusters[i].id == datas[j].cluster){
                
                //sum features
                for(int k = 0; k < numFeatures; k++){
                    Feature[k] = Feature[k] + datas[j].Features[k];
                }

                count++;

            }
        }

        //after all in cluster found, average
        for(int x = 0; x < numFeatures; x++){
            Feature[x] = Feature[x]/count;
        }

        Clusters[i].Position = Feature;

        std::vector<float> Feature(numFeatures, 0);
        count = 0;
    }
}

int check(Data_Points datas[numDataPoints])
{
    int count = 0;

    for(int i = 0; i < numDataPoints; i++){
        if(datas[i].cluster == datas[i].prevCluster){
            count++;
        }
    }

    if(count >=numDataPoints){
        return(1);
    }
    else{
        return(0);
    }
}