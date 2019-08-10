
/**
* Arduino central controller
*   
* updated 27/06/2019 - server can connect to multi-player now.
*
*   created by Long Tran 26/06/2019
*   
*
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <packet.h>
#include <GameManager.h>

#define CE 5   // set chip enable pin
#define CSN 10 //Set chip select pin.

//set limit to 6 as currently the game enginer only support 6 
#define NO_PLAYER 6

/// create object RF24
RF24 radio(CE, CSN); // CE, CSN
// uint16_t prev_value = 0;
GameManager soccer_game(720, 480, 6);
/// address of sender_01, can create 6 address for 6 different sender
//const byte address[2][6] = {"00001", "00002"};
// const byte address[][6] = {"00001","22222"};
const uint64_t address[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};
// const byte address_2[6] = "00002";
/// create a standard packet to be received.

// create player for the game
packet Player_packet; //[NO_PLAYER];

void setup()
{
  // init serial port for debugging
  Serial.begin(115200);
  Serial1.begin(115200);

  // for (int i = 0; i < NO_PLAYER; i++)
  // {
  //   Player_packet[i].packet_data = 0;
  //   Serial.println(Player_packet[i].packet_data, BIN);
  // }

  Player_packet.packet_data = 0;
  // initialize RF24 module
  radio.begin();
  //radio.setPALevel(RF24_PA_MIN);
  radio.setPALevel(RF24_PA_HIGH);
  //radio.setChannel(108);
  // radio.setPALevel(RF24_PA_MAX);
  for (int i = 0; i < 6; i++)
  {
    radio.openReadingPipe(i, address[i]);
  }
  // radio.openReadingPipe(0, address[0]);
  // radio.openReadingPipe(1, address[1]);
  // radio.openReadingPipe(0, address[1]);
  radio.startListening();

  randomSeed(analogRead(0));
}

void print_data(packet player)
{
  Serial.print("-----------------------------------------------\n");

  char charVal[3];
  sprintf(charVal, "%02X", player.player_id);
  Serial.print("Player ID: ");
  Serial.println(charVal);

  if (player.left == 1)
  {
    Serial.print(F("LEFT  \t"));
  }
  else if (player.right == 1)
  {
    Serial.print(F("RIGHT  \t"));
  }

  if (player.up == 1)
  {
    Serial.print(F("UP  \t"));
  }
  else if (player.down == 1)
  {
    Serial.print(F("DOWN  \t"));
  }

  if (player.kick == 1)
  {
    Serial.print(F("SHOOT  \n"));
  }
  else
  {
    Serial.print(F("\n-------------------------------------------\n"));
  }

}



/**
   * @brief ----------create random data for one player-----------------------------
   *
   * packet_data format: |3-reserved-bits|right|left|down|up|kick|8-bit ID|
   *  
   */
uint16_t random_data(uint16_t data)
{
  uint16_t test_movement_data = 3;
  while ((test_movement_data == 3) || (test_movement_data == 11) || (test_movement_data == 7))
  {
    test_movement_data = random(0, 11);
  }

  /// add movement data to the packet to simulate movement
  data = (data & 0xE1FF) | test_movement_data << 9;
  return data;
}

long previous = 0;
void loop()
{
  ///test time to execute program
  // Serial.println(micros()-previous);
  // previous=micros();

  byte pipeNum = 0;
  uint16_t gotData = 0; //2-bytes data is save imn this buffer
  //scan incoming RF package, each pipeNum is equavilent a player
  while (radio.available(&pipeNum))
  {
    radio.read(&gotData, 2); /// read 2-byte of data
    Serial.print("Received data from pipe: ");
    Serial.println(pipeNum + 1); //print which pipe or transmitter this is from
    // Serial.print("They guess number: ");
    // Serial.println(gotData); //print payload or the number the transmitter guessed

    //Serial.println(Player1.packet_data, BIN);
    // Player_packet[pipeNum].packet_data = gotData;
    Player_packet.packet_data = gotData;
    // if (prev_value != Player1.packet_data)
    // Serial.print("Player ID ");
    // Serial.println(Player_packet.player_id); //print payload or the number the transmitter guessed
    // print_data(Player_packet);
    // prev_value = Player1.packet_data;
    soccer_game.input(&Player_packet);
    soccer_game.logic();
    // soccer_game.draw();
    soccer_game.send();
    // Serial.println(micros()-previous);
    // previous=micros();
    
  }  
  // enable draw function for debugging purpose
  

  // Serial.println(random(0,15));
  //Packet.packet_data = Packet.packet_data & 0xFFE7 ;// 11111111 11100111;

  // // test_movement_data = 3;

  // ///remove the case when both up-down or left-right active at the same time
  // while ((test_movement_data == 3) || (test_movement_data == 11) || (test_movement_data == 7))
  // {
  //   test_movement_data = random(0, 11);
  // }

  // /// add movement data to the packet to simulate movement
  // Player1.packet_data = (Player1.packet_data & 0xE1FF) | test_movement_data << 9;
  // ///--------------------------------------------------------------------------

  // Player1.packet_data=random_data(Player1.packet_data);
  ///call method in game_manager class.
}
