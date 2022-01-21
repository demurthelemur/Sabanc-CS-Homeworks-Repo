#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//Struct for storing the informatiın about the current line
struct Word{
    string word;
    int x;
    int y;
    string direction;
    string clockDir;
};


void openFile(ifstream & file);
void rowColumnReturn(int & row, int & column, string firstLine);
void createMatrix(vector<vector<string> > & matrix, int row, int column);
void printMatrix(vector<vector<string> > matrix, int row, int column);
Word createStruct(string line);
bool numberOfInputs(string demoString);
bool orientationCheck(string str);
bool directionCheck(string str);
void setCurrent(int & current);



int main(){
    //create a new ifstream object
    ifstream file;
    
    //function call to open file and getting the first line
    openFile(file);
    string firstLine;
    getline(file, firstLine);
    
    //get the row and column data for the matrix
    int row, column;
    rowColumnReturn(row, column, firstLine);
    
    //check if the row and column data are valid, exit if not
    if(row < 0 || column < 0){
        cout << "Invalid number for row and/or column! " << endl;
        return 0;
    }
    
    //Create the matrix with the given data
    vector<vector<string> > matrix(row, vector<string>(column));
    createMatrix(matrix, row, column);
    int i = 0;
    
    //Reading the file line by line
    while(!file.eof()){
        //get the current line
        string currentLine;
        getline(file, currentLine);
        
        //create a struct with necessay inputs
        struct Word newWord = createStruct(currentLine);
        if(newWord.word == "__SKIPLINE"){
            cout << "Starting point cannot be negative" << endl;
            continue;
        }
        
        //debug Couts
#ifdef __DEBUG
        cout << "Line number: " << i << endl;
        cout << "Word: " << newWord.word << " X: " << newWord.x << " Y: " << newWord.y << " Direction: " << newWord.direction << " Orientation: " << newWord.clockDir << endl;
        cout << "*********************" << endl;
#endif
        //Input numbers check
        if(numberOfInputs(currentLine)){
            cout << "Right length for the input" << endl;
        } else{
            cout << "Failed the input check!" << endl;
            i++;
            cout << "*********************" << endl;
            continue;
        }
        
        //Checking for the starting location being in range
        if(!(newWord.x < row) || !(newWord.y < column)){
            cout << "Starting value is out of range! Range: " << newWord.x << ", " << newWord.y << endl;
            continue;
        }
        
        //Checks if the direction given is correct
        if(!directionCheck(newWord.direction)){
               cout << "Invalid input for direction! Direction: " << newWord.direction << endl;
               continue;
           }
        
        //Checks if the orientation given is correct
        if(!orientationCheck(newWord.clockDir)){
            cout << "Invalid input for orientation! Orientation: " << endl;
            continue;
        }
        //PLACEMENT
        //Check if the first letter for the word is empty
        if(matrix[newWord.x][newWord.y] != "-"){
            //this if statement checks if the starting location for the word is equals "-". if not gives an error and skips to the next word
            cout << "\"" << newWord.word << "\"" << " could not be put into the matrix with given starting string point: "
            << newWord.x << "," << newWord.y << " direction: " << newWord.direction << " orientation: " << newWord.clockDir << endl;
            printMatrix(matrix, row, column);
            continue;
        }
        //put the first letter in the starting position;
        matrix[newWord.x][newWord.y] = newWord.word[0];
        cout << newWord.word << "was put into the matrix with the given starting point " << newWord.x << ", " << newWord.y << " cirection: " << newWord.direction << " orientation: " << newWord.clockDir << endl;
        
        //define how clockwise and counter-clockwise movement will work
        string directionCW [4] = {"u", "r", "d", "l"};
        string directionCCW [4] = {"u", "l", "d", "r"};
        
        //change the direction data to char for use in case-switch
        char direction = newWord.direction[0];
        int x = newWord.x;
        int y = newWord.y;
        int index = 1;
        size_t length = newWord.word.length() - 1;
        int current;
        //switch case to decide on the startign direction of the word
        switch (direction) {
            case 'r':
                
                //adding one to the y value if the we can to get to the next space after placing the first letter of the word
                if(y != column || matrix[x][y] == "-"){
                    y++;
                }
                //choosing if clockwise or counter-clockwise
                if(newWord.clockDir == "CW"){
                    //Choosing current as one to select r from the cw array
                    current = 1;
                    while(index <= length){
                        //if the current direction is right
                        if(directionCW[current] == "r"){
                            if(y != column || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value
                                matrix[x][y] = newWord.word[index];
                                //increase index and y value
                                index++;
                                y++;
                            }
                            //if the y value cannot go further right then go to the next direction according to the cw array
                            if(y == column || matrix[x][y] != "-"){
                                setCurrent(current);
                                y--;
                            }
                            //if the current direction is down
                        } else if(directionCW[current] == "d"){
                            //check if the right value is available, if available change the direction to right
                            if(matrix[x][y+1] == "-"){
                                current = 1;
                            }
                            else if(x != row-1 || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value after increasing the x
                                x++;
                                matrix[x][y] = newWord.word[index];
                                index++;
                            }
                            //if the x value cannot go further down then go the next direction according to the cw array
                            else if(x == row || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                            //if the current direction is left
                        } else if(directionCW[current] == "l"){
                            //check if the right value is available, if available change the direction to right
                            if(matrix[x][y+1] == "-"){
                                current = 1;
                            }
                            else if(y != 0 || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value after decreasing the x
                                y--;
                                matrix[x][y] = newWord.word[index];
                                index++;
                            }
                            //if the y value cannot go further left change the direction according to the cw array
                            else if(y == 0 || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                            //check if the current direction is up
                        } else if(directionCW[current] == "u"){
                            //check if the right value is available, if available change the direction to right
                            if(matrix[x][y + 1] == "-"){
                                current = 1;
                                continue;
                            }
                            //put a char into the matrix in the corresponding x and y value after decreasing the x
                            else if(x != 0 || matrix[x][y] == "-"){
                                x--;
                                matrix[x][y] = newWord.word[index];
                                index++;
                            //if the x value cannot go further down change the direction according to the cw array
                            } else if(x == 0 || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                        }
                    }
                } else if(newWord.clockDir == "CCW"){
                    current = 3;
                    while(index <= length){
                        //if the current direction is right
                        if(directionCCW[current] == "r"){
                            if(y != column || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value
                                matrix[x][y] = newWord.word[index];
                                //increase index and y value
                                index++;
                                y++;
                            }
                            //if the y value cannot go further right then go to the next direction according to the cw array
                            if(y == column || matrix[x][y+1] != "-"){
                                setCurrent(current);
                                y--;
                            }
                            //if the current direction is down
                        } else if(directionCCW[current] == "d"){
                            //check if the right value is available, if available change the direction to right
                            if(matrix[x][y+1] == "-"){
                                current = 3;
                            }
                            else if(x != row-1 || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value after increasing the x
                                x++;
                                matrix[x][y] = newWord.word[index];
                                index++;
                            }
                            //if the x value cannot go further down then go the next direction according to the cw array
                            else if(x == row || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                            //if the current direction is left
                        } else if(directionCCW[current] == "l"){
                            //check if the right value is available, if available change the direction to right
                            if(matrix[x][y+1] == "-"){
                                current = 3;
                            }
                            else if(y != 0 || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value after decreasing the x
                                y--;
                                matrix[x][y] = newWord.word[index];
                                index++;
                            }
                            //if the y value cannot go further left change the direction according to the cw array
                            else if(y == 0 || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                            //check if the current direction is up
                        } else if(directionCCW[current] == "u"){
                            //check if the right value is available, if available change the direction to right
                            if(matrix[x][y + 1] == "-"){
                                current = 3;
                                continue;
                            }
                            //put a char into the matrix in the corresponding x and y value after decreasing the x
                            else if(x != 0 || matrix[x][y] == "-"){
                                x--;
                                matrix[x][y] = newWord.word[index];
                                index++;
                            //if the x value cannot go further down change the direction according to the ccw array
                            } else if(x == 0 || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                        }
                    }
                }
                break;
            case 'd':
                //choosing if clockwise or counter-clockwise
                if(newWord.clockDir == "CW"){
                    //Choosing current as one to select d from the cw array
                    current = 2;
                    while(index <= length){
                        //if the current direction is right
                        if(directionCW[current] == "r"){
                            //check if the down value is available, if available change the direction to down
                            if(matrix[x+1][y] == "-"){
                                current = 2;
                            }
                            else if(y != column || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value
                                y++;
                                matrix[x][y] = newWord.word[index];
                                //increase index and y value
                                index++;
                                
                            }
                            //if the y value cannot go further right then go to the next direction according to the cw array
                            if(y == column || matrix[x][y] != "-"){
                                setCurrent(current);
                                y--;
                            }
                            //if the current direction is down
                        } else if(directionCW[current] == "d"){
                            if(x != row-1 || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value after increasing the x
                                x++;
                                matrix[x][y] = newWord.word[index];
                                index++;
                                
                            }
                            //if the x value cannot go further down then go the next direction according to the cw array
                            else if(x == row || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                            //if the current direction is left
                        } else if(directionCW[current] == "l"){
                            //check if the down value is available, if available change the direction to down
                            if(matrix[x + 1][y] == "-"){
                                current = 2;
                            }
                            else if(y != 0 || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value after decreasing the x
                                y--;
                                matrix[x][y] = newWord.word[index];
                                index++;
                            }
                            //if the y value cannot go further left change the direction according to the cw array
                            else if(y == 0 || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                            //check if the current direction is up
                        } else if(directionCW[current] == "u"){
                            //check if the right value is available, if available change the direction to down
                            if(matrix[x + 1][y] == "-"){
                                current = 2;
                                continue;
                            }
                            //put a char into the matrix in the corresponding x and y value after decreasing the x
                            else if(x != 0 || matrix[x][y] == "-"){
                                x--;
                                matrix[x][y] = newWord.word[index];
                                index++;
                            //if the x value cannot go further up change the direction according to the cw array
                            } else if(x == 0 || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                        }
                    }
                } else if(newWord.clockDir == "CCW"){
                    current = 2;
                    while(index <= length){
                        //if the current direction is right
                        if(directionCCW[current] == "r"){
                            //check if the down value is available, if available change the direction to down
                            if(matrix[x+1][y] == "-"){
                                current = 2;
                            }
                            if(y != column || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value
                                y++;
                                matrix[x][y] = newWord.word[index];
                                //increase index and y value
                                index++;
                                
                            }
                            //if the y value cannot go further right then go to the next direction according to the cw array
                            if(y == column || matrix[x][y] != "-"){
                                setCurrent(current);
                                y--;
                            }
                            //if the current direction is down
                        } else if(directionCCW[current] == "d"){
                            if(x != row-1 || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value after increasing the x
                                x++;
                                matrix[x][y] = newWord.word[index];
                                index++;
                            }
                            //if the x value cannot go further down then go the next direction according to the cw array
                            else if(x == row || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                            //if the current direction is left
                        } else if(directionCCW[current] == "l"){
                            //check if the down value is available, if available change the direction to down
                            if(matrix[x+1][y] == "-"){
                                current = 2;
                            }
                            else if(y != 0 || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value after decreasing the x
                                y--;
                                matrix[x][y] = newWord.word[index];
                                index++;
                            }
                            //if the y value cannot go further left change the direction according to the cw array
                            else if(y == 0 || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                            //check if the current direction is up
                        } else if(directionCCW[current] == "u"){
                            //check if the down value is available, if available change the direction to down
                            if(matrix[x+1][y] == "-"){
                                current = 2;
                                continue;
                            }
                            //put a char into the matrix in the corresponding x and y value after decreasing the x
                            else if(x != 0 || matrix[x][y] == "-"){
                                x--;
                                matrix[x][y] = newWord.word[index];
                                index++;
                            //if the x value cannot go further up change the direction according to the ccw array
                            } else if(x == 0 || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                        }
                    }
                }
                
                break;
            case 'l':
                    //choosing if clockwise or counter-clockwise
                    if(newWord.clockDir == "CW"){
                        //Choosing current as one to select l from the cw array
                        current = 3;
                        while(index <= length){
                            //if the current direction is right
                            if(directionCW[current] == "r"){
                                //check if the left value is available, if available change the direction to left
                                if(matrix[x][y-1] == "-"){
                                    current = 3;
                                }
                                else if(y != column || matrix[x][y] == "-"){
                                    //put a char into the matrix in the corresponding x and y value
                                    y++;
                                    matrix[x][y] = newWord.word[index];
                                    //increase index and y value
                                    index++;
                                }
                                //if the y value cannot go further right then go to the next direction according to the cw array
                                if(y == column || matrix[x][y] != "-"){
                                    setCurrent(current);
                                    y--;
                                }
                                //if the current direction is down
                            } else if(directionCW[current] == "d"){
                                //check if the left value is available, if available change the direction to left
                                if(matrix[x][y-1] == "-"){
                                    current = 3;
                                }
                                else if(x != row-1 || matrix[x][y] == "-"){
                                    //put a char into the matrix in the corresponding x and y value after increasing the x
                                    x++;
                                    matrix[x][y] = newWord.word[index];
                                    index++;
                                }
                                //if the x value cannot go further down then go the next direction according to the cw array
                                else if(x == row || matrix[x][y] != "-"){
                                    setCurrent(current);
                                }
                                //if the current direction is left
                            } else if(directionCW[current] == "l"){
                                if(y != 0 || matrix[x][y] == "-"){
                                    //put a char into the matrix in the corresponding x and y value after decreasing the x
                                    y--;
                                    matrix[x][y] = newWord.word[index];
                                    index++;
                                }
                                //if the y value cannot go further left change the direction according to the cw array
                                else if(y == 0 || matrix[x][y] != "-"){
                                    setCurrent(current);
                                }
                                //check if the current direction is up
                            } else if(directionCW[current] == "u"){
                                //check if the left value is available, if available change the direction to left
                                if(matrix[x][y-1] == "-"){
                                    current = 3;
                                }
                                //put a char into the matrix in the corresponding x and y value after decreasing the x
                                else if(x != 0 && matrix[x][y] == "-"){
                                    x--;
                                    matrix[x][y] = newWord.word[index];
                                    index++;
                                //if the x value cannot go further up change the direction according to the cw array
                                } else if(x == 0 || matrix[x][y] != "-"){
                                    setCurrent(current);
                                }
                            }
                        }
                    } else if(newWord.clockDir == "CCW"){
                        current = 1;
                        while(index <= length){
                            //if the current direction is right
                            if(directionCCW[current] == "r"){
                                //check if the left value is available, if available change the direction to left
                                if(matrix[x][y-1] == "-"){
                                    current = 1;
                                }
                                if(y != column || matrix[x][y] == "-"){
                                    //put a char into the matrix in the corresponding x and y value
                                    y++;
                                    matrix[x][y] = newWord.word[index];
                                    //increase index and y value
                                    index++;
                                    
                                }
                                //if the y value cannot go further right then go to the next direction according to the cw array
                                if(y == column || matrix[x][y] != "-"){
                                    setCurrent(current);
                                    y--;
                                }
                                //if the current direction is down
                            } else if(directionCCW[current] == "d"){
                                //check if the left value is available, if available change the direction to left
                                if(matrix[x][y-1] == "-"){
                                    current = 1;
                                }
                                else if(x != row-1 || matrix[x][y] == "-"){
                                    //put a char into the matrix in the corresponding x and y value after increasing the x
                                    x++;
                                    matrix[x][y] = newWord.word[index];
                                    index++;
                                }
                                //if the x value cannot go further down then go the next direction according to the cw array
                                else if(x == row || matrix[x][y] != "-"){
                                    setCurrent(current);
                                }
                                //if the current direction is left
                            } else if(directionCCW[current] == "l"){
                                if(y != 0 || matrix[x][y] == "-"){
                                    //put a char into the matrix in the corresponding x and y value after decreasing the x
                                    y--;
                                    matrix[x][y] = newWord.word[index];
                                    index++;
                                }
                                //if the y value cannot go further left change the direction according to the cw array
                                else if(y == 0 || matrix[x][y] != "-"){
                                    setCurrent(current);
                                }
                                //check if the current direction is up
                            } else if(directionCCW[current] == "u"){
                                //check if the left value is available, if available change the direction to left
                                if(matrix[x][y-1] == "-"){
                                    current = 1;
                                }
                                //put a char into the matrix in the corresponding x and y value after decreasing the x
                                else if(x != 0 || matrix[x][y] == "-"){
                                    x--;
                                    matrix[x][y] = newWord.word[index];
                                    index++;
                                //if the x value cannot go further up change the direction according to the ccw array
                                } else if(x == 0 || matrix[x][y] != "-"){
                                    setCurrent(current);
                                }
                            }
                        }
                    }
                break;
            case 'u':
                //choosing if clockwise or counter-clockwise
                if(newWord.clockDir == "CW"){
                    //Choosing current as one to select u from the cw array
                    current = 0;
                    while(index <= length){
                        //if the current direction is right
                        if(directionCW[current] == "r"){
                            //check if the up value is available, if available change the direction to up
                            if(matrix[x-1][y] == "-"){
                                current = 0;
                            }
                            else if(y != column || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value
                                y++;
                                matrix[x][y] = newWord.word[index];
                                //increase index and y value
                                index++;
                                
                            }
                            //if the y value cannot go further right then go to the next direction according to the cw array
                            if(y == column || matrix[x][y] != "-"){
                                setCurrent(current);
                                y--;
                            }
                            //if the current direction is down
                        } else if(directionCW[current] == "d"){
                            //check if the up value is available, if available change the direction to up
                            if(matrix[x-1][y] == "-"){
                                current = 0;
                            }
                            else if(x != row-1 || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value after increasing the x
                                x++;
                                matrix[x][y] = newWord.word[index];
                                index++;
                                                            }
                            //if the x value cannot go further down then go the next direction according to the cw array
                            else if(x == row || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                            //if the current direction is left
                        } else if(directionCW[current] == "l"){
                            //check if the up value is available, if available change the direction to up
                            if(matrix[x-1][y] == "-"){
                                current = 0;
                            }
                            else if(y != 0 || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value after decreasing the x
                                y--;
                                matrix[x][y] = newWord.word[index];
                                index++;
                            }
                            //if the y value cannot go further left change the direction according to the cw array
                            else if(y == 0 || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                            //check if the current direction is up
                        } else if(directionCW[current] == "u"){
                            //put a char into the matrix in the corresponding x and y value after decreasing the x
                            if(x != 0 || matrix[x][y] == "-"){
                                x--;
                                matrix[x][y] = newWord.word[index];
                                index++;
                            //if the x value cannot go further up change the direction according to the cw array
                            } else if(x == 0 || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                        }
                    }
                } else if(newWord.clockDir == "CCW"){
                    current = 0;
                    while(index <= length){
                        //if the current direction is right
                        if(directionCCW[current] == "r"){
                            //check if the up value is available, if available change the direction to up
                            if(matrix[x-1][y] == "-"){
                                current = 0;
                            }
                            if(y != column || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value
                                y++;
                                matrix[x][y] = newWord.word[index];
                                //increase index and y value
                                index++;
                                
                            }
                            //if the y value cannot go further right then go to the next direction according to the cw array
                            if(y == column || matrix[x][y] != "-"){
                                setCurrent(current);
                                y--;
                            }
                            //if the current direction is down
                        } else if(directionCCW[current] == "d"){
                            //check if the up value is available, if available change the direction to up
                            if(matrix[x-1][y] == "-"){
                                current = 0;
                            }
                            else if(x != row-1 || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value after increasing the x
                                x++;
                                matrix[x][y] = newWord.word[index];
                                index++;
                            }
                            //if the x value cannot go further down then go the next direction according to the cw array
                            else if(x == row || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                            //if the current direction is left
                        } else if(directionCCW[current] == "l"){
                            //check if the up value is available, if available change the direction to up
                            if(matrix[x-1][y] == "-"){
                                current = 0;
                            }
                            else if(y != 0 || matrix[x][y] == "-"){
                                //put a char into the matrix in the corresponding x and y value after decreasing the x
                                y--;
                                matrix[x][y] = newWord.word[index];
                                index++;
                            }
                            //if the y value cannot go further left change the direction according to the cw array
                            else if(y == 0 || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                            //check if the current direction is up
                        } else if(directionCCW[current] == "u"){
                            //put a char into the matrix in the corresponding x and y value after decreasing the x
                            if(x != 0 || matrix[x][y] == "-"){
                                x--;
                                matrix[x][y] = newWord.word[index];
                                index++;
                            //if the x value cannot go further up change the direction according to the ccw array
                            } else if(x == 0 || matrix[x][y] != "-"){
                                setCurrent(current);
                            }
                        }
                    }
                }
                break;
        }
        printMatrix(matrix, row, column);
        
        
        
        
#ifdef __DEBUG
        printMatrix(matrix, row, column);
        i++;
        cout << "*********************" << endl;
#endif
    }
    
    
    
    
    return 0;
}

void openFile(ifstream & file){
    //gets the filename from the user and tests it
    string fileName;
    cout << "Please enter the file name: " << endl;
    cin >> fileName;
    file.open(fileName.c_str());
    //if the file cannot be oppened it prompts the user until correct filename is given
    while(file.fail()){
        cout << "File Name is incorrect, please enter again: " << endl;
        cin >> fileName;
        file.open(fileName.c_str());
    }
}
    
void rowColumnReturn(int & row, int & column, string line){
    //finds the row and column data from the first string
    int firstDigit = 0;
    while(line[firstDigit] != ' '){
        firstDigit++;
    }
    //creates substrings for the data
    string x = line.substr(0, firstDigit+1);
    string y = line.substr(firstDigit+1, 2);
    //transfers the data to int
    row = stoi(x);
    column = stoi(y);
}

void createMatrix(vector<vector<string> > & matrix, int row, int column){
    //creates a matrix using two for loops
    for(int i = 0; i < row; i++){
        for(int k = 0; k < row; k++){
            matrix[i][k] = "-";
        }
    }
}

void printMatrix(vector<vector<string> > matrix, int row, int column){
    //prints the matrix using two for loops
    for(int i = 0; i < row; i++){
        for(int k = 0; k < row; k++){
            cout << " " << matrix[i][k] << " ";
        }
        cout << endl;
    }
}

Word createStruct(string line){
    Word newWord;

    //Finding the word
    int x = 0;
    while(line[x] != ' '){
        x++;
    }
    if(x > 20){
        return newWord;
    }
    // add the string to the struct
    newWord.word = line.substr(0, x);
    //find the x value
    int y = x+1;
    while(line[y] == ' '){
        y++;
    }
    string xValue = line.substr(x+1, y-x+1);
    //if the x value is negative give an error
    if(xValue[0] == '-'){
        newWord.word = "__SKIPLINE";
        return newWord;
    }
    //convert the x value to a string and add it to the struct
    newWord.x = stoi(xValue);
    int z = y+1;
    while(line[z] == ' '){
        z++;
    }
    //if the y value is negative give an error
    string yValue = line.substr(z, 2);
    if(yValue[0] == '-'){
        newWord.word = "__SKIPLINE";
        return newWord;
    }
    //convert the y value to an int and add it to the struct;
    newWord.y = stoi(yValue);
    //finds the direction value
    int a = z+1;
    while(line[a] == ' '){
        a++;
    }
    int b = a;
    while(isalpha(line[b])){
        b++;
    }
    //adds the direction value to the struct
    string dirValue = line.substr(a, b-a);
    newWord.direction = dirValue;
    //finds the orientation
    int c = b + 1;
    while(line[c] == ' '){
        c++;
    }
    int d = c;
    while(isalpha(line[d])){
        d++;
    }
    //adds the orientation value to the struct
    string clockWise = line.substr(c, c-d);
    newWord.clockDir = clockWise;
    
    return newWord;
}

bool numberOfInputs(string demoString){
    //first find where the string ends and go to the next element;
    int firstSpace = 0;
    while(demoString[firstSpace] != ' '){
        firstSpace++;
    }
    int firstInput = firstSpace + 1;
    while(demoString[firstInput] == ' '){
        firstInput++;
    }
    //count the number of elements
    int numberOfInput = 1;
    int secondSpace = firstInput + 1;
    while(secondSpace < demoString.length()){
        if(demoString[secondSpace] != ' '){
            numberOfInput++;
        }
        secondSpace++;
    }

    if(numberOfInput == 5){
        return true;
    } else if(numberOfInput == 6){
        return true;
    } else{
        return false;
    }

}

bool orientationCheck(string str){
    //check if the orientation is correct by checking if it is in the array
    string acceptableDirections[2] = {"CW", "CCW"};
    bool found = false;
    for(int i = 0; i < 2; i++){
        if(str == acceptableDirections[i]){
            found = true;
        }
    }
    return found;
}
bool directionCheck(string str){
    string acceptableDirections[4] = {"r", "l", "u", "d"};
    bool found = false;
    for(int i = 0; i < 4; i++){
        if(str == acceptableDirections[i]){
            found = true;
        }
    }
    return found;
}

void setCurrent(int & current){
    if(current == 3){
        current = 0;
    } else{
        current++;
    }
}

