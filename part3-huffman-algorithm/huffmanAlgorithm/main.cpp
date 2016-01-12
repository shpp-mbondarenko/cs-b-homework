#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <fstream>


#define CODED_FILE "coded.txt"
#define DECODED_FILE "decoded.txt"

using namespace std;

class Node {
public:
    int quan;   //quantity appearing
    char c;     //our symbol char
    Node *left, *right;

    Node() {}

    Node(Node *L, Node *R) {
        left = L;
        right = R;
        c = NULL;
        quan = L->quan + R->quan;
    }
};



//sort list of node pointers
struct sortList {
    bool operator()(Node* l, Node* r) const
    {return l -> quan < r -> quan;}
};

//print tree
void print(Node *root, unsigned k = 0) {
    if(root != NULL){
        print(root -> left,k+3);
        for(unsigned i = 0; i < k; i++){
            cout << "   ";
        }
        if(root -> c != NULL){
            cout << root -> quan << " (" << root->c << ")" <<endl;
        }else{
            cout << root -> quan << endl;
        }
        print(root->right, k+3);
    }
}


//create a table of code for each character
void createTableOfEncodedCharacters(Node *root, map<char, vector<bool> > &table, vector<bool> &code) {
    if(root->left != NULL){
        code.push_back(0);
        createTableOfEncodedCharacters(root->left, table, code);
    }
    if(root->right != NULL){
        code.push_back(1);
        createTableOfEncodedCharacters(root->right, table, code);
    }
    if(root->c){
        table[root->c] = code;
    }
    code.pop_back(); //delete one symbol and come back to parent node and work further
}

