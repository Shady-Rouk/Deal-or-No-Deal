
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;




float remTot(float amt[], string box[]){ //declares function to calculate sum of amounts in remaining boxes
  float total = 0; //declares float for the sum
  for(int v=0; v<26; v++){ //creates for loop to run 26 times
    if(box[v] != "X"){ //checks that a box has not already been chosen
      total += amt[v]; //adds the amount in that box to total
    }
  }
  return total; //returns total to main
}

float Bankoffer(float remTotal, int casesLeft){ //declares function to calculate banker's offer
  float value = 0; //declares float for the offer amount
  value = 10000 + (-2714.74 * casesLeft) + (.04 * remTotal); //assigns calculation expression for banker's offer to value
  return value; //returns value to main
}

int remBoxes(string boxes[]){ //declares function to find number of boxes that have not been picked
  int count = 0; //declares a counter variable
  for(int l=0; l<26; l++){ //creates for loop to run 26 times
    if(boxes[l] != "X"){ //checks that a box has not already been chosen 
      count++; //increments the value of count
    }
  }
  return count; //returns count to main
}

int main(){
  
  //reading and assigning
  ifstream reader; //creates fstream object reader
  reader.open("file.txt"); //opens file.txt for reading
  string boxNameArr[26]; //creates a string array for the box names
  float amountArr[26], pot = 0; //creates a float array for the box amounts and a float variable for the potential winnings
  int xCheck = 0; //declares int variable to monitor how many boxes have been chosen
  float choices[26]; //declares float array to monitor amounts of the boxes the user chooses
  
  for(int i=0; i<26; i++){ //creates for loop to run 26 times
    reader >> boxNameArr[i] >> amountArr[i]; //reads from file.txt into the box name and box amount arrays
  }
  for(int i=0; i<26; i++){ //creates for loop to run 26 times
    choices[i] = amountArr[i]; //assigns choices[i] to amountArr[i]
  }
  reader.close(); //closes file.txt
  
  string UserName, decision = "n"; //declares string variables to hold user name and decision to take a deal or not
  cout << "Enter your name" << endl; //asks user for their name
  cin >> UserName; //assigns user input to UserName
  cout << UserName <<", welcome to Deal or No Deal!\n"; //welcomes the user
  
  
  //real work
  int userChoice; //declares int variable to hold user box to keep choice
  cout << "Choose a box to keep  (Enter a number between 0 and 25)\n"; //asks user to choose a box to keep
  cin >> userChoice; //assigns user input to userChoice
  float userAmt = amountArr[userChoice]; //declares userAmt and sets its value to amountArr[userChoice]
  boxNameArr[userChoice] = "X"; //marks user box choice as taken in boxNameArr
  
  while(decision=="n" && xCheck<21){ //creates while loop to run as long as user doesn't accept a deal and they have not opened all boxes
  for(int j=0; j<5; j++){ //creates for loop to run 5 times
    cout << "Choose a box to open  (Enter a number between 0 and 25)\n"; //asks user to choose a box to open
    int choice; //declares int variable to hold user box to open choice
    cin >> choice; //ssigns user input to choice
    choices[choice] = 0; //changes the value of choices[choice] to 0 to indicate that the amount has been chosen
    boxNameArr[choice] = "X"; //marks boxNameArr[choice] as taken
    xCheck++; //increments the value of xCheck
    cout << "It has $" << fixed << showpoint << setprecision(2) << amountArr[choice] << " inside" << endl; //tells user the amount of money in the box they chose
  }
  
  int rem = remBoxes(boxNameArr); //calculates the value of remaining boxes
  float remT = remTot(amountArr, boxNameArr); //calculates the sum of the amounts in th eremaining boxes
  float offer = Bankoffer(remT, rem); //calculates the banker's offer
  if (xCheck < 21){ //checks if xCheck is less than 21
    pot = offer; //sets potential winnings to the current banker's offer
  }
  if(xCheck < 21){ //checks if xCheck is less than 21
  cout << "Banker offer: : $" << offer << endl; //prints the banker's offer to the user
  cout << "Remaining boxes\n"; //starts a list of remaining boxes
  for(int u=0; u<26; u++){ //creates for loop to run 26 times
    if(boxNameArr[u] == "X"){ //checks if boxNameArr[u] has been marked as taken
      cout << " " << boxNameArr[u] << " "; //prints out "X" in the remaining boxes list
    }
    else{ //else
      cout << " " << u << " "; //prints out the box number
    }
  }
  }
  cout << endl; //prints end of line character
  if(xCheck < 21){ //checks if xCheck is less than 21
  cout << "deal or no deal (d/n)\n"; //asks user if they will take the deal or not
  cin >> decision; //assigns user input to decision
  }
  }
  cout << "Let’s see how you did!\n"; //preps user for their game progress
  if(decision == "n"){
    cout << "Potential Winnings: $" << fixed << showpoint << setprecision(2) << pot << endl; //prints the potential winnings to the user
    cout << "Winnings: $" << fixed << showpoint << setprecision(2) << userAmt << endl; //prints the amount in the box the user chose
  }
  else{
    cout << "Potential Winnings: $" << fixed << showpoint << setprecision(2) << userAmt << endl; //prints the amount in the box the user chose as potential winnings
    cout << "Winnings: $" << fixed << showpoint << setprecision(2) << pot << endl; //prints the potential winnings to the user as their winnings
  }
  cout << "Would you like to see what is in the remaining boxes?(yes/no)" << endl; //asks user if they would like to see what's in the remaining boxes
  string look; //declares string variable to hold user decision to see the remaining boxes
  cin >> look; //assigns user input to look
  if(look != "no"){ //checks that user wants to see the remaining boxes
    cout << "Remaining boxes\n"; //starts the remaining boxes list
    for(int r=0; r<26; r++){ //creates for loop to run 26 times
      cout << "Box " << r << ": $" << fixed << showpoint << setprecision(2) << choices[r] << endl; //prints the box number and the amount currently in it
    }
  }
  return 0;
}
