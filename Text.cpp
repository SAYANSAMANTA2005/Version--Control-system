#include<iostream>
#include<string>
#include<vector>
using namespace std;
/*
enabled Storing of Text in History and Undo Functionality

User Writes Text in CLI / terminal & programme stores the text in History 
and user can undo the text that is written in the history
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
     cout<<history[i].id<<" "<<history[i].text<<endl;
   }
}
int main(){
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
        else break;
    }
}