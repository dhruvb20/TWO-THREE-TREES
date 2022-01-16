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
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void preorder(struct node *root){
    if(root->n==1){
        cout<<root->leaf_val<<' ';
        return ;
    }
    else{
        cout<<":"<<root->n<<":";
        preorder(root->left);
        preorder(root->middle);
        if(root->right!=NULL){
            preorder(root->right);
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
ll height(struct node *root){
    ll count=0;
    struct node *curr=root;
    while(curr->n!=1){
        curr=curr->left;
        count++;
    }
    return count;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
ll findmin(struct node *root){
    struct node *curr=root;
    while(curr->n!=1){
        curr=curr->left;
    }
    return curr->leaf_val;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
struct return_node *my_merge_right(struct node *root1,struct node *root2,ll diff,ll min_val){
    if(diff==1){
        if(root1->right==NULL){
            struct return_node *tempnode=makenode_type2();
            root1->right=root2;
            root1->n=3;
            root1->k2=min_val;
            tempnode->first=root1;
            return tempnode;
        }
        else{
            struct return_node *tempnode=makenode_type2();
            struct node *helpnode1=makenode();
            struct node *helpnode2=makenode();
            helpnode1->n=2;
            helpnode1->k1=root1->k2;
            helpnode1->left=root1->left;
            helpnode1->middle=root1->middle;
            helpnode2->n=2;
            helpnode2->k1=min_val;
            helpnode2->left=root1->right;
            helpnode2->middle=root2;
            tempnode->first=helpnode1;
            tempnode->second=helpnode2;
            return tempnode;
        }
    }
    {
        if(root1->n==2){
            struct return_node *tempnode=my_merge_right(root1->middle,root2,diff-1,min_val);
            if(tempnode->second==NULL){
                struct node *helpnode=makenode();
                helpnode->k1=root1->k1;
                helpnode->n=2;
                helpnode->left=root1->left;
                helpnode->middle=tempnode->first;
                struct return_node *temp_node=makenode_type2();
                temp_node->first=helpnode;
                return temp_node;
            }
            else{
                struct node *helpnode=makenode();
                helpnode->n=3;
                helpnode->k1=root1->k1;
                helpnode->k2=min_val;
                helpnode->left=root1->left;
                helpnode->middle=tempnode->first;
                helpnode->right=tempnode->second;
                struct return_node *temp_node=makenode_type2();
                temp_node->first=helpnode;
                return temp_node;
            }
        }
        {
            struct return_node *tempnode=my_merge_right(root1->right,root2,diff-1,min_val);
            if(tempnode->second==NULL){
                struct node *helpnode=makenode();
                helpnode->k1=root1->k1;
                helpnode->k2=root1->k2;
                helpnode->n=3;
                helpnode->left=root1->left;
                helpnode->middle=root1->middle;
                helpnode->right=tempnode->first;
                struct return_node *temp_node=makenode_type2();
                temp_node->first=helpnode;
                return temp_node;
            }
            {
                struct node *helpnode1=makenode();
                struct node *helpnode2=makenode();
                helpnode1->n=2;
                helpnode2->n=2;
                helpnode1->k1=root1->k1;
                helpnode1->left=root1->left;
                helpnode1->middle=root1->middle;
                helpnode2->k1=min_val;
                helpnode2->left=tempnode->first;
                helpnode2->middle=tempnode->second;
                struct return_node *temp_node=makenode_type2();
                temp_node->first=helpnode1;
                temp_node->second=helpnode2;
                return temp_node;
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
struct return_node *my_merge_left(struct node *root1,struct node *root2,ll diff,ll min_val){
    if(diff==1){
        if(root2->right==NULL){
            struct return_node *tempnode=makenode_type2();
            struct node *helpnode=makenode();
            helpnode->n=3;
            helpnode->k1=findmin(root2->left);
            helpnode->k2=root2->k1;
            helpnode->left=root1;
            helpnode->middle=root2->left;
            helpnode->right=root2->middle;
            tempnode->first=helpnode;
            return tempnode;
        }
        else{
            struct return_node *tempnode=makenode_type2();
            struct node *helpnode1=makenode();
            struct node *helpnode2=makenode();
            helpnode1->n=2;
            helpnode1->left=root1;
            helpnode1->middle=root2->left;
            helpnode1->k1=findmin(root2->left);
            helpnode2->n=2;
            helpnode2->left=root2->middle;
            helpnode2->middle=root2->right;
            helpnode2->k1=root2->k2;
            tempnode->first=helpnode1;
            tempnode->second=helpnode2;
            tempnode->min=root2->k1;
            return tempnode;
        }
    }
    {
        if(root2->n==2){
            struct return_node *tempnode=my_merge_left(root1,root2->left,diff-1,min_val);
            if(tempnode->second==NULL){
                struct node *helpnode=makenode();
                helpnode->k1=root2->k1;
                helpnode->n=2;
                helpnode->left=tempnode->first;
                helpnode->middle=root2->middle;
                struct return_node *temp_node=makenode_type2();
                temp_node->first=helpnode;
                return temp_node;
            }
            else{
                struct node *helpnode=makenode();
                helpnode->n=3;
                helpnode->k1=tempnode->min;
                helpnode->k2=root2->k2;
                helpnode->left=tempnode->first;
                helpnode->middle=tempnode->second;
                helpnode->right=root2->middle;
                struct return_node *temp_node=makenode_type2();
                temp_node->first=helpnode;
                return temp_node;
            }
        }
        {
            struct return_node *tempnode=my_merge_left(root1,root2->left,diff-1,min_val);
            if(tempnode->second==NULL){
                struct node *helpnode=makenode();
                helpnode->k1=root2->k1;
                helpnode->k2=root2->k2;
                helpnode->n=3;
                helpnode->left=tempnode->first;
                helpnode->middle=root2->middle;
                helpnode->right=root2->right;
                struct return_node *temp_node=makenode_type2();
                temp_node->first=helpnode;
                return temp_node;
            }
            {
                struct node *helpnode1=makenode();
                struct node *helpnode2=makenode();
                helpnode1->n=2;
                helpnode2->n=2;
                helpnode1->k1=tempnode->min;
                helpnode1->left=tempnode->first;
                helpnode1->middle=tempnode->second;
                helpnode2->k1=root2->k2;
                helpnode2->left=root2->middle;
                helpnode2->middle= root2->right;
                struct return_node *temp_node=makenode_type2();
                temp_node->first=helpnode1;
                temp_node->second=helpnode2;
                temp_node->min=root2->k1;
                return temp_node;
            }    
        }
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
struct node *merge(struct node *root1,struct node *root2){
    ll height1=height(root1);
    ll height2=height(root2);
    if(height1==height2){
        struct node *root=makenode();
        root->n=2;
        root->k1=findmin(root2);
        root->left=root1;
        root->middle=root2;
        return root;
    }
    ll diff=abs(height1-height2);
    if(height1>height2){    
        ll min_val=findmin(root2);
        struct return_node *tempnode=my_merge_right(root1,root2,diff,min_val);
        if(tempnode->second==NULL){
            struct node *root=tempnode->first;
            return root;
        }
        {
            struct node *root=makenode();
            root->n=2;
            root->k1=findmin(tempnode->second);
            root->left=tempnode->first;
            root->middle=tempnode->second;
            return root;
        }
    }
    //if(height1<height2)
    {
        ll min_val=findmin(root1);
        struct return_node *tempnode=my_merge_left(root1,root2,diff,min_val);
        if(tempnode->second==NULL){
            return tempnode->first;
        }
        {
            struct node *root=makenode();
            root->n=2;
            root->k1=tempnode->min;
            root->left=tempnode->first;
            root->middle=tempnode->second;
            return root;
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
struct return_node *insert(struct node *root,ll val){
    if(root->n==1){
        if(root->leaf_val==val){
            struct return_node *tempnode=makenode_type2();
            tempnode->first=root;
            return tempnode;
        }
        else if(root->leaf_val<val){
            struct return_node *tempnode=makenode_type2();
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
            struct return_node *tempnode=makenode_type2();
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
    }
    //if(root->n==3)
    {
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
        //if(val>root->k2)
        {
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
            {
                struct node *helpnode1=makenode();
                struct node *helpnode2=makenode();
                helpnode1->n=2;
                helpnode2->n=2;
                helpnode1->k1=root->k1;
                helpnode1->left=root->left;
                helpnode1->middle=root->middle;
                helpnode2->k1=tempnode->min;
                helpnode2->left=tempnode->first;
                helpnode2->middle=tempnode->second;
                struct return_node *temp_node2=makenode_type2();
                temp_node2->first=helpnode1;
                temp_node2->second=helpnode2;
                temp_node2->min=root->k2;
                return temp_node2;
            }
        }
    }   
}
//------------------------------------------------------------------------------------------------------------------------------------------------------
struct node *insert_root(struct node *root,ll val){
    if(root==NULL){
        struct node *newnode=makenode();
        newnode->n=1;
        newnode->leaf_val=val;   
        return newnode;
    }
    if(root->n==0){
        root->n=1;
        root->leaf_val=val;   
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
            root->k1=root->leaf_val;
            root->n=2;
            return root;
        }
        else if(val>root->leaf_val){
            struct node *temp1=makenode();
            struct node *temp2=makenode();
            temp1->n=1;
            temp2->n=1;
            temp1->leaf_val=root->leaf_val;
            temp2->leaf_val=val;
            root->left=temp1;
            root->middle=temp2;
            root->n=2;
            root->k1=val;
            return root;
        }
    }
    struct return_node *tempnode=insert(root,val);
    if(tempnode->second==NULL){
        return tempnode->first;
    }
    {
        struct node *helpnode=makenode();
        helpnode->n=2;
        helpnode->k1=tempnode->min;
        helpnode->left=tempnode->first;
        helpnode->middle=tempnode->second;
        return helpnode;
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
ll heightright(struct node *root){
    struct node *curr=root;
    ll count=0;
    while(curr->n!=1){
        curr=curr->middle;
        count++;
    }
    return count;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(){
    struct node *root=insert_root(NULL,1);
    for(ll i=2;i<20;i++){
        struct node *temp=insert_root(NULL,i);
        root=merge(root,temp);
    }   
    struct node *rootnew=insert_root(NULL,777);
    for(ll i=778;i<1000;i++){
        struct node *temp=insert_root(NULL,i);
        rootnew=merge(rootnew,temp);
    }
    root=merge(root,rootnew);
    preorder(root);
    cout<<endl;
    cout<<height(root)<<"}}||"<<heightright(root);
}