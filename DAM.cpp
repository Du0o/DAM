#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h> 
#include <fstream>
#include <direct.h>  
#include <thread>
using namespace std;

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

void updateStats(){
  maxHealth = 100;
  if (clas == 'M'){
    maxMana = 100;
  }
  float extraHealth, extraMana;
  if (armor == "None"){
    extraHealth = 0;
  }
  else if (armor == "warriorRobe"){
    extraHealth = 75;
  }
  else if (armor == "archerRobe"){
    extraHealth = 30;
  }
  else if (armor == "None"){
    extraHealth = 40;
  }
  if (weapon == "basicSword"){
    damage = 25;
    speed = 75;
  }
  else if (weapon == "basicBow"){
    damage = 75;
    speed = 25;
  }
  else if (weapon == "basicWand"){
    damage = 50;
    speed = 50;
  }
  if (artfact1 == "None" || artfact2 == "None" || artfact3 == "None"){
    extraMana = 100;
  }
  else if (artfact1 == "manaSkull" || artfact2 == "manaSkull" || artfact3 == "manaSkull"){
    extraMana = 100;
  }
  maxHealth += extraHealth;
  maxMana += extraMana;
}
void useItem(string item){
  if(item == "HealthPotion" && health < maxHealth){
    health += 20;
    if(health > maxHealth)
      health = maxHealth;
  }
  else if(item == "ManaPotion" && mana < maxMana){
    mana += 20;
    if(mana > maxMana)
      mana = maxMana;
    cout << "Mana Potion used. Your mana is now at " << mana << "/" << maxMana << endl;
  }
  else if(item == "warriorRobe"){
    armor = item;
    updateStats();
  }
  else if(item == "basicSword"){
    weapon = item;
    updateStats();
  }
  else if(item == "manaSkull"){
    cout << "Which artifact slot? (1|2|3): ";
    cin >> input;
    if(input == '1'){
      artfact1 = item;
    }
    if(input == '2'){
      artfact2 = item;
    }
    if(input == '3'){
      artfact3 = item;
    }
  }
  else if(item == "yoo"){
    cout << "whoo are yoooooooo" << endl;
  }else
    cout << "You don't have that item." << endl;
}
void death(){
  system("cls");
  cout << R"(
                                   _____  _____
                                <     `/     |
                                 >          (
                                |   _     _  |
                                |  |_) | |_) |
                                |  | \ | |   |
                                |            |
                 ______.______%_|            |__________  _____
               _/                                       \|     |
              |                                                <
              |_____.-._________              ____/|___________|
                                |            |
                                |            |
                                |            |
                                |            |
                                |   _        <
                                |__/         |
                                 / `--.      |
                               %|            |%
                           |/.%%|          -< @%%%
                           `\%`@|     v      |@@%@%%    - mfj
                         .%%%@@@|%    |    % @@@%%@%%%%
                    _.%%%%%%@@@@@@%%_/%\_%@@%%@@@@@@@%%%%%%
  )";
  cin >> input;
}
void shop(string item1, string item2, string item3, string item4, string item5, int cost1, int cost2, int cost3, int cost4, int cost5){
  bool shoping = true;
  while(shoping == true){
    system("cls");
  cout << R"(
  ____________________________________________________
  ________             _________.__                   
  \______ \ _____     /   _____/|  |__   ____ ______  
  |    |  \\__  \    \_____  \ |  |  \ /  _ \\____ \
  |    `   \/ __ \_  /        \|   Y  (  <_> )  |_> >
  /_______  (____  / /_______  /|___|  /\____/|   __/ 
          \/     \/          \/      \/       |__|    
  ____________________________________________________
  )" << endl;
    cout << "Welcome to the shop! You have " << gold << " gold.";
    cout << "\n 1. " << item1 << "\n 2. " << item2 << "\n 3. " << item3 << "\n 4. " << item4 << "\n 5. " << item5 << endl;
    int choice;
    cin >> choice;
    
    if (choice == 1){
      cout << "Are you sure you want to buy " << item1 << "? y/n: ";
      cin >> input;
      if (input == 'y'){
        gold -= cost1;
        Inventory.push_back(item1);
      }
    }
    else if (choice == 2){
      cout << "Are you sure you want to buy " << item2 << "? y/n: ";
      cin >> input;
      if (input == 'y'){
        gold -= cost2;
        Inventory.push_back(item2);
      }
    }
    else if (choice == 3){
      cout << "Are you sure you want to buy " << item3 << "? y/n: ";
      cin >> input;
      if (input == 'y'){
        gold -= cost3;
        Inventory.push_back(item3);
      }
    }
    else if (choice == 4){
      cout << "Are you sure you want to buy " << item4 << "? y/n: ";
      cin >> input;
      if (input == 'y'){
        gold -= cost4;
        Inventory.push_back(item4);
      }
    }
    else{
      cout << "Are you sure you want to buy " << item5 << "? y/n: ";
      cin >> input;
      if (input == 'y'){
        gold -= cost5;
        Inventory.push_back(item5);
      }
    }
    cout << "Are you done shoping? y/n: ";
    cin >> input;
    if (input == 'y'){
      shoping = false;
    }
  }
}
void showStats(){
  cout << "Your Stats:\n Class: " << clas << "\n Health: " << health << "/" << maxHealth << "\n Mana: " << mana << "/" << maxMana << "\n Damage: " << damage << "\n Speed: " << speed << "\n" << "\n Weapon: " << weapon << "\n" << "\n Armor: " << armor << "\n" << "\n Artifact1: " << artfact1 << "\n" << "\n Artifact2: " << artfact2 << "\n" << "\n Artifact3: " << artfact3 << "\n";
}
//
void saveData(){
  ofstream file("saveData.txt");
  file << clas << "\n" << name << "\n" << health << "\n" << maxHealth << "\n" << mana << "\n" << maxMana << "\n" << damage << "\n" << speed << "\n" << gold << "\n" << chapterIndex << "\n" << artfact1 << "\n" << artfact2 << "\n" << artfact3 << "\n" << weapon << "\n" << armor << "\n" << campainIndex << "\n";
  for (string item : Inventory){
    file << item << "\n";
  }
  file.close();
}

void showInventory(){
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
      useItem(Inventory[input]);
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


void battle(string enemy, float enemyHealth, float enemyMaxHealth, float enemyDamage, float enemySpeed, string sprite , int gold, int enemyGold, vector<string> Inventory){
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
        death();
        exit(0);
        return;
      }
    } else {
      tempspeed = 0;
      if (input == 'A'){
        enemyHealth -= damage;
        if (clas == 'M'){
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
        if (clas == 'M'){
          mana += 10;
          if (mana > maxMana){
            mana = maxMana;
          }
        }
        if (health <= 0){
          death();
          exit(0);
          return;
        }
      }
      if (input == 'I'){
        showInventory();
      }
      if (input == 'E'){
        death();
        exit(0);
        return;
      }
      health -= enemyDamage;
      if (health <= 0){
        death();
        exit(0);
        return;
      }
    }

  }
}




int main() {
  Slime slime;
  //cout << "\e[8;50;50t";
  system("Color 03");
  // setup variables

  
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
      showStats();
    }
    else if (input == 'H'){
      system("cls");
      cout << "List of commands:\nHelp(H)\nStats(S)\nExit(E)\nInventory(I)\nStart Adventure(A)\nContinue Adventure(C)\nCredits(T)\n";
    }
    else if (input == 'E'){
      return 0;
    }
    else if (input == 'I'){
      showInventory();
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
        else if (clas == 'A'){
          weapon = "basicBow";
        }
        else {
          weapon = "basicWand";
        }
        saveData();
        
      }
      play = true;
    }
    else if (input == 'C'){
      int size = Inventory.size();
      // continue adventure
      ifstream file("saveData.txt");
      file >> clas >> name >> health >> maxHealth >> mana >> maxMana >> damage >> speed >> gold >> chapterIndex >> artfact1 >> artfact2 >> artfact3 >> weapon >> armor >> campainIndex; 
      Inventory.clear();
      for (int i = 0; i < 255; i++){
        string re = "";
        file >> re;
        if (re != ""){
          Inventory.push_back(re);
        }
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
      cout << "Chapter 0: Sands" << endl;
      shop("HealthPotion", "none", "none", "none", "none", 10, 20, 30, 40, 50);
      showInventory();
      saveData();
      cout << "" << endl;
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
      battle(slime.name, slime.enemyhealth, slime.maxEnemyHealth, slime.enemyDamage, slime.enemySpeed, slime.sprite, gold, slime.goldDrop, Inventory);
      system("cls");
      if (health <= 0){
        death();
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

 \ \/_\/ /( (_( )_) ))____) )( (_()____) )    |     \ \/_\/ // /____/     |      \ \ \   ( (_(  )_) )( (_(( (_____\
  )_____(  \/_/ \_\/ \____\/  \/_/\____\/     |      )_____( \/_/         |      /_/_/    \/_/  \_\/  \/_/ \/_____/ 
                                                                                                                    
      )" << "\n";
      cout << "Chapter 0: Sands \n";
      cin >> input;
      //battle(slimeEnemy.name, slimeEnemy.enemyhealth, slimeEnemy.maxEnemyHealth, slimeEnemy.enemyDamage, slimeEnemy.enemySpeed, slimeEnemy.sprite, gold, slimeEnemy.goldDrop , Inventory);
      system("cls");
      if (health <= 0){
        death();
      }
      cin >> input;
    }
  }
  return 0;
}