//make list of pointers to Node from mapChar
list <Node*> createListOfNodesContainLettersAndFrequency(map<char, int> mapChar) {
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
map<char, int> createMapOfCharacterFrequencyOccurrence(string fName) {
    char n; //to read one character
    ifstream str(fName.c_str(), ios::binary);
    //create MAP for all symbols in our string and quantity of their appear
    map<char, int> mapChar;
    //go through string. Count elements(char)
    while(str.get(n)){
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
void createBinaryHuffmanTree(list <Node*> &ListOfPointersToNodes) {
    while(ListOfPointersToNodes.size() != 1){
        ListOfPointersToNodes.sort(sortList()); //sorting list

        //peek and pop smalest two elements in list
        Node *sonL = ListOfPointersToNodes.front();
        ListOfPointersToNodes.pop_front();
        Node *sonR = ListOfPointersToNodes.front();
        ListOfPointersToNodes.pop_front();

        Node *parent = new Node (sonL, sonR);
        ListOfPointersToNodes.push_back(parent);
    }
}

//print coded map <char, vector<bool> > table
void printMap(map<char, vector<bool> > table) {
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

/**
* Create vector<bool> where we save our coded message readed from file
* @param fName - file compress to
* @param table - collection, symbols and his code
*/
vector<bool>* createEncodedRepresentationOfFile(string fName, map<char, vector<bool> > &table) {
    vector<bool> *codedMessage = new vector<bool>();
    char d; //to read one character
    ifstream str(fName.c_str(), ios::binary);
    while(str.get(d)){
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
        while((codedMessage->size()) % 8 != 0){
            codedMessage->push_back(0);
        }
    }
    //    cout << "Size of vector code after adding '0': " << codedMessage->size() << endl;
    return codedMessage;
}

/**
* Write in file our coded map - "table" and coded file, in char representation
* using one char to add the size of "table" (map)
* next i add coded symbol (1)
* add symbols length in char(2)
* the third adding vector<bool> code of symbol in integer representation
* using for this 4 bytes.
* and do this cycle "table.size()".
* after all i put the coded message char by char
* @param codedFile - file, where we write compressed file
* @param fName - file compress to
* @param table - collection, symbols and his code
*/
void writeInDocumentCompressedFile(string codedFile, string fName, map<char, vector<bool> > table) {
    //create vector<bool> where we save our coded message readed from file
    vector<bool> *codedMessage = createEncodedRepresentationOfFile(fName, table);
    int sizeOfCodedMessage = codedMessage->size();
    char sizeOfTableMap = table.size();
    ofstream fout(codedFile.c_str(), ios::binary);
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
        buf = buf | (codedMessage->at(i)) << (7 - count);
        count++;
        if(count == 8){
            count = 0;
            fout << buf;
            buf = 0;
        }
    }
    fout.close(); // Close file
}

/**
* Decode our coded file
* @param fCoded - file, where we writed compressed file
* @param fDecoded - file, where we write decoded file
*/
void decryptCompressedFile(string fCoded, string fDecoded) {
    ifstream stream(fCoded.c_str(), ios::binary);
    ofstream dec(fDecoded.c_str(), ios::binary);
    char tabsize;
    stream.get(tabsize);
    map<vector<bool>, char> tab;
    for(int i = 0; i < tabsize; i++){
        char value;
        stream.get(value);
        char len;
        stream.get(len);
        int num = 0;
        stream.read((char*)& num, sizeof(int));
        vector<bool> keyCode;
        num = num << (sizeof(num) * 8 - len);
        for(char u = 0; u < len; u++){
            keyCode.push_back(num < 0);
            num = num << 1;
        }
        tab[keyCode] = value;
    }
    int sizeOfMessage = 0;
    stream.read((char*)& sizeOfMessage, sizeof(sizeOfMessage));
    vector<bool> codeMessage; //all text in one vector
    int counter = 0;
    int counterForByte = 0;
    while(!stream.eof()){
        char ch = 0;
        stream.get(ch);
        while(counterForByte != 8){
            codeMessage.push_back(ch < 0);
            ch = ch << 1;
            counterForByte++;
        }
        counterForByte = 0;
        counter = counter + 8;
    }
    vector<bool> res;
    for(int i = 0; i < (codeMessage.size() - (codeMessage.size() - sizeOfMessage)); i++){
        res.push_back(codeMessage[i]);
        if(tab[res]){
            dec << tab[res];
            res.clear();
        }
    }
    cout << "File decoded!" << endl;
    stream.close();
    dec.close();
}
/**
* Compressing file
* @param fName - file compress to
* @param codedFile - file, where we write compressed file
*/
void compressFile(string fName, string codedFile) {
    //create collection - map from file
    map<char, int> mapChar = createMapOfCharacterFrequencyOccurrence(fName);

    //make list of pointers to Node
    //in one Node we store symbol and his frequency
    list<Node*> listOfCharacterFrequencies = createListOfNodesContainLettersAndFrequency(mapChar);

    vector<bool> code; //binary code of symbol
    map<char, vector<bool> > table; //char and his binary code
    //create binary tree of Huffman and make table of code and symbols map<char, vector<bool>>
    createBinaryHuffmanTree(listOfCharacterFrequencies);
    Node *root = listOfCharacterFrequencies.front();
    createTableOfEncodedCharacters(root, table, code);
    //    print(root,0);

    //write in file our coded map - "table" and coded file, in char representation
    writeInDocumentCompressedFile(codedFile, fName, table);
    cout << "File compressed!" << endl;
}

int main() {
    while(true){
        cout << "What we shall do? Input 1 for compress file. Input 2 for decrypt file." << endl;
        string task;
        getline(cin, task);
        if(task == "exit"){
            break;
        }
        if(task == "1"){
            string fName;
            cout << "Enter filename:";
            getline(cin, fName);
            compressFile(fName, CODED_FILE);
        }else if(task == "2"){
            string fName;
            cout << "Enter filename to decode:";
            getline(cin, fName);
            //decode our coded file
            decryptCompressedFile(fName, DECODED_FILE);
        }else{
            cout << "Program, don't know what to do! Please try again!" << endl;
        }
    }
    return 0;
}
