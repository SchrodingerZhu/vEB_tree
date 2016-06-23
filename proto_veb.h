#pragma once
#include <cmath>
#include <functional>
#include <memory>
#include <vector>
#include<iostream>
namespace std {
    template <class T>
    class proto_vEB{
    public:
        proto_vEB(int i=2){
            u=i;
            if(u<=2){
                summary=NULL;
                cluster.resize(0);
                A.push_back(data(0,T(0)));
                A.push_back(data(0,T(0)));
            }else {
                A.resize(0);
                summary= new proto_vEB( pow(u,0.5) ) ;
                for(int i=0;i<pow(u,0.5);i++){
                    cluster.push_back(new proto_vEB( pow(u,0.5) ));
                }
            }
        }
        int high(int x){
            return (int)(x/(pow(u,0.5)));
        }
        int low(int x){
            return x%((int)pow(u,0.5));
        }
        int index(int x,int y){
            return x*(pow(u,0.5))+y;
        }

        bool member(int x){
            if(u==2){
                return A[x].first;
            }
            else return cluster.at(high(x))->member(low(x));
        }
        T& get(int x){
            if(u==2){
                return A[x].second;
            }
            else return cluster.at(high(x))->get(low(x));
        }
        void insert(int x,T y){
            if (u==2) {
                A[x].first=1;
                A[x].second=y;
            }else{
                cluster.at(high(x))->insert(low(x),y);
                summary->insert(high(x),y);
            }
        }


    private:
        typedef pair<bool,T> data;
        int u;
        vector< data > A;
        proto_vEB<T>* summary;
        vector < proto_vEB<T>* > cluster;
    };


}
