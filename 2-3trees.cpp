#include<iostream>
using namespace std;
typedef long long ll;
struct node{
    ll n;
    ll k1,k2;
    struct node *left;
    struct node *right;
    struct node *middle;
    ll leaf_val;
};
struct return_node{
    struct node *first;
    struct node *second;
    ll min;
};
struct return_nodedel{
    struct node *first;
    ll min;
};
struct node *makenode(){
    struct node *newnode=(struct node *)malloc(sizeof(struct node));
    newnode->n=0;
    newnode->k1=-1;
    newnode->k2=-1;
    newnode->left=NULL;
    newnode->middle=NULL;
    newnode->right=NULL;
    return newnode;
}
struct return_node *makenode_type2(){
    struct return_node *newnode=(struct return_node *)malloc(sizeof(struct return_node));
    newnode->first=NULL;
    newnode->second=NULL;
    newnode->min=-1;
    return newnode;
}
struct return_nodedel *makenode_type3(){
    struct return_nodedel *newnode=(struct return_nodedel *)malloc(sizeof(struct return_nodedel));
    newnode->first=NULL;
    newnode->min=-1;
    return newnode;
}
struct node *insert_root(struct node *root,ll val){
    if(root->n==0){
        root->n=1;
        root->leaf_val=val;   // Null root becomes a leaf
        return root;
    }
    if(root->n==1){
        if(root->leaf_val==val){
            return root;
        }
        else if(val<root->leaf_val){
            struct node *temp1=makenode();
            struct node *temp2=makenode();
            temp1->n=1;
            temp2->n=1;
            temp1->leaf_val=val;
            temp2->leaf_val=root->leaf_val;
            root->left=temp1;
            root->middle=temp2;
            root->k1=val;
            return root;
        }
        else if(val>root->leaf_val){
            struct node *temp1=makenode();
            struct node *temp2=makenode();
            temp1->n==1;
            temp2->n==1;
            temp1->leaf_val=val;
            temp2->leaf_val=root->leaf_val;
            root->left=temp2;
            root->middle=temp2;
            root->k1=root->leaf_val;
            return root;
        }
    }
    struct return_node *tempnode=insert(root,val);
    if(tempnode->second==NULL){
        return tempnode->second;
    }
    else{
        struct node *helpnode=makenode();
        helpnode->n=2;
        helpnode->k1=tempnode->min;
        helpnode->left=tempnode->first;
        helpnode->middle=tempnode->second;
        return helpnode;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------
struct return_node *insert(struct node *root,ll val){
    if(root->n==1){
        if(root->leaf_val==val){
            struct return_node *tempnode=makenode_type2();
            tempnode->first=root;
            return tempnode;
        }
        else if(root->leaf_val<val){
            struct return_node *tempnode=makenode_type2();
            tempnode->first=root;
            struct node *temp2=makenode();
            temp2->n=1;
            temp2->leaf_val=val;
            tempnode->first=root;
            tempnode->second=temp2;
            tempnode->min=val;
            return tempnode;
        }
        else if(root->leaf_val>val){
            struct return_node *tempnode=makenode_type2();
            struct node *temp2=makenode();
            temp2->n=1;
            temp2->leaf_val=val;
            tempnode->second=root;
            tempnode->first=temp2;
            tempnode->min=root->leaf_val;
            return tempnode;
        }
    }
    if(root->n==2){
        if(val<root->k1){
            struct return_node *tempnode=insert(root->left,val);
            if(tempnode->second==NULL){
                struct node *helpnode=makenode();
                helpnode->n=2;
                helpnode->k1=root->k1;
                helpnode->left=tempnode->first;
                helpnode->middle=root->middle;
                struct return_node *temp_node2=makenode_type2();
                temp_node2->first=helpnode;
                return temp_node2;
            }
            else{
                struct node *helpnode=makenode();
                helpnode->n=3;
                helpnode->k1=tempnode->min;
                helpnode->k2=root->k1;
                helpnode->left=tempnode->first;
                helpnode->middle=tempnode->second;
                helpnode->right=root->middle;
                struct return_node *temp_node2=makenode_type2();
                temp_node2->first=helpnode;
                return temp_node2;
            }
        }
        if(val==root->k1){
            struct return_node *tempnode;
            tempnode->first=root;
            return tempnode;
        }
        if(val>root->k1){
            struct return_node *tempnode=insert(root->middle,val);
            if(tempnode->second==NULL){
                struct node *helpnode=makenode();
                helpnode->n=2;
                helpnode->k1=root->k1;
                helpnode->left=root->left;
                helpnode->middle=tempnode->first;
                struct return_node *temp_node2=makenode_type2();
                temp_node2->first=helpnode;
                return temp_node2;
            }
            else{
                struct node *helpnode=makenode();
                helpnode->n=3;
                helpnode->k1=root->k1;
                helpnode->k2=tempnode->min;
                helpnode->left=root->left;
                helpnode->middle=tempnode->first;
                helpnode->right=tempnode->second;
                struct return_node *temp_node2=makenode_type2();
                temp_node2->first=helpnode;
                return temp_node2;
            }
        }
        if(root->n==3){
            if(val<root->k1){
                struct return_node *tempnode=insert(root->left,val);
                if(tempnode->second==NULL){
                    struct node *helpnode=makenode();
                    helpnode->n=3;
                    helpnode->k1=root->k1;
                    helpnode->k2=root->k2;
                    helpnode->left=tempnode->first;
                    helpnode->middle=root->middle;
                    helpnode->right=root->right;
                    struct return_node *temp_node2=makenode_type2();
                    temp_node2->first=helpnode;
                    return temp_node2;
                }
                else{
                    struct node *helpnode1=makenode();
                    struct node *helpnode2=makenode();
                    helpnode1->n=2;
                    helpnode2->n=2;
                    helpnode1->k1=tempnode->min;
                    helpnode1->left=tempnode->first;
                    helpnode1->middle=tempnode->second;
                    helpnode2->k1=root->k2;
                    helpnode2->left=root->middle;
                    helpnode2->middle=root->right;
                    struct return_node *temp_node2=makenode_type2();
                    temp_node2->first=helpnode1;
                    temp_node2->second=helpnode2;
                    temp_node2->min=root->k1;
                    return temp_node2;
                }
            }
            if(val==root->k1){
                struct return_node *temp_node2=makenode_type2();
                temp_node2->first=root;
                return temp_node2;
            }
            if(val>root->k1&&val<root->k2){
                struct return_node *tempnode=insert(root->middle,val);
                if(tempnode->second==NULL){
                    struct node *helpnode=makenode();
                    helpnode->n=3;
                    helpnode->k1=root->k1;
                    helpnode->k2=root->k2;
                    helpnode->left=root->left;
                    helpnode->middle=tempnode->first;
                    helpnode->right=root->right;
                    struct return_node *temp_node2=makenode_type2();
                    temp_node2->first=helpnode;
                    return temp_node2;
                }
                else{
                    struct node *helpnode1=makenode();
                    struct node *helpnode2=makenode();
                    helpnode1->n=2;
                    helpnode2->n=2;
                    helpnode1->k1=root->k1;
                    helpnode1->left=root->left;
                    helpnode1->middle=tempnode->first;
                    helpnode2->k1=tempnode->min;
                    helpnode2->left=tempnode->second;
                    helpnode2->middle=root->right;
                    struct return_node *temp_node2=makenode_type2();
                    temp_node2->first=helpnode1;
                    temp_node2->second=helpnode2;
                    temp_node2->min=root->k2;
                    return temp_node2;
                }
            }
            if(val==root->k2){
                struct return_node *temp_node2=makenode_type2();
                temp_node2->first=root;
                return temp_node2;
            }
            if(val>root->k2){
                struct return_node *tempnode=insert(root->right,val);
                if(tempnode->second==NULL){
                    struct node *helpnode=makenode();
                    helpnode->n=3;
                    helpnode->k1=root->k1;
                    helpnode->k2=root->k2;
                    helpnode->left=root->left;
                    helpnode->middle=root->middle;
                    helpnode->right=tempnode->first;
                    struct return_node *temp_node2=makenode_type2();
                    temp_node2->first=helpnode;
                    return temp_node2;
                }
                else{
                    struct node *helpnode1=makenode();
                    struct node *helpnode2=makenode();
                    helpnode1->n=3;
                    helpnode2->n=3;
                    helpnode1->k1=root->k1;
                    helpnode1->left=root->left;
                    helpnode1->middle=root->middle;
                    helpnode2->k1=tempnode->min;
                    helpnode2->left=tempnode->first;
                    helpnode2->middle=tempnode->first;
                    struct return_node *temp_node2=makenode_type2();
                    temp_node2->first=helpnode1;
                    temp_node2->second=helpnode2;
                    temp_node2->min=root->k2;
                    return temp_node2;
                }
            }
        }
    }
// -----------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------   
}
struct return_nodedel *deletenode(struct node *root,ll val){
    if(root->n==2&&root->left->n==1&&root->middle->n==1&&root->right==NULL){
        if(val==root->left->leaf_val){
            struct node *tempnode=makenode();
            tempnode->n=1;
            tempnode->leaf_val=root->middle->leaf_val;
            struct return_nodedel *temp_node2=makenode_type3();
            temp_node2->first=tempnode;
            temp_node2->min=root->middle->leaf_val;
            return temp_node2;
        }
        if(val==root->middle->leaf_val){
            struct node *tempnode=makenode();
            tempnode->n=1;
            tempnode->leaf_val=root->left->leaf_val;
            struct return_nodedel *temp_node2=makenode_type3();
            temp_node2->first=tempnode;
            temp_node2->min=root->left->leaf_val;
            return temp_node2;
        }
        else{
            struct return_nodedel *temp_node=makenode_type3();
            temp_node->first=root;
            temp_node->min=root->left->leaf_val;
            return temp_node;
        }
    }
    if(root->n==2&&root->left->n==1&&root->middle->n==1&&root->right->n==1){
        if(val==root->left->leaf_val){
            struct node *tempnode=makenode();
            tempnode->n=2;
            struct node *tempnode1=root->middle;
            struct node *tempnode2=root->right;
            tempnode->left=tempnode1;
            tempnode->middle=tempnode2;
            tempnode->k1=root->k2;
            struct return_nodedel *temp_node=makenode_type3();
            temp_node->first=tempnode;
            temp_node->min=root->middle->leaf_val;
            return temp_node;
        }
        if(val==root->middle->leaf_val){
            struct node *tempnode=makenode();
            tempnode->n=2;
            struct node *tempnode1=root->left;
            struct node *tempnode2=root->right;
            tempnode->left=tempnode1;
            tempnode->middle=tempnode2;
            tempnode->k1=root->k2;
            struct return_nodedel *temp_node=makenode_type3();
            temp_node->first=tempnode;
            temp_node->min=root->left->leaf_val;
            return temp_node;
        }
        if(val==root->right->leaf_val){
            struct node *tempnode=makenode();
            tempnode->n=2;
            struct node *tempnode1=root->left;
            struct node *tempnode2=root->middle;
            tempnode->left=tempnode1;
            tempnode->middle=tempnode2;
            tempnode->k1=root->k1;
            struct return_nodedel *temp_node=makenode_type3();
            temp_node->first=tempnode;
            temp_node->min=root->left->leaf_val;
            return temp_node;
        }
        else{
            struct return_nodedel *temp_node=makenode_type3();
            temp_node->first=root;
            temp_node->min=root->left->leaf_val;
            return temp_node;
        }
    }
    if(root->n==2){
        if(val<root->k1){
            struct return_nodedel *tempnode=makenode_type3();
            tempnode=deletenode(root->left,val);
            if(tempnode->first->n!=1){
                struct return_nodedel *temp_node=makenode_type3();
                struct node *helpnode=makenode();
                helpnode->n=2;
                helpnode->k1=root->k1;
                helpnode->left=tempnode->first;
                helpnode->middle=root->middle;
                temp_node->first=helpnode;
                temp_node->min=tempnode->min;
                return temp_node;
            }
            else{
                if(root->middle->n==3){
                    struct node *helpnode1=makenode();
                    struct node *helpnode2=makenode();
                    helpnode1->k1=root->k1;
                    helpnode1->left=tempnode->first;
                    helpnode1->middle=root->middle->left;
                    helpnode2->k1=root->middle->k2;
                    helpnode2->left=root->middle->middle;
                    helpnode2->right=root->middle->right;
                    struct node *helpnode3=makenode();
                    helpnode3->n=2;
                    helpnode3->k1=root->middle->k1;
                    helpnode3->left=helpnode1;
                    helpnode3->middle=helpnode3;
                    struct return_nodedel *temp_node=makenode_type3();
                    temp_node->first=helpnode3;
                    temp_node->min=tempnode->min;
                    return temp_node;
                }
                if(root->middle->n==2){
                    struct node *helpnode=makenode();
                    helpnode->n=3;
                    helpnode->k1=root->k1;
                    helpnode->k2=root->middle->k1;
                    helpnode->left=tempnode->first;
                    helpnode->middle=root->middle->left;
                    helpnode->right=root->middle->middle;
                    struct return_nodedel *temp_node=makenode_type3();
                    temp_node->first=helpnode;
                    temp_node->min=tempnode->min;
                    return temp_node;
                }
            }
        }
        if(val>=root->k1){
            struct return_nodedel *tempnode=deletenode(root->left,val);
            if(tempnode->first->n!=1){
                struct node *helpnode=makenode();
                helpnode->n=2;
                helpnode->k1=tempnode->min;
                helpnode->left=root->left;
                helpnode->right=tempnode->first;
                struct return_nodedel *temp_node=makenode_type3();
                temp_node->first=helpnode;
                //temp_node->min=helpnode;
            }
        }
    }
}
struct node *delete_root(struct node *root,ll val){
    if(root==NULL){
        return root;
    }
    if(root->n==0){
        return NULL;
    }
    if(root->n==1){
        if(val==root->leaf_val){
            return NULL;
        }
        else{
            return root;
        }
    }
    struct return_nodedel *tempnode=deletenode(root,val);
}
int main(){
    struct node *root=makenode();
}