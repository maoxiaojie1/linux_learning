#ifndef _SORT_H_2020_2_19_20_17_
#define _SORT_H_2020_2_19_20_17_

typedef unsigned long int size_t;

template <typename T>
class Sort
{
public:
    Sort(T *pData, size_t len) : _pData(pData), _length(len) {};
    ~Sort() {};

    /* 插入排序 */
    void insert()
    {
        for (int i = 1; i < _length; i++)
        {
            T key = _pData[i];
            int j = i - 1;

            /* 找到i位置元素往前插入的位置 */
            while (j >= 0 && _pData[j] > key)
            {
                /* 没找到位置就往后挪一位 */
                _pData[j + 1] = _pData[j];
                --j;
            }

            /* 插入 */
            _pData[j + 1] = key;
        }
    };

    /* 冒泡排序 */
    void bubble()
    {
        for (int i = 1; i < _length; ++i)
        {
            T temp;
            /* 从序列的后面开始往前冒泡，序列的长度是从i到序列结尾*/
            for (int j = _length - 1; j >= i ; --j)
            {
                if (_pData[j - 1] > _pData[j])
                {
                    temp = _pData[j];
                    _pData[j] = _pData[j - 1];
                    _pData[j - 1] = temp;
                }
            } 
        }
    }

    /* 选择排序 */
    void select()
    {
        for (size_t i = 0; i < _length; i++)
        {
            /* 把序列的开始元素作为最小值来初始化 */
            T min = _pData[i];
            size_t index = i;

            /* 从i开始的序列里找到最小值的位置 */
            for (size_t j = i + 1; j < _length; j++)
            {
                if (min > _pData[j])
                {
                    min = _pData[j];
                    index = j;
                }
            }

            /* 如果最小值不是i位置的元素，就交换最小值和i位置的元素 */
            if (i != index)
            {
                _pData[index] = _pData[i];
                _pData[i]  = min;
            }
        }
    }

    /* 快速排序 */
    void fast()
    {
        _fast(0, _length - 1);
    }

    /* 堆排序 */
    void heap()
    {
        /* 构建最大根堆*/
        heapInsert();
        int size = _length;
        while (size > 1)
        {
            /*此时首元素就是最大值，放到数组的后面*/
            swap(_pData[0], _pData[size - 1]);
            size--;
            /* 调整堆成为最大根堆，此时堆中元素数量为size */
            heapify(size);
        } 
    }

    /* 计数排序 */
    void count()
    {
        T maxValue = _pData[0];

        /* 找出序列最大值 */
        for (size_t i = 1; i < _length; i++)
        {
            if (_pData[i] > maxValue)
            {
                maxValue = _pData[i];
            }
        }
        
        /* 创建临时数组 */
        T *tmpData = new T[maxValue + 1]();
        T *sortData = new T[_length]();
        //memset(tmpData, 0, maxValue + 1);
        //memset(sortData, 0, maxValue + 1);

        /* 计数 */
        for (size_t i = 0; i < _length; i++)
        {
            tmpData[_pData[i]]++;
        }
        
        /* 顺序累加 */
        for (size_t i = 1; i < maxValue + 1; i++)
        {
            tmpData[i] += tmpData[i - 1];
        }
        
        /* 把排序好的数据存到sortData里 */
        for (size_t i = 0; i < _length; i++)
        {
            sortData[tmpData[_pData[i]] - 1] = _pData[i];
            tmpData[_pData[i]]--;
        }

        /* 再把sortData数据存回原数组里 */
        for (size_t i = 0; i < _length; i++)
        {
            _pData[i] = sortData[i];
        }

        delete []tmpData;
        delete []sortData;
    }

    void merge()
    {
        T *tempArr = new T[_length]();
        _mergeSort(tempArr, 0, _length - 1);
        delete []tempArr;
    }
private:
    void _fast(int startIndex, int endIndex)
    {
        /* 递归结束条件：序列只有一个元素 */
        if (startIndex >= endIndex)
        {
            return;
        }
        /* 用基准点，将序列一分为二，小的放左边，大的放右边*/
        int maskIndex = partition(startIndex, endIndex);

        /* 递归左边的序列 */
        _fast(startIndex, maskIndex - 1);
        /* 递归右边的序列 */
        _fast(maskIndex + 1, endIndex);
    }

