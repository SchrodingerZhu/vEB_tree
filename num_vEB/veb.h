#pragma once
#include <cmath>
#include <functional>
#include <memory>
#include <vector>
#include <iostream>

namespace std {
    class vEB{
    private:
        long long upper,lower,u;
        long long min,max;
        shared_ptr<vEB > summary;
        vector< shared_ptr<vEB > > cluster;
        typedef  shared_ptr<vEB > vEB_ptr;
        void emInsert(long long x){
            min=max=x;
        }

    public:
        vEB(long long i=2){
            u=i;
            min=max=-1;
            upper=pow(2,ceil( (log( u )/log(2)) / 2.0 ));
            lower=pow(2,floor( (log( u )/log(2)) / 2.0 ));
            if(i==2){
                summary=nullptr;
                cluster.resize(0);
            }else{
                summary=vEB_ptr(new vEB(upper));
                for(long long i=0;i<upper;i++){
                    cluster.push_back((vEB_ptr)new vEB(lower) );
                }
            }
        }

        long long high(long long x){
            return (floor( x/lower ));
        }

        long long low(long long x){
            return x%lower;
        }
        long long index(long long x,long long y){
            return x*lower+y;
        }
        long long maximum(){
            return max;
        }

        long long minimum(){
            return min;
        }

        bool member(long long b){
            if(b==max||b==min)
                return true;
            else if(u==2) return false;
            else return cluster[high(b)]->member(low(b));
        }

        void insert(long long x){
            if(min==-1) emInsert(x);
            else {
                if (x<min){
                    swap(min,x);
                }
                if (u>2){
                    if(cluster.at(high(x))->minimum()==-1){
                        summary->insert(high(x));
                        cluster.at(high(x))->emInsert(low(x));
                    }
                    else{
                        cluster.at(high(x))->insert(low(x));
                    }
                }
                if(x>max){
                    max=x;
                }
            }
        }
        long long successor(long long x){
            if(u==2) {
                if(x==0&&max==1){
                    return 1;
                }else return -1;
            }
            else if(min!=-1&&x<min){
                return min;
            }
            else {
                long long max_low=cluster.at(high(x))->maximum();
                if (max_low!=-1&&low(x)<max_low){
                    long long offset = cluster.at(high(x))->successor(low(x));
                    return index(high(x),offset);
                }
                else{
                    long long succ_cluster =summary->successor(high(x));
                    if(succ_cluster==-1) return -1;
                    else{
                        long long offset = cluster.at(succ_cluster)->minimum();
                        return index(succ_cluster,offset);
                    }
                }
            }
        }

        long long predecessor(long long x){
            if(u==2){
                if(x==1&&min==0) return 0;
                else return -1;
            }
            else if(max!=-1&&x>max){
                return max;
            }
            else{
                long long min_low=cluster.at(high(x))->minimum();
                if(min_low!=-1&&low(x)>min_low){
                    long long offset = cluster.at(high(x))->predecessor(low(x));
                    return index(high(x),offset);
                }
                else{
                    long long pred_cluster = summary->predecessor(high(x));
                    if(pred_cluster==-1){
                        if (min!=-1&&x>min) return min;
                        else return -1;
                    }
                    else{
                        long long offset = cluster.at(pred_cluster)->maximum();
                        return index(pred_cluster,offset);
                    }
                }

            }
        }
        void erase(long long x){
            if(min==max){
                min=max=-1;
            }
            else if(u==2){
                if (x==0) {
                    min=1;
                }
                else min=0;
                max=min;
            }
            else{
                if(x==min){
                    long long first_cluster = summary->minimum();
                    x=index(first_cluster,cluster.at(first_cluster)->minimum());
                    min=x;
                }
                cluster.at(high(x))->erase(low(x));
                if (cluster.at(high(x))->minimum()==-1){
                    summary->erase(high(x));
                    if(x==max){
                        long long summary_max=summary->maximum();
                        if(summary_max==-1){
                            max=min;

                        }
                        else{
                            max=index(summary_max,cluster.at(summary_max)->maximum());

                        }
                    }
                }
                else if(x==max){
                    max= index(high(x),cluster.at(high(x))->maximum());

                }

            }

        }





    };



}
