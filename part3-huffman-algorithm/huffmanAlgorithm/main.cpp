#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <fstream>

#define FNAME "2.txt"
#define CODED_FILE "ofstreamcode.txt"
#define FDECODED "decoded.txt"

using namespace std;

class Node {
public:
    int quan;   //quantity appearing
    char c;     //our symbol char
    Node *left, *right;

    Node() {}

    Node(Node *L, Node *R){
        left = L;
        right = R;
        c = NULL;
        quan = L->quan + R->quan;
    }
};



//sort list of node pointers
struct sortList{
    bool operator()(Node* l, Node* r) const
    {return l->quan < r->quan;}
};

//print tree
void print(Node *root, unsigned k = 0){
    if(root != NULL){
        print(root->left,k+3);
        for(unsigned i = 0; i < k; i++){
            cout << "   ";
        }
        if(root->c != NULL){
            cout << root->quan << " (" << root->c << ")" <<endl;
        }else{
            cout << root->quan << endl;
        }
        print(root->right, k+3);
    }
}

vector<bool> code; //binary code of symbol
map<char, vector<bool> > table; //char and his binary code
//create a table of code for each character
void createTableOfEncodedCharacters(Node *root){
    if(root->left != NULL){
        code.push_back(0);
        createTableOfEncodedCharacters(root->left);
    }
    if(root->right != NULL){
        code.push_back(1);
        createTableOfEncodedCharacters(root->right);
    }
    if(root->c){
        table[root->c]=code;
    }
    code.pop_back(); //delete one symbol and come back to parent node and work further
}

//make list of pointers to Node from mapChar
list <Node*> createListOfKeyValuePair(map<char, int> mapChar){
    list <Node*> lPoin;
    map<char, int>:: iterator i;
    for(i = mapChar.begin(); i != mapChar.end(); ++i){
        Node *p = new Node;
        p->c = i->first;
        p->quan = i->second;
        p->left = NULL;
        p->right = NULL;
        lPoin.push_back(p);
    }
    //checking what we create (optional)
    //    list<Node*> lPointers2 = lPoin;
    //    lPointers2.sort(sortList());
    //    while(!lPointers2.empty()){
    //        Node* p = lPointers2.front();
    //        cout << p->c << " : " << p->quan << endl;
    //        lPointers2.pop_front();
    //    }
    return lPoin;
}

// make map from file map<char, int> where char is one symbol and int quantity of appearing
map<char, int> makeMapOfFile(char* fName){
    char n; //to read one character
    ifstream str(fName, ios::binary);
    //create MAP for all symbols in our string and quantity of their appear
    map<char, int> mapChar;
    //go throught string. Count elements(char)
    while (str.get(n)) {
        mapChar[n]++;
    }
    str.close();
    //show my map (optional)
    //        map<char, int> :: iterator j;
    //        for(j = mapChar.begin(); j != mapChar.end(); j++){
    //            cout << j->first << " : " << j->second << endl;
    //        }
    return mapChar;
}

//create binary tree of Huffman
void createBinaryHuffmanTree(list <Node*> &lPointers){
    while (lPointers.size() != 1) {
        lPointers.sort(sortList()); //sorting list

        //peek and pop smalest two elements in list
        Node *sonL = lPointers.front();
        lPointers.pop_front();
        Node *sonR = lPointers.front();
        lPointers.pop_front();

        Node *parent = new Node (sonL,sonR);
        lPointers.push_back(parent);
    }
}

//print coded map <char, vector<bool> > table
void printMap(map<char, vector<bool> > table){
    int y = 0;
    //    show elements of "table" map
    map<char, vector<bool> > ::iterator z;
    for(z = table.begin(); z != table.end(); ++z){
        cout <<y++ <<" " << z->first << " : ";
        vector<bool> tmp = z->second;
        for(int i = 0; i < tmp.size(); i++){
            cout << tmp[i];
        }
        cout << endl;
    }
}

//create vector<bool> where we save our coded message readed from file
vector<bool>* createEncodedRepresentationOfFile(char* fName){
    vector<bool> *codedMessage = new vector<bool>();
    char d; //to read one character
    ifstream str(fName, ios::binary);
    while (str.get(d)) {
        vector<bool> tmp = table[d];
        for(int i = 0; i < tmp.size(); i++){
            codedMessage->push_back(tmp[i]);
        }
    }
    str.close();
    //find size of codedMessage vector
    int sizeOfCodedMessage = codedMessage->size();
    //    cout << "Size of vector code: " << sizeOfCodedMessage <<endl;
    //adding to end of vector "0" till codeMessage%8 = 0
    if(sizeOfCodedMessage%8 != 0){
        while((codedMessage->size())%8 !=0){
            codedMessage->push_back(0);
        }
    }
    //    cout << "Size of vector code after adding '0': " << codedMessage->size() << endl;
    return codedMessage;
}