    int partition(int startIndex, int endIndex)
    {
        int left = startIndex;
        int right = endIndex;
        /* 以序列的第一个元素作为基准点, 也可以选择随机点作为基准点，这样可以保证算法性能 */
        T mask = _pData[startIndex];

        while (true) 
        {
            /* 从序列左边开始找，找到不符合条件的数据位置 */
            while (_pData[left] <= mask)
            {
                left++;
                if (left == right)
                {
                    break;
                }
            }
            
            /* 从序列右边开始找，找到不符合条件的数据位置 */
            while (_pData[right] > mask)
            {
                right--;
                if (left == right)
                {
                    right--;
                    break;
                }
            }

            /* 左右边界一样就退出 */
            if (left >= right)
            {
                break;
            }

            /* 交换左右两边不符合条件的数据，这样左右两边就都符合条件了 */
            T tmp = _pData[left];
            _pData[left] = _pData[right];
            _pData[right] = tmp;
        }
        
        /* 最后把基准点插入序列中，这样一个序列就变成了以基准点为标准，大的放右边，小的放左边了 */
        T tmp = _pData[startIndex];
        _pData[startIndex] = _pData[right];
        _pData[right] = tmp;

        /* 把基准点的位置返回 */
        return right;
    }

    void heapInsert()
    {
        /* 通过不断从树下面插入数据，构建最大根堆 */
        for (size_t i = 1; i < _length; i++)
        {
            int currIndex = i;
            int fatherIndex = (currIndex - 1) / 2;

            /* 通过循环不断调整插入数据的位置 */
            while (_pData[currIndex] > _pData[fatherIndex])
            {
                swap(_pData[currIndex], _pData[fatherIndex]);
                /* 把父节点作为当前节点 */
                currIndex = fatherIndex;
                /* 再找到当前节点的父节点 */
                fatherIndex = (currIndex - 1) / 2;
            }
        }
    }

    void heapify(int size)
    {
        /* 找到根节点的左右孩子 */
        int root = 0;
        int left = 2*root + 1;
        int right = 2*root + 2;

        /* 调整堆成为最大根堆 */
        while (left < size)
        {
            /* 找到父节点和孩子节点中最大值 */
            int largestIndex = 0;
            if (_pData[left] < _pData[right] && right < size)
            {
                largestIndex = right;
            }
            else
            {
                largestIndex = left;
            }
            
            if (_pData[root] > _pData[largestIndex])
            {
                largestIndex = root;
            }
            
            /* 如果父节点就是最大值，则结束循环 */
            if (root == largestIndex)
            {
                break;
            }
            
            /* 把最大值与父节点交换*/
            swap(_pData[largestIndex], _pData[root]);

            /* 子树中继续 */
            root = largestIndex;
            left = 2*root + 1;
            right = 2*root + 2;
        }  
    }

    void swap(T &x, T &y)
    {
        T tmp = x;
        x = y;
        y = tmp;
    }

    void _mergeSort(T *tempArr, int startIndex, int endIndex)
    {
        if (startIndex >= endIndex)
        {
            return;
        }
        
        int midIndex = startIndex + (endIndex - startIndex) / 2;
        _mergeSort(tempArr, startIndex, midIndex);
        _mergeSort(tempArr, midIndex + 1, endIndex);
        _merge(tempArr, midIndex, startIndex, endIndex);
    }

    void _merge(T *tempArr, int midIndex, int startIndex, int endIndex)
    {
        int left = startIndex;
        int right = midIndex + 1;
        int k = startIndex;

        while (left <= midIndex && right <= endIndex)
        {
            tempArr[k++] = _pData[left] < _pData[right]? _pData[left++] : _pData[right++];
        }
        
        while (left <= midIndex)
        {
            tempArr[k++] = _pData[left++];
        }
        
        while (right <= endIndex)
        {
            tempArr[k++] = _pData[right++];
        }
        
        for (size_t i = startIndex; i <= endIndex; i++)
        {
            _pData[i] = tempArr[i];
        }
    }

private:
    T *_pData;
    size_t _length;
};


#endif 