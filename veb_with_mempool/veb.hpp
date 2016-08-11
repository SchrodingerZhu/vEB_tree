#pragma once
#include <cmath>
#include <functional>
#include <memory>
#include <vector>
#include <iostream>
#include "memorypool.hpp"
namespace std {

    struct vEB{



        long long upper,lower,u;
        long long _min_,_max_;
        shared_ptr<vEB > summary;
        vector< shared_ptr<vEB > > cluster;
        typedef  shared_ptr<vEB > vEB_ptr;
        void e_min_sert(long long x){
            _min_=_max_=x;
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
            return _max_;
        }

        long long minimum(){
            return _min_;
        }

     	bool member(long long b){
            if(b==_max_||b==_min_)
                return true;
            else if(u==2) return false;
            else return cluster[high(b)]->member(low(b));
        }

        void insert(long long x){
            if(_min_==-1) e_min_sert(x);
            else {
                if (x<_min_){
                    swap(_min_,x);
                }
                if (u>2){
                    if(cluster.at(high(x))->minimum()==-1){
                        summary->insert(high(x));
                        cluster.at(high(x))->e_min_sert(low(x));
                    }
                    else{
                        cluster.at(high(x))->insert(low(x));
                    }
                }
                if(x>_max_){
                    _max_=x;
                }
            }
        }
        long long successor(long long x){
            if(u==2) {
                if(x==0&&_max_==1){
                    return 1;
                }else return -1;
            }
            else if(_min_!=-1&&x<_min_){
                return _min_;
            }
            else {
                long long _max__low=cluster.at(high(x))->maximum();
                if (_max__low!=-1&&low(x)<_max__low){
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
                if(x==1&&_min_==0) return 0;
                else return -1;
            }
            else if(_max_!=-1&&x>_max_){
                return _max_;
            }
            else{
                long long _min__low=cluster.at(high(x))->minimum();
                if(_min__low!=-1&&low(x)>_min__low){
                    long long offset = cluster.at(high(x))->predecessor(low(x));
                    return index(high(x),offset);
                }
                else{
                    long long pred_cluster = summary->predecessor(high(x));
                    if(pred_cluster==-1){
                        if (_min_!=-1&&x>_min_) return _min_;
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
            if(_min_==_max_){
                _min_=_max_=-1;
            }
            else if(u==2){
                if (x==0) {
                    _min_=1;
                }
                else _min_=0;
                _max_=_min_;
            }
            else{
                if(x==_min_){
                    long long first_cluster = summary->minimum();
                    x=index(first_cluster,cluster.at(first_cluster)->minimum());
                    _min_=x;
                }
                cluster.at(high(x))->erase(low(x));
                if (cluster.at(high(x))->minimum()==-1){
                    summary->erase(high(x));
                    if(x==_max_){
                        long long summary__max_=summary->maximum();
                        if(summary__max_==-1){
                            _max_=_min_;

                        }
                        else{
                            _max_=index(summary__max_,cluster.at(summary__max_)->maximum());

                        }
                    }
                }
                else if(x==_max_){
                    _max_= index(high(x),cluster.at(high(x))->maximum());

                }

            }

        }





    };
    class vEB_tree{
        ObjectPool<vEB> pool;
        shared_ptr<vEB> root;
        void init(long long i,shared_ptr<vEB>& t){
            t->u=i;
            t->_min_=t->_max_=-1;
            t->upper=pow(2,ceil( (log( t->u )/log(2)) / 2.0 ));
            t->lower=pow(2,floor( (log( t->u )/log(2)) / 2.0 ));
            if(i==2){
                t->summary=nullptr;
                t->cluster.resize(0);
            }else{
                t->summary=pool.acquireObject();
                init(t->upper,t->summary);
                for(long long i=0;i<t->upper;i++){
                    t->cluster.push_back(pool.acquireObject());
                    init(t->lower,t->cluster.back());
                }
            }
        }
    public:
        vEB_tree(long long i=2){
	    root=pool.acquireObject();
            init(i,root);
        }
	bool member(long long b){
		return root->member(b);
	}
        void insert(long long x){
		root->insert(x);
        }
	long long maximum(){
            return root->_max_;
        }

        long long minimum(){
            return root->_min_;
        }
	long long successor(long long x){
		return root->successor(x);
	}
	long long predecessor(long long x){
		return root->predecessor(x);
	}
	void erase(long long x){
		root->erase(x);
        }
	

	

    };

}
