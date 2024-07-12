template <typename T>
struct Node
{
    Node(T d, Node<T>* r = nullptr, Node<T>* l = nullptr)
        : data{d}
        , left{l}
        , right{r}
    {}
    

    Node<T>* left;
    Node<T>* right;

    T data;
};
