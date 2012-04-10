#pragma once

#include "Misc/Assert.h"
#include "Misc/Utils.h"
#include <ostream>
#include <vector>


template<class T>
void ReorderUpwards(std::vector<T>& heap, int nd)
{
    while((nd>1) && (heap[nd/2] < heap[nd]))
    {
        Swap(heap[nd/2], heap[nd]);
        nd /= 2;
    }
}

template<class T>
void ReorderDownwards(std::vector<T>& heap, int nd, int heapsize)
{
    while(2*nd <= heapsize)
    {
        int child = 2 * nd;

        if((child < heapsize) && (heap[child] < heap[child+1]))
        {
            ++child;
        }

        if(heap[nd] < heap[child])
        {
            Swap(heap[child], heap[nd]);
            nd = child;
        }
        else
        {
            break;
        }
    }
}

/**
    2-way heap based priority queue. Highest value has the highest priority
*/
template<class T>
class PriorityQ
{
private:
    std::vector<T> heap_;
    int            size_;
    int            maxSize_;

    void ReorderUpwards(std::vector<T>& heap, int nd)
    {
        while((nd > 1) && (heap[nd/2] < heap[nd]))
        {
            Swap(heap[nd/2],heap[nd]);
            nd /= 2;
        }
    }

    void ReorderDownwards(std::vector<T>& heap, int nd, int heapsize)
    {
        while(2*nd <= heapsize)
        {
            int child = 2 * nd;

            if((child < heapsize) && (heap[child] < heap[child+1]))
            {
                ++child;
            }

            if(heap[nd] < heap[child])
            {
                Swap(heap[child], heap[nd]);
                nd = child;
            }
            else
            {
                break;
            }
        }
    }

public:

    PriorityQ(int maxsize) : maxSize_(maxsize), size_(0)
    {
        heap_.assign(maxSize_+1,T());
    }

    bool Empty() const
    {
        return size_ == 0;
    }

    void Insert(const T elem)
    {
        Assert(size_+1 <= maxSize_);
        ++size_;
        heap_[size_] = elem;
        ReorderUpwards(heap_,size_);
    }

    T Pop()
    {
        Swap(heap_[1],heap_[size_]);
        ReorderDownwards(heap_, 1, size_-1);
        return heap_[size--];
    }

    const T& Peek() const
    {
        return heap_[1];
    }
};

/**
    2-way heap al' prednost dobija onaj sa najmanjim prioritetom
*/

template<class T>
class PriorityQL
{
private:

    std::vector<T> heap_;
    int            size_;
    int            maxSize_;

    void ReorderUpwards(std::vector<T>& heap, int nd)
    {
        while((nd > 1) && (heap[nd/2] > heap[nd]))
        {
            Swap(heap[nd/2],heap[nd]);
            nd /= 2;
        }
    }

    void ReorderDownwards(std::vector<T>& heap, int nd, int heapsize)
    {
        while(2*nd <= heapsize)
        {
            int child = 2 * nd;

            if((child < heapsize) && (heap[child] > heap[child+1]))
            {
                ++child;
            }

            if(heap[nd] > heap[child])
            {
                Swap(heap[child], heap[nd]);
                nd = child;
            }
            else
            {
                break;
            }
        }
    }

public:

    PriorityQL(int maxsize) : maxSize_(maxsize), size_(0)
    {
        heap_.assign(maxSize_+1,T());
    }

    bool Empty() const
    {
        return size_ == 0;
    }

    void Insert(const T elem)
    {
        Assert(size_+1 <= maxSize_);
        ++size_;
        heap_[size_] = elem;
        ReorderUpwards(heap_,size_);
    }

    T Pop()
    {
        Swap(heap_[1],heap_[size_]);
        ReorderDownwards(heap_, 1, size_-1);
        return heap_[size--];
    }

    const T& Peek() const
    {
        return heap_[1];
    }
};

/**
    2-way heap based priority queue based on an index into a set of keys.
    Prioritet ima element sa najmanjom vrednoscu.
*/
template<class TKeyType>
class IndexedPriorityQL
{
private:
        std::vector<TKeyType>& vecKeys_;
        std::vector<int>       heap_;
        std::vector<int>       invHeap_;
        int                    size_,
                               maxSize_;

        void Swap(int a, int b)
        {
            int temp = heap_[a];
            heap_[a] = heap_[b];
            heap_[b] = temp;
            invHeap_[heap_[a]] = a;
            intHeap_[heap_[b]] = b;
        }

        void ReorderUpwards(int nd)
        {
            //move up the heap swapping the elements until the heap is ordered
            while ( (nd>1) && (m_vecKeys[m_Heap[nd/2]] > m_vecKeys[m_Heap[nd]]) )
            {
                Swap(nd/2, nd);

                nd /= 2;
            }
        }


        void ReorderDownwards(int nd, int HeapSize)
        {
            //move down the heap from node nd swapping the elements until
            //the heap is reordered
            while (2*nd <= HeapSize)
            {
                int child = 2 * nd;

                //set child to smaller of nd's two children
                if ((child < HeapSize) && (m_vecKeys[m_Heap[child]] > m_vecKeys[m_Heap[child+1]]))
                {
                    ++child;
                }

                //if this nd is larger than its child, swap
                if (m_vecKeys[m_Heap[nd]] > m_vecKeys[m_Heap[child]])
                {
                    Swap(child, nd);

                    //move the current node down the tree
                    nd = child;
                }

                else
                {
                    break;
                }
            }
        }

    public:
        IndexedPriorityQL(std::vector<TKeyType>& keys,
                          int                    maxSize) : vecKeys_(keys),
                                                            maxSize_(maxSize),
                                                            size_(0)
        {
            heap_.assign(maxSize_+1,0);
            invHeap_.assign(maxSize_+1,0);
        }

        const bool Empty() const
        {
            return size_ == 0;
        }

        void Insert(const int ind)
        {
            Assert(size_+1 <= maxSize_);
            ++size_;
            heap_[size_] = ind;
            invHeap_[ind] = size_;
            ReorderUpwards(size_);
        }

        int Pop()
        {
            Swap(1, size_);
            ReorderDownwards(1, size_-1);
            return heap_[size_--];
        }

        void ChangePriority(const int ind)
        {
            ReorderUpwards(invHeap_[ind]);
        }
};