/**
* write in file our coded map - "table" and coded file, in char representation
* using one char to add the size of "table" (map)
* next i add coded symbol (1)
* add symbols length in char(2)
* the third adding vector<bool> code of symbol in integer representation
* using for this 4 bytes.
* and do this sycle "table.size()".
* after all i put the coded message char by char
*/
void writeCodedFile(char* fCode, vector<bool> *codedMessage, int sizeOfCodedMessage){
    char sizeOfTableMap = table.size();
    ofstream fout("ofstreamcode.txt", ios::binary);
    char buf = 0;
    fout.put(sizeOfTableMap); // write in file size of table map<char, vector<bool>>
    //writing in file char and his code
    map<char, vector<bool> > ::iterator q;
    for(q = table.begin(); q != table.end(); ++q){
        //1 byte writing char from map
        char c = q->first;
        fout.put(c);
        vector<bool> tmp = q->second;
        //2 byte write size of tmp vector
        fout.put((char)tmp.size());
        //3 - 4 bytes write code of our char in int form
        vector<bool>::iterator p;
        int vecbool = 0;
        for(p = tmp.begin(); p != tmp.end(); p++){
            vecbool = (vecbool << 1) | *p;
        }
        fout.write((char*)& vecbool, sizeof(vecbool));
    }

    //writing length of coded message, use 4 byte
    fout.write ((char *)&sizeOfCodedMessage, sizeof(sizeOfCodedMessage));

    //writing in file coded message
    int count = 0; buf = 0;
    for(int i = 0; i < codedMessage->size(); i++){
        buf = buf | (codedMessage->at(i)) <<(7 - count);
        count++;
        if(count == 8){
            count = 0;
            fout << buf;
            buf = 0;
        }
    }
    fout.close(); // Close file
}

//decode our coded file
void decryptTheEncryptedFile(char* fCode, char* fDecoded){
    ifstream s(fCode, ios::binary);
       ofstream dec(fDecoded, ios::binary);
       char tabsize;
       s.get(tabsize);
       map<vector<bool>, char> tab;
       for(int i = 0; i < tabsize; i++){
           char valuue;
           s.get(valuue);
           char len;
           s.get(len);
           int num = 0;
           s.read((char*)& num, sizeof(int));
           vector<bool> keyCode;
           num = num << (sizeof(num) * 8 - len);
           for(char u = 0; u < len; u++){
               keyCode.push_back(num < 0);
               num = num << 1;
           }
           tab[keyCode] = valuue;
       }
       int smessage = 0;
       s.read((char*)& smessage, sizeof(smessage));
       vector<bool> cCodeMessage; //all text in one vector
       int counter = 0;
       int couForByte = 0;
       while(!s.eof()){
           char ch = 0;
           s.get(ch);
           while(couForByte != 8){
               cCodeMessage.push_back(ch < 0);
               ch = ch << 1;
               couForByte++;
           }
           couForByte = 0;
           counter = counter + 8;
       }
       vector<bool> ress;
       for(int i = 0; i<(cCodeMessage.size()-(cCodeMessage.size()- smessage)); i++){
           ress.push_back(cCodeMessage[i]);
           if(tab[ress]){
               dec << tab[ress];
               ress.clear();
           }
       }
       cout << "File decoded!!!" << endl;
       s.close();
       dec.close();
}

int main()
{

    //create collection - map from file
    map<char, int> mapChar = makeMapOfFile(FNAME);

    //make list of pointers to Node from mapChar
    list<Node*> lPointers = createListOfKeyValuePair(mapChar);

    //create binary tree of Huffman and make table of code and symbols map<char, vector<bool>>
    createBinaryHuffmanTree(lPointers);
    Node *root = lPointers.front();
    createTableOfEncodedCharacters(root);
    //    print(root,0);

    //create vector<bool> where we save our coded message readed from file
    vector<bool> *codedMessage = createEncodedRepresentationOfFile(FNAME);

    //write in file our coded map - "table" and coded file, in char representation
    writeCodedFile(CODED_FILE, codedMessage, codedMessage->size());

    //decode our coded file
    decryptTheEncryptedFile(CODED_FILE, FDECODED);

    return 0;
}
