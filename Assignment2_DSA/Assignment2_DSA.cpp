//Test file
#include <iostream>
#include "ClubManager.h"
using namespace std;

//Function header(s)
void generatePrompt();
int takeInput();
bool takeNumber(int& number);
void processRequest(int choice, clubManager& manager);
//request loop
int main()
{
    clubManager management;
    cout << "\n\t<<< WELCOME TO CHESS CLUB PORTAL >>>" << endl;
    int userResponse = 9;//arbitrary response
    while (userResponse) {
        generatePrompt();
        userResponse = takeInput();
        processRequest(userResponse, management);
    }cout << "Thanks for visiting! <3" << endl;
    return 0;
}
void generatePrompt() {
    cout << "\tHow can we serve you now? Press:(0-8) " << endl;
    cout << "\\_______________________________________________________/\n";
    cout << "\t1. New Registeration" << endl;
    cout << "\t2. Find Player's Profile" << endl;
    cout << "\t3. Remove Player" << endl;
    cout << "\t4. Conduct Match" << endl;
    cout << "\t5. Display Recent Event" << endl;
    cout << "\t6. Display Alphabetical Roaster" << endl;
    cout << "\t7. Display LeaderBoard" << endl;
    cout << "\t8. Find K-Nearest matchmacking opponents" << endl;
    cout << "\t0. Quit" << endl;
    cout << "\\______________________________________________________/\n";
}
int takeInput() {
    int response;

    cout << "\nYour choice: ";

    if (!(cin >> response)) {
        if (cin.eof())//input stream is closed, quit instead of looping forever
            return 0;
        cin.clear();
        cin.ignore(1000, '\n');
        return -1;
    }
    cin.ignore(1000, '\n');//throw away anything left on the line
    return response;
}
bool takeNumber(int& number) {
    if (!(cin >> number)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }
    cin.ignore(1000, '\n');
    return true;
}
void processRequest(int choice, clubManager& manager) {
    string name;
    string other;
    int option = 0;
    int k = 0;
    switch (choice) {
    case 0:
        break;
    case 1:
        cout << "\nPlayer Username: ";
        cin >> name;
        manager.registerPlayer(name, 0, 0, 0, 0);
        break;
    case 2:
        cout << "\nPlayer Username: ";
        cin >> name;
        manager.revealPlayer(name);
        break;
    case 3:
        cout << "\nPlayer Username: ";
        cin >> name;
        manager.removePlayer(name);
        break;
    case 4:
        cout << "\nFirst Player Username: ";
        cin >> name;
        cout << "Second Player Username: ";
        cin >> other;
        manager.conductMatch(name, other);
        break;
    case 5:
        cout << "\n1. Forward (Head -> Tail)\n2. Backward (Tail -> Head)\nYour choice: ";
        if (!takeNumber(option)) {
            cout << "Invalid Choice!Try Again..." << endl;
            break;
        }
        switch (option) {
        case 1:
            manager.revealNoticeBoard();
            break;
        case 2:
            manager.revealNoticeBoardBackward();
            break;
        default:
            cout << "Invalid Choice!Try Again..." << endl;
        }
        break;
    case 6:
        cout << "\n1. Full Roster (A -> Z)\n2. Range of Usernames\nYour choice: ";
        if (!takeNumber(option)) {
            cout << "Invalid Choice!Try Again..." << endl;
            break;
        }
        switch (option) {
        case 1:
            manager.revealDirectory();
            break;
        case 2:
            cout << "From: ";
            cin >> name;
            cout << "To: ";
            cin >> other;
            manager.revealDirectoryRange(name, other);
            break;
        default:
            cout << "Invalid Choice!Try Again..." << endl;
        }
        break;
    case 7:
        cout << "\n1. Ascending (Lowest First)\n2. Descending (Highest First)\n3. Highest Player\n4. Lowest Player\nYour choice: ";
        if (!takeNumber(option)) {
            cout << "Invalid Choice!Try Again..." << endl;
            break;
        }
        switch (option) {
        case 1:
            manager.revealLeaderBoard();
            break;
        case 2:
            manager.revealLeaderBoardDescending();
            break;
        case 3:
            manager.revealTopPlayer();
            break;
        case 4:
            manager.revealBottomPlayer();
            break;
        default:
            cout << "Invalid Choice!Try Again..." << endl;
        }
        break;
    case 8:
        cout << "\nPlayer Username: ";
        cin >> name;
        cout << "Number of opponents (k): ";
        if (!takeNumber(k)) {
            cout << "k must be a number!" << endl;
            break;
        }
        manager.revealNearbyPlayers(name, k);
        break;
    default:
        cout << "Invalid Choice!Try Again...\n";
    }
}