#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h> 
#include <fstream>
#include <direct.h>  
#include <thread>
using namespace std;


void death(string name){
  
}
void showStats(float health, float mana, float damage, float speed, float maxHealth, float maxMana, char classs, string weapon, string armor, string art1, string art2, string art3 ){
  cout << "Your Stats:\n Class: " << classs << "\n Health: " << health << "/" << maxHealth << "\n Mana: " << mana << "/" << maxMana << "\n Damage: " << damage << "\n Speed: " << speed << "\n" << "\n Weapon: " << weapon << "\n" << "\n Armor: " << armor << "\n" << "\n Artifact1: " << art1 << "\n" << "\n Artifact2: " << art2 << "\n" << "\n Artifact3: " << art3 << "\n";
}
void saveData(vector<string> Inventory, float health, float mana, float damage, float speed, float maxHealth, float maxMana, char classs, string name, int gold, int chapter, string art1, string art2, string art3, string weapon, string armor, int campain){
  ofstream file("saveData.txt");
  file << classs << "\n" << name << "\n" << health << "\n" << maxHealth << "\n" << mana << "\n" << maxMana << "\n" << damage << "\n" << speed << "\n" << gold << "\n" << chapter << "\n" << art1 << "\n" << art2 << "\n" << art3 << "\n" << weapon << "\n" << armor << "\n" << campain << "\n";
  for (string item : Inventory){
    file << item << "\n";
  }
  file.close();
}
void showInventory(vector<string> Inventory, int gold){
  char reponce;
  int itemIndex =  0;
  int input;
  system("cls"); // clear screen for better readability
  cout << "Your Inventory: \n";
  cout << "Gold: " << gold << "\n";
  cout << "Items: \n";
  for (string item : Inventory){
    cout << itemIndex<< ". " << item << "\n";
    itemIndex++;
  }
  cout << "Would you like to use any items? y/n: ";
  cin >> reponce;
  if (reponce == 'y'){
    cout << "\n" << "What item would you like to use? Item #:";
    cin >> input;
    if (input >= Inventory.size()){
      return;
    }
    cout << "Are you sure you want to use " << Inventory[input] << "? y/n: ";
    cin >> reponce;
    if (reponce == 'y'){
      
    }
  }
}






class Slime{
  public:
    float enemyhealth = 50, maxEnemyHealth = 50, enemyDamage = 20, enemySpeed = 10;
    int goldDrop = 10;
    string name = "Slime";
    string sprite = R"(
      ________________
     /                \
    /     0      o     \
   /    ------------    \
   \____________________/
    )";
  void attack(float health){
    health -= enemyDamage;
  }
  void dropGold(int gold){
    goldDrop += gold;
  }
  void takeDamage(float damage){
    enemyhealth -= damage;
  }
};


void battle(float health, float mana, float damage, float speed, float maxHealth, float maxMana, char classs, string weapon, string armor, string art1, string art2, string art3, string enemy, float enemyHealth, float enemyMaxHealth, float enemyDamage, float enemySpeed, string sprite , int gold, int enemyGold, vector<string> Inventory){

  bool battling = false;
  char input;
  int tempspeed = 0;
  while (battling == false){
    system("cls"); // clear screen for better readability
    cout << "Enemy HP: " << enemyHealth << "/" << enemyMaxHealth << sprite << "\n" << "Player HP: " << health << "/" << maxHealth << "\n" << "Player Mana: " << mana << "/" << maxMana << endl;
    cout << "| Attack(A) | Block(B) | Use Item(I) | Exit(E) |" << endl;
    cin >> input;
    if (enemySpeed > speed+tempspeed){
      cout << "You took " << enemyDamage << "!" << endl;
      health -= enemyDamage;
      if (health <= 0){
        return;
      }
    } else {
      tempspeed = 0;
      if (input == 'A'){
        enemyHealth -= damage;
        if (classs == 'M'){
          mana -= 20;
          if (mana > maxMana){
            mana = maxMana;
          }
        }
        cout << "You hit the enemy for " << damage << "!" << endl;
        if (enemyHealth <= 0){
          battling = true;
          gold += enemyGold;
          cout << "You killed the enemy and received " << enemyGold << " gold!" << endl;
        }
      }
      if (input == 'B'){
        cout << "You blocked the enemy's attack!" << endl;
        cout << "You took " << enemyDamage/2 << "!" << endl;
        health -= enemyDamage/2;
        tempspeed = 10000000;
        if (classs == 'M'){
          mana += 10;
          if (mana > maxMana){
            mana = maxMana;
          }
        }
        if (health <= 0){
          return;
        }
      }
      if (input == 'I'){
        showInventory(Inventory, gold);
      }
      if (input == 'E'){
        return;
      }
      health -= enemyDamage;
      if (health <= 0){
        return;
      }
    }

  }
}




