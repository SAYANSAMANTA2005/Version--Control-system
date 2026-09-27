#include <vector>
#include <iostream>
using namespace std;

class VersionHistory {
private:
    vector<int> history;
    int cursor;
    int maxHistory;

public:

    VersionHistory(int maxHistory) {
        this->maxHistory = maxHistory;
        cursor = -1;
    }

    void pushState(int state) {
        // If we previously did undo(),
        // delete all states after current cursor.
        if (cursor < (int)history.size() - 1) {
            history.erase(history.begin() + cursor + 1, history.end());
        }

        // Add new state
        history.push_back(state);

        // Current state becomes the newly added state
        cursor++;

        // Remove oldest states if history is too large
        if ((int)history.size() > maxHistory) {
            history.erase(history.begin());

            // Cursor shifts left because index 0 was removed
            cursor--;
        }
    }

    bool undo() {
        // Cannot go before the first available state
        if (cursor <= 0) {
            return false;
        }

        cursor--;
        return true;
    }

    // Return ONLY the index of current state
    int currentState() {
        return cursor;
    }

    // Print all states currently available
    void printHistory() {
        cout << "History: ";

        for (int i = 0; i < (int)history.size(); i++) {

            if (i == cursor)
                cout << "[" << history[i] << "] ";
            else
                cout << history[i] << " ";
        }

        cout << "\n";

        cout << "Current index: " << cursor << "\n";
    }
};


int main() {

    VersionHistory vh(500);
    cout<<"Version History: "<<endl;
    cout<<" Enter the State(Number) U want to push in the History: "<<endl;
    int state;cin>>state;
    vh.pushState(state);
    while(true){
        cout<<" If u Want to push more state in the History then press 1 else if u want to undo the history press 0: "<<endl;
        int choice;
        cin>>choice;
        if(choice==1){
        cout<<" Enter the State(Number) U want to push in the History: "<<endl;
        cin>>state;
        vh.pushState(state);
      }
      else if(choice==0){
        cout<<"\nUndo\n";
        if(!vh.undo()){
          cout<<"No more states to undo\n";
        }
        
      }
      else{
        break;
      }
     vh.printHistory();
    }

    return 0;
}