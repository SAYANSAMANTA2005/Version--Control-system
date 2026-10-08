#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <filesystem>
using namespace std;
/*
enabled Storing of Text in History and Undo Functionality

User Writes Text in CLI / terminal & programme stores the text in History 
and user can undo the text that is written in the history
*/

/*
    CURRENT PROJECT BEHAVIOUR:

    This project is a basic text-based Version Control System that:

    1. Allows the user to enter text through the CLI.
    2. Stores each entered text as a State in an in-memory history.
    3. Assigns a unique ID to each State.
    4. Supports an Undo operation by moving one State backward
       and removing the latest State from the current history.
    5. Displays the currently active history.
    6. Saves the current text history to "history.txt" when the
       program exits.
    7. Saves the current history index to "CurrentIndex.txt".
    8. When the program starts again, it loads the previously saved
       history and restores the current index.
    
    CURRENT LIMITATIONS:

    - Undo permanently removes the State from the in-memory history.
    - Redo functionality is not implemented.
    - A State currently stores the complete text rather than a diff.
    - Only single-line text input is supported.
    - There is currently no branching or merging of versions.
    - Changes are saved only when the program exits.
    
    CURRENT STORAGE MODEL:

        User Input
             ↓
          State
             ↓
       vector<State>
             ↓
       history.txt
             +
       CurrentIndex.txt

    The next improvements can include:
        - Redo
        - Persistent individual versions
        - Diff-based storage
        - Commit system
        - Version branching
        - Checkout
        - Merge
*/
struct State{
 int id;
 string text;
};

vector<State>history;
int currIndex=0;

void displayHistory(){
    cout<<"Current History is: "<<endl;
   for(int i=0;i<currIndex;i++){
     cout<<"State :"<<i<<" Is "<<" "<<history[i].text<<endl;
   }
}

void SaveState(vector<State>&history){
     //currentIndex Reprents How many States are there in the Current History
  string filename="history.txt";

  ofstream file(filename);
  if(!file){
    cout<<"Failed to Create file"<<endl;
    return;
  }

  for(int i=0;i<currIndex;i++){
     file<<history[i].text<<endl;
  }

  file.close();
}

void SaveId(){
    //This Function saves the Current Index in the File
    ofstream file("CurrentIndex.txt");
    if(file){
        file<<currIndex;
        file.close();
    }
    else{
        cout<<"Failed to Save Current Index"<<endl;
    }
}
void LoadId(){
    //This Function sets The Current Index to the Last Saved Index in the File
    ifstream file("CurrentIndex.txt");
    if(file){
        file>>currIndex;
        file.close();
    }
    else{
        currIndex=0;
    }
}

void LoadingHistory(){
   history.resize(currIndex);
   ifstream file("history.txt");
   if(!file){
    cout<<"Failed to Load History"<<endl;
       return;
   }
   for(int i=0;i<currIndex;i++){
        history[i].id=i;
        getline(file,history[i].text);
   }
}
int main(){

    cout<<"Welcome to Version Control System"<<endl;
    cout<<"Please Wait untill Ur Last History is Loaded"<<endl;
    LoadId();
    LoadingHistory();
    cout<<"Ur Last State is: "<<endl;
    displayHistory();
    cout<<endl;

    while(true){
        cout<<"Enter 1 for Writing text , Else enter 2 for go Back in histry, Enter 3 to display current history"<<endl;
        int option;cin>>option;
        

        //cin >> option leaves the newline (\n) in the input buffer, which can cause issues for subsequent input operations. Using cin.ignore() clears the newline character from the input buffer, allowing getline() to work correctly for reading strings.
        cin.ignore(); // Ignore the newline character left in the buffer
        if(option==1){
        cout<<"Write What ever U want to Write on screen"<<endl;

        //This can take iput of String that is in One line only,
         //If u want to take input of multiple lines then use getline(cin,text)
         // instead of cin>>text
        string text;
        getline(cin,text);
        State s;
        s.id=currIndex;
        s.text=text;
        history.push_back(s);

        currIndex++;
        }
        else if(option==2){
            //currIndex --> represent the How many Staes R there in the Current History
            if(currIndex==0){
                cout<<"No more states to undo"<<endl;
            }
            else{
                //history.pop_back();
                currIndex--;
                cout<<"Undo Done "<<endl;
                history.pop_back();
            }

        }
        else if(option==3){
            displayHistory();
        }
        else{
            SaveState(history);
            SaveId();
            break;

        } 
    }
}