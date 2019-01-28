// #include <stdio.h>
// #include <string.h>

// int main() {

//     return 0;
// }

// void insertNewFirstNode(AirportCode A, NodeType** L) {
//     NodeType* new = (NodeType*)malloc(sizeof(NodeType)); //casting mallox aout 
//     strcp(A, new->Airport);


//     new->Link = *L;

// }

// void deleteFirst(NodeType** L) {

//     if(*L != NULL && (*L)->Link) { //full list
//         NodeType* to_del = *L;
//         *L = *L->Link;
//         free(to_del);
//         return;
//     } 
//     free(*L);
//     return;
// }