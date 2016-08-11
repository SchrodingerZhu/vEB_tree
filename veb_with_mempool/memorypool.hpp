#pragma once
#include <cstddef>
#include <queue>
#include <stdexcept>
#include <memory>
namespace std{
        template <typename T>
        class ObjectPool
        {
                public:
                        ObjectPool(size_t chunkSize = kDefaultChunkSize);
                        ObjectPool(const ObjectPool<T>& src) =delete;
                        ObjectPool<T>& operator=(const ObjectPool<T>& rhs) =delete;
                        using Object =std::shared_ptr<T>;
                        Object acquireObject();

                private:
                        std::queue<std::unique_ptr<T> > mFreeList;
                        size_t mChunkSize;
                        static const size_t kDefaultChunkSize = 2000;
                        void allocateChunk();
        };

//	template <typename T>
//	const size_t ObjectPool<T>::kDefaultChunkSize;

        template <typename T>
        ObjectPool<T>::ObjectPool(size_t chunkSize)
        {
                if(chunkSize==0){
                        throw std::invalid_argument("chunk size must be positive");
                }
                mChunkSize =chunkSize;
                allocateChunk();
        }

        template <typename T>
        void ObjectPool<T>::allocateChunk()

        {
                //cout<<"called"<<endl;
                for(register size_t i=0;i<mChunkSize;++i){
                        mFreeList.emplace(std::make_unique<T>());
                }
        }

        template <typename T>
        typename ObjectPool<T>::Object ObjectPool<T>::acquireObject(){
                if(mFreeList.empty()){
                        allocateChunk();
                }
                std::unique_ptr<T> obj(std::move(mFreeList.front()));
                mFreeList.pop();
                Object smartObject(obj.release(),[ this] (T* t){
                        mFreeList.push(std::unique_ptr<T> (t));
                });
                return smartObject;
        }
}
