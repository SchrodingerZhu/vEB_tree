#pragma once
#include <cmath>
#include <functional>
#include <memory>
#include <vector>
#include <iostream>

namespace std {
    template <class T>
    class vEB{
    private:
    public:
        typedef pair<long long,T> data;
        long long upper,lower,u;
        data min,max;
        shared_ptr<vEB<T> > summary;
        vector< shared_ptr<vEB<T> > > cluster;
        typedef  shared_ptr<vEB<T> > vEB_ptr;
        void emInsert(long long x,T a){
            min.first=max.first=x;
            min.second=max.second=a;
        }

    public:
        vEB(long long i=2){
            u=i;
            min.first=max.first=-1;
            upper=pow(2,ceil( (log( u )/log(2)) / 2.0 ));
            lower=pow(2,floor( (log( u )/log(2)) / 2.0 ));
            if(i==2){
                summary=nullptr;
                cluster.resize(0);
            }else{
                summary=vEB_ptr(new vEB<T>(upper));
                for(long long i=0;i<upper;i++){
                    cluster.push_back((vEB_ptr)new vEB<T>(lower) );
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
            return max.first;
        }

        long long minimum(){
            return min.first;
        }

        bool member(long long b){
            if(b==max.first||b==min.first)
                return true;
            else if(u==2) return false;
            else return cluster[high(b)]->member(low(b));
        }
        T get_value(long long b){
            if(b==max.first)
                return max.second;
            else if(b==min.first)
                return min.second;
            else return cluster[high(b)]->get_value(low(b));
        }
        void insert(long long x,T a){
            if(min.first==-1) emInsert(x,a);
            else {
                if (x<min.first){
                    swap(min.first,x);
                    swap(min.second,a);
                }
                if (u>2){
                    if(cluster.at(high(x))->minimum()==-1){
                        summary->insert(high(x),a);
                        cluster.at(high(x))->emInsert(low(x),a);
                    }
                    else{
                        cluster.at(high(x))->insert(low(x),a);
                    }
                }
                if(x>max.first){
                    max.first=x;
                    max.second=a;
                }
            }
        }
        long long successor(long long x){
            if(u==2) {
                if(x==0&&max.first==1){
                    return 1;
                }else return -1;
            }
            else if(min.first!=-1&&x<min.first){
                return min.first;
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
                if(x==1&&min.first==0) return 0;
                else return -1;
            }
            else if(max.first!=-1&&x>max.first){
                return max.first;
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
                        if (min.first!=-1&&x>min.first) return min.first;
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
            if(min.first==max.first){
                min.first=max.first=-1;
            }
            else if(u==2){
                if (x==0) {
                    min.first=1;
                }
                else min.first=0;
                max.first=min.first;
            }
            else{
                if(x==min.first){
                    long long first_cluster = summary->minimum();
                    x=index(first_cluster,cluster.at(first_cluster)->minimum());
                    min.first=x;
                }
                cluster.at(high(x))->erase(low(x));
                if (cluster.at(high(x))->minimum()==-1){
                    summary->erase(high(x));
                    if(x==max.first){
                        long long summary_max=summary->maximum();
                        if(summary_max==-1){
                            max.first=min.first;

                        }
                        else{
                            max.first=index(summary_max,cluster.at(summary_max)->maximum());

                        }
                    }
                }
                else if(x==max.first){
                    max.first= index(high(x),cluster.at(high(x))->maximum());

                }

            }

        }





    };



}
