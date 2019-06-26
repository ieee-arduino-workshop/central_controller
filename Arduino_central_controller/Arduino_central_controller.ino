
/*
* Arduino central controller
*       
*   created by Long Tran 26/06/2019
* 
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <packet.h>
#include <game_engine.h>

#define CE 5   // set chip enable pin
#define CSN 10 //Set chip select pin.

/// create object RF24
RF24 radio(CE, CSN); // CE, CSN
/// address of sender_01, can create 6 address for 6 different sender
const byte address[6] = "00001";

/// create a standard packet to be received.
packet Player1;

void setup()
{
  // init serial port for debugging
  Serial.begin(115200);
  Player1.packet_data = 0;
  Player1.up = 1;
  Serial.println(Player1.packet_data, BIN);
  // initialize RF24 module
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  randomSeed(analogRead(0));
}

void print_data(packet player)
{
  Serial.print("-----------------------------------------------\n");
  Serial.print("Player ID: ");
  Serial.println(Player1.player_id, BIN);

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

uint16_t prev_value = 0;

game_manager soccer_game(70, 20);
//Player1.up=1;
uint16_t test_movement_data;
void loop()
{
  // if (radio.available())
  // {
  //   //uint16_t text;
  //   // radio.read(&text, sizeof(text));
  //   //radio.read(&text, sizeof(text));
  //   //Serial.println(text,BIN);
  //   radio.read(&Player1.packet_data, sizeof(Player1.packet_data));
  //   //Serial.println(Player1.packet_data, BIN);

  //   if (prev_value != Player1.packet_data)
  //   {
  //     print_data(Player1);
  //   }
  //   prev_value = Player1.packet_data;
  // }

  // Serial.println(random(0,15));
  //Packet.packet_data = Packet.packet_data & 0xFFE7 ;// 11111111 11100111;

  /**
   * @brief ----------create random data for one player-----------------------------
   *
   * packet_data format: |3-reserved-bits|right|left|down|up|kick|8-bit ID|
   *  
   */

  test_movement_data = 3;

  ///remove the case when both up-down or left-right active at the same time
  while ((test_movement_data == 3) || (test_movement_data == 11) || (test_movement_data == 7))
  {
    test_movement_data = random(0, 11);
  }

  /// add movement data to the packet to simulate movement
  Player1.packet_data = (Player1.packet_data & 0xE1FF) | test_movement_data << 9;
  ///--------------------------------------------------------------------------

  ///call method in game_manager class.
  soccer_game.Input(&Player1);
  soccer_game.Logic();
  soccer_game.Draw();
}
