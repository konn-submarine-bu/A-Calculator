#ifndef VECTOR_H
#define VECTOR_H


typedef int Rank;
#define default_capacity 10
template <typename T> class vector
{
    protected:
        Rank _size;
        int _capacity;
        T* _elem;
        void copyfrom(T const* A,Rank lo,Rank hi);                //复制  A[lo,hi)
    public:
        //构造函数
        vector(int c=default_capacity,int s=0,T e=0)             //默认构造函数
        {_elem=new T[_capacity=c];
        for(_size=0;_size<s;_elem[_size++]=e);
        }
        vector(T const* A,Rank n)                               //数组整体复制
        {
            copyfrom(A,0,n);
        }                                                      //s<=c
        vector(T const* A,Rank lo,Rank hi)                    //数组区间复制
        {
            copyfrom(A,lo,hi);
        }
        vector(vector<T> const* V)                            //向量整体复制
        {
            copyfrom(V,0,V->size());
        }
        vector(vector<T> const* V,Rank lo,Rank hi)           //向量区间复制
        {
            copyfrom(V,lo,hi);
        }
        //析构函数
        ~vector()
        {
            delete [] _elem;
        }
        //只读访问接口
        int size() const { return _size;}                   //获取规模
        bool empty() const {return !_size;}                 //判断是否为空
        T get(int r) const{return _elem[r];}                //取得秩为r的元素
        Rank find(T const & e,Rank lo,Rank hi) const;       //无序向量区间查找，返回最大的秩 ，失败时返回lo-1，元素类型T必须为基本类型或已重载运算符
        Rank find(T const & e) const                        //无序向量整体查找
        {
            return find(e,0,_size);
        }
        //可写访问接口
        T* getPos(int r)const 
		{
			T* pos=_elem;
			while(0<r--)
			{
				pos++;
			}
			return pos;
		} 
        T& operator[](Rank r) const                        //重载下标操作符，可以类似于数组引用
        {
            return this->_elem[r];
        }
        vector<T>& operator = (vector<T> const &V )          //重载赋值运算符，直接克隆向量
        {
            copyfrom(V,0,V.size());
        }
        void expand();                                      //扩容
        void shrink();                                      //缩容
        int remove(Rank lo,Rank hi);                        //区间删除元素，返回删除元素个数
        T remove(Rank r)                                  //删除秩为r的元素，返回元素
        {
            T e=_elem[r];
            remove(r,r+1);
            return e;
        }
        Rank insert(Rank r ,T const &e);                    //插入
        Rank insert(T const& e)                             //作为末元素插入
        {
            return insert(_size,e);
        }

 };
template <typename T>
void vector<T>::copyfrom(T const* A,Rank lo,Rank hi)
{
    _elem=new T[_capacity=2*(hi-lo)];
    _size=0;
    while(lo<hi)
    {
        _elem[_size++]=A[lo++];                          //复制  A[lo,hi)
    }
}
template <typename T>
Rank vector<T>::find(T const & e,Rank lo,Rank hi) const
{
    while((lo<hi--)&&(e!=_elem[hi]));
    return hi;
}
template <typename T>
void vector<T>::expand()
{
    if(_size<_capacity) return;
    if(_capacity<default_capacity) _capacity=default_capacity;//不低于最小容量
    T* oldelem=_elem;
    _elem=new T[_capacity<<=1];
    for(int i=0;i<_size;i++) _elem[i]=oldelem[i];
    delete [] oldelem;
}
template <typename T>
void vector<T>::shrink()
{
    if(_capacity<default_capacity<<1) return;                //不至于收缩到最小容量以下
    if(_size>>2>_capacity) return;                           //以25%为界
    T* oldelem=_elem;
    _elem=new T[_capacity>>=1];
    for(int i=0;i<_size;i++) _elem[i]=oldelem[i];
    delete [] oldelem;
}
template <typename T>
int vector<T>::remove(Rank lo,Rank hi)
{
    if(lo==hi)return 0;                                      //出于效率，单独考虑退化情况
    while(hi<_size) _elem[lo++]=_elem[hi++];                  //删除区间[lo,hi)
    _size=lo;
    shrink();                                                //若必要，缩容
    return hi-lo;
}
template <typename T>
Rank vector<T>::insert(Rank r ,T const &e)
{
    expand();                                                //若有必要，扩容
    for(int i=_size;i>r;i--) _elem[i]=_elem[i-1];
    _elem[r]=e;
    _size++;
    return r;
}



#endif // VECTOR_H
