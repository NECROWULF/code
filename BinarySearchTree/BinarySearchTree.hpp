namespace BinarySearchTree{
    template<typename T>
    class BinarySearchTree{
    private:
        T value;
        BinarySearchTree<T>* left = nullptr;
        BinarySearchTree<T>* right = nullptr;
    public:
        BinarySearchTree(T value){
            this->value = value;
            left = nullptr;
            right = nullptr;
        }
        bool Find(T value){
            if(this->value == value){
                return true;
            }
            if(this->value > value){
                return this->right && this->right->Find(value);
            }
            if(this->value < value){
                return this->left && this->left->Find(value);
            }
        }
        void Add(T value){
            if(this->value == value){
                //do smth if elements are repeated
                return;
            }
            if(this->value > value){
                if(this->right){
                    this->right->Add(value);
                    return;
                }
                this->right = new BinarySearchTree(value);
            }
            if(this->value < value){
                if(this->left){
                    this->left->Add(value);
                    return;
                }
                this->left = new BinarySearchTree(value);
            }
        }
    };
}
