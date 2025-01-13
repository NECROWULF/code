#include <iostream>
#include <string>
#include<vector>

namespace treap{

    template<typename XType, typename YType, typename CounterType = long long>
    struct Node{
        XType x = 0;
        YType y = 0;


        Node* left = nullptr;
        Node* right = nullptr;
    };

    template<typename XType, typename YType>
    struct Treap{
        Node<XType, YType>* root = nullptr;

        void Merge(Treap treap2){
            if(treap2.root == nullptr){
                return;
            }else{
                if(root.x > root.y){
                    return;
                }
            }
        }
    };

    template<typename XType, typename YType>
    void Merge(Treap<XType, YType> treap1, Treap<XType, YType> treap2){

    }
};