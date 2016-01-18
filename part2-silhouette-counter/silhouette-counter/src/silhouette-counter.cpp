#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "strlib.h"
#include "gbufferedimage.h"
#include "set.h"
#include "vector.h"
#include <fstream>
#include <sstream>
using namespace std;

/**
 * The Coordinate structure. Save position of pixel
 */
struct Coordinate {
    int y;
    int x;
};

/**
 * Class that stores vector of coordinates of one black object
 */
class BlackObject {
private:
    Vector<Coordinate> object;
public:
    BlackObject(){};
    BlackObject(Vector<Coordinate> silhouette) {
        object = silhouette;
    };

    /**
     * Give access to vector "object"
     * @return - Vector<Coordinate>
     */
    Vector<Coordinate> getVec() {
        return object;
    }
};



/**
 * Load image.
 * Creating binary representation of image.
 * @param filename - Name of loaded image
 * @return - Vector two dimensional comprising of 0 and 1
 */
Vector<Vector<bool> > createBinaryRepresenationOfFile(string filename) {
    GBufferedImage* img = new GBufferedImage(0, 0, 900, 900);
    img->load(filename);
    int imgWidth = img->getWidth();
    int imgHeight = img->getHeight();
    Vector<Vector<bool> > res(imgHeight, Vector<bool>(imgWidth, 0));
    for(int i = 0; i < imgHeight; i++){
        for(int j = 0; j < imgWidth; j++){
            int pixColor = img->getRGB(j, i);
            if(img->getBlue(pixColor) < 128 && img->getGreen(pixColor) < 128 && img->getRed(pixColor) < 128){
                res[i][j] = 1;
            }
        }
    }
    delete img;
    return res;
}


/**
 * Fill in the vector coordinates of the object
 * @param img - The binarized user's image.
 * @param x - x coordinate.
 * @param y - y coordinate.
 * @param silho - The vector of the silhouette Coordinates.
 */
void getSingleSilhouette(Vector<Vector<bool> > &img, int x, int y, Vector<Coordinate> &silho) {
    if((x <= img[0].size()) && (y <= img.size())){
        if(!(img[y][x])){
            return;
        }
    }
    Coordinate coord;
    coord.x = x;
    coord.y = y;
    silho.add(coord);
    if((x <= img[0].size()) && (y <= img.size())){
        img[y][x] = 0;
    }
    getSingleSilhouette(img, x - 1, y, silho);
    getSingleSilhouette(img, x + 1, y, silho);
    getSingleSilhouette(img, x, y - 1, silho);
    getSingleSilhouette(img, x, y + 1, silho);
}

/**
 * Create Vector of coordinates of one silhouette
 * @param image - Binarized user's image
 * @return - vector<Coordinate> one silhouette
 */
BlackObject getSingleBlackObject(Vector<Vector<bool> > &img, int x, int y) {
    Vector<Coordinate> silho;
    getSingleSilhouette(img, x, y, silho);
    BlackObject res(silho);
    return res;
}

/**
 * Collect all the objects in the image into a vector of BlackObject
 * @param img - The binarized image.
 * @return - The vector of BlackObjects.
 */
Vector<BlackObject> getCollectionOfBlackObjects(Vector<Vector<bool> > &img) {
    int imgWidth = img[0].size();
    int imgHeight = img.size();
    Vector<BlackObject> result;
    for(int y = 0; y < imgHeight; y++){
        for(int x = 0; x < imgWidth; x++){
            if((img[y][x])){
                BlackObject object = getSingleBlackObject(img, x, y);
                result.add(object);
            }
        }
    }
    return result;
}

/**
 * Attempt to determine whether a person is.
 * @param filename - User's image filename.
 * @return - true or false if we define or not define human
 */
bool isSilhouette(BlackObject c) {
    int topY = 2000;
    int botY = 0;
    int leftX = 2000;
    int rightX = 0;
    Vector<Coordinate> vec = c.getVec();
    for(Coordinate currentCoord : vec){
        if(currentCoord.x > rightX){
            rightX = currentCoord.x;
        }
        if(currentCoord.x < leftX){
            leftX = currentCoord.x;
        }
        if(currentCoord.y > botY){
            botY = currentCoord.y;
        }
        if(currentCoord.y < topY){
            topY = currentCoord.y;
        }
    }
    double widthOfObj = rightX - leftX;
    double heightOfMan = botY - topY;
    double uniqueMeasurer = heightOfMan / 8;
    return ((widthOfObj / uniqueMeasurer) < (5.5) && (widthOfObj / uniqueMeasurer) > (1.5));
}


/**
 * Show to user, result of search
 * @param filename - User's image, filename.
 */
void countSilhouettes(string filename) {
    int approxSilho = 0;
    Vector<Vector<bool> > img = createBinaryRepresenationOfFile(filename);
    Vector<BlackObject> objects = getCollectionOfBlackObjects(img);
    int validObj = objects.size();
    int imgWidth = img[0].size();
    int imgHeight = img.size();
    int imgSize = imgWidth * imgHeight;
    for(BlackObject c : objects){
        if(isSilhouette(c)){
            approxSilho++;
        }
        if((c.getVec().size()) < (imgSize / 1000)){
            validObj--;
        }
    }
    cout << "In file " << filename << " was found BlackObject " << validObj << " objects. And approximately ";
    cout << approxSilho << " people." <<  endl;
}

/**
 * Calculate quantity of black objects, on white background.
 */
int main() {
    while(true){
        string choice;
        cout << "Input 1 to enter your filename and 2 for standard test collection." << endl;
        getline(cin, choice);
        if(choice == "exit"){
            break;
        }
        if(choice == "1"){
            string fName;
            cout << "Input filename:";
            getline(cin, fName);
            countSilhouettes(fName);
        }
        if(choice == "2"){
            countSilhouettes("action.jpg");
            countSilhouettes("f.jpg");
            countSilhouettes("a.png");
            countSilhouettes("4in1.jpg");
        }else{
            cout << "Input is wrong! Try again!";
        }
    }
    return 0;
}