int main() {
  Slime slimeEnemy;
  //cout << "\e[8;50;50t";
  system("Color 03");
  // setup variables
  string weapon = "None";
  string armor = "None";
  string artfact1 = "None";
  string artfact2 = "None";
  string artfact3 = "None";
  int chapterIndex = 0, campainIndex = 0;
  char input, clas;
  string name;
  bool makClass = false, play = false;
  float health, maxHealth, mana, maxMana, damage, speed;
  vector<string> Inventory = {"yoo", "mak"};
  int gold = 0;
  
  cout << R"(
   ______   _______  _______ 
  /  __  \ /  ___  \/       \
  | /  \  \| /   \ || /\ /\ |
  | |   \ || \___/ || || || |
  | |   | ||  ___  || |\_/| |
  | |   / || |   | || |   | |
  | (__/  /| /   \ || /   \ |  (Created by Teddy Todorov with c++/best played with fullscreen)
  \______/ |/     \||/     \| 
                           
  )" << "\n";
  cout << "Hello Adventurer! \n I am the DAM (dungeon artificial matrix)\n So what is your name travaler? ";
  cin >> name;
  while (makClass == false) { // making new character loop
    cout << "Greetings, " << name << "! \n What class do you want? Warrior(W) Archer(A) or Mage(M). if you want more information type (I): ";
    cin >> clas;
    if (clas == 'I'){
      system("cls");
      cout << "The 3 classes the are you can choose are Warrior, Archer, and Mage. The Warrior class is good for low level damage and high level speed, The Archer class is known for it high damage and low speed but reqireing arrows to attack, and the Mage class is a mana based class with all around stats. \n";
    }
    if (clas == 'W'){
      char confirm = 'n';
      system("cls");
      cout << "Ah it seems you are interseted in the Warrior class, with your quick strikes you will make quick work of your enemys! \n";
      cout << "Are you sure you want to pick this class? (THIS CAN'T BE CHANGED LATER!) y/n: ";
      cin >> confirm;
      if (confirm == 'y'){
        makClass = true;
        system("cls");
        cout << "Congrats! You have chosen the Warrior class! \n";
        health = 100, mana = 0, damage = 25, speed = 75, maxHealth = 100, maxMana = 0;
      } 
    }
    if (clas == 'A'){
      char confirm = 'n';
      system("cls");
      cout << "Ah it seems you are interseted in the Archer class, with your trusty bow nothing is impossible! \n";
      cout << "Are you sure you want to pick this class? (THIS CAN'T BE CHANGED LATER!) y/n: ";
      cin >> confirm;
      if (confirm == 'y'){
        makClass = true;
        system("cls");
        cout << "Congrats! You have chosen the Archer class! \n";
        health = 100, mana = 0, damage = 75, speed = 25, maxHealth = 100, maxMana = 0;
      } 
    }
    if (clas == 'M'){
      char confirm = 'n';
      system("cls");
      cout << "Ah it seems you are interseted in the Mage class, your intelect and knowlege is sure to trump all situations! \n";
      cout << "Are you sure you want to pick this class? (THIS CAN'T BE CHANGED LATER!) y/n: ";
      cin >> confirm;
      if (confirm == 'y'){
        makClass = true;
        system("cls");
        cout << "Congrats! You have chosen the Mage class! \n";
        health = 100, mana = 100, damage = 50, speed = 50, maxHealth = 100, maxMana = 100;
      } 
    }
  }
  while (play == false){
    cout << "What would you like to do? for help type (\"H\"): ";
    cin >> input;
    if (input == 'S'){
      system("cls");
      showStats(health, mana, damage, speed, maxHealth, maxMana, clas, weapon, armor, artfact1, artfact2, artfact3);
    }
    else if (input == 'H'){
      system("cls");
      cout << "List of commands:\nHelp(H)\nStats(S)\nExit(E)\nInventory(I)\nStart Adventure(A)\nContinue Adventure(C)\nCredits(T)\n";
    }
    else if (input == 'E'){
      return 0;
    }
    else if (input == 'I'){
      showInventory(Inventory, gold);
    }
    else if (input == 'A'){
      // start adventure
      cout << "Are you sure you want to start? (this will delete you other players save data) y/n: ";
      cin >> input;
      if (input == 'y'){
        Inventory.clear();
        cout << "What campaign do you want to start? Oasis Of Time(1)  WORKINPROGRESS(2) WORKINPROGRESS(3)";
        cin >> campainIndex;
        if (clas == 'W'){
          weapon = "basicSword";
        }
        if (clas == 'A'){
          weapon = "basicBow";
        }
        else {
          weapon = "basicWand";
        }
        saveData(Inventory, health, mana, damage, speed, maxHealth, maxMana, clas, name, gold, chapterIndex, artfact1, artfact2, artfact3, weapon, armor, campainIndex);
        
      }
      play = true;
    }
    else if (input == 'C'){
      // continue adventure
      ifstream file("saveData.txt");
      file >> clas >> name >> health >> maxHealth >> mana >> maxMana >> damage >> speed >> gold >> chapterIndex >> artfact1 >> artfact2 >> artfact3 >> weapon >> armor >> campainIndex; 
      Inventory.clear();
      for (int i = 0; i < 3; i++){
        string re = "";
        file >> re;
        Inventory.push_back(re);
      }
      file.close();
      play = true;
    }
    else if (input == 'T'){
      system("cls");
      cout << "Created by Teddy Todorov with c++ with some help from https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20 for ascii art font" << endl;
    }
  }
  if (campainIndex == 1){
    system("Color 06");
    if (chapterIndex == 0){
      system("cls");
      cout << R"(
   _____     _____    ______   __  ______             _____   _______            _______   __    __    __    _____  
  ) ___ (   /\___/\  / ____/\ /\_\/ ____/\    |     ) ___ (  /\_____\     |    /\_______)\/\_\  /_/\  /\_\ /\_____\
 / /\_/\ \ / / _ \ \ ) ) __\/ \/_/) ) __\/    |     / /\_/\ \( (  ___/    |    \(___  __\/\/_/  ) ) \/ ( (( (_____/ 
/ /_/ (_\ \\ \(_)/ /  \ \ \    /\_\\ \ \      |    / /_/ (_\ \\ \ \_      |      / / /     /\_\/_/ \  / \_\\ \__\
\ \ )_/ / // / _ \ \  _\ \ \  / / /_\ \ \     |    \ \ )_/ / // / /_\     |     ( ( (     / / /\ \ \\// / // /__/_  
 \ \/_\/ /( (_( )_) ))____) )( (_()____) )    |     \ \/_\/ // /____/     |      \ \ \   ( (_(  )_) )( (_(( (_____\
  )_____(  \/_/ \_\/ \____\/  \/_/\____\/     |      )_____( \/_/         |      /_/_/    \/_/  \_\/  \/_/ \/_____/ 
                                                                                                                    
      )" << "\n";
      cout << "Chapter 0: Sands \n";
      cin >> input;
      battle(health, mana, damage, speed, maxHealth, maxMana, clas, weapon, armor, artfact1, artfact2, artfact3, slimeEnemy.name, slimeEnemy.enemyhealth, slimeEnemy.maxEnemyHealth, slimeEnemy.enemyDamage, slimeEnemy.enemySpeed, slimeEnemy.sprite, gold, slimeEnemy.goldDrop , Inventory);
      system("cls");
      if (health <= 0){
        death(name);
      }
      cin >> input;
    }
  }
  if (campainIndex == 2){
    system("Color 06");
    if (chapterIndex == 0){
      system("cls");
      cout << R"(
   _____     _____    ______   __  ______             _____   _______            _______   __    __    __    _____  
  ) ___ (   /\___/\  / ____/\ /\_\/ ____/\    |     ) ___ (  /\_____\     |    /\_______)\/\_\  /_/\  /\_\ /\_____\
 / /\_/\ \ / / _ \ \ ) ) __\/ \/_/) ) __\/    |     / /\_/\ \( (  ___/    |    \(___  __\/\/_/  ) ) \/ ( (( (_____/ 
/ /_/ (_\ \\ \(_)/ /  \ \ \    /\_\\ \ \      |    / /_/ (_\ \\ \ \_      |      / / /     /\_\/_/ \  / \_\\ \__\
\ \ )_/ / // / _ \ \  _\ \ \  / / /_\ \ \     |    \ \ )_/ / // / /_\     |     ( ( (     / / /\ \ \\// / // /__/_  
 \ \/_\/ /( (_( )_) ))____) )( (_()____) )    |     \ \/_\/ // /____/     |      \ \ \   ( (_(  )_) )( (_(( (_____\
  )_____(  \/_/ \_\/ \____\/  \/_/\____\/     |      )_____( \/_/         |      /_/_/    \/_/  \_\/  \/_/ \/_____/ 
                                                                                                                    
      )" << "\n";
      cout << "Chapter 0: Sands \n";
      cin >> input;
      battle(health, mana, damage, speed, maxHealth, maxMana, clas, weapon, armor, artfact1, artfact2, artfact3, slimeEnemy.name, slimeEnemy.enemyhealth, slimeEnemy.maxEnemyHealth, slimeEnemy.enemyDamage, slimeEnemy.enemySpeed, slimeEnemy.sprite, gold, slimeEnemy.goldDrop , Inventory);
      system("cls");
      if (health <= 0){
        death(name);
      }
      cin >> input;
    }
  }
  if (campainIndex == 3){
    system("Color 06");
    if (chapterIndex == 0){
      system("cls");
      cout << R"(
   _____     _____    ______   __  ______             _____   _______            _______   __    __    __    _____  
  ) ___ (   /\___/\  / ____/\ /\_\/ ____/\    |     ) ___ (  /\_____\     |    /\_______)\/\_\  /_/\  /\_\ /\_____\
 / /\_/\ \ / / _ \ \ ) ) __\/ \/_/) ) __\/    |     / /\_/\ \( (  ___/    |    \(___  __\/\/_/  ) ) \/ ( (( (_____/ 
/ /_/ (_\ \\ \(_)/ /  \ \ \    /\_\\ \ \      |    / /_/ (_\ \\ \ \_      |      / / /     /\_\/_/ \  / \_\\ \__\
\ \ )_/ / // / _ \ \  _\ \ \  / / /_\ \ \     |    \ \ )_/ / // / /_\     |     ( ( (     / / /\ \ \\// / // /__/_  
 \ \/_\/ /( (_( )_) ))____) )( (_()____) )    |     \ \/_\/ // /____/     |      \ \ \   ( (_(  )_) )( (_(( (_____\
  )_____(  \/_/ \_\/ \____\/  \/_/\____\/     |      )_____( \/_/         |      /_/_/    \/_/  \_\/  \/_/ \/_____/ 
                                                                                                                    
      )" << "\n";
      cout << "Chapter 0: Sands \n";
      cin >> input;
      battle(health, mana, damage, speed, maxHealth, maxMana, clas, weapon, armor, artfact1, artfact2, artfact3, slimeEnemy.name, slimeEnemy.enemyhealth, slimeEnemy.maxEnemyHealth, slimeEnemy.enemyDamage, slimeEnemy.enemySpeed, slimeEnemy.sprite, gold, slimeEnemy.goldDrop , Inventory);
      system("cls");
      if (health <= 0){
        death(name);
      }
      cin >> input;
    }
  }
  return 0;
}