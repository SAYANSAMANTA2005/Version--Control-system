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

    VersionHistory vh(5);

    vh.pushState(10);
    vh.pushState(20);
    vh.pushState(30);
    vh.pushState(40);
    vh.pushState(50);

    vh.printHistory();

    cout << "\nUndo\n";
    vh.undo();

    vh.printHistory();

    cout << "\nUndo\n";
    vh.undo();

    vh.printHistory();

    cout << "\nCurrent index = "
         << vh.currentState() << "\n";

    cout << "\nAdd 35 after undo\n";
    vh.pushState(35);

    vh.printHistory();

    cout << "\nAdd 45\n";
    vh.pushState(45);

    vh.printHistory();

    return 0;
}