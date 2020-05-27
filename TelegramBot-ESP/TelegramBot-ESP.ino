#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Initialize Wifi connection to the router
char ssid[] = "myname";     // your network SSID (name)
char password[] = "satrio2709"; // your network key

// Initialize Telegram BOT
#define BOTtoken "1268144171:AAGiCQsY_T-f5miWJ0Ejz_77P9P169_wSN4"  // your Bot Token (Get from Botfather)

WiFiClientSecure client;

UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done

String defaultChatID = "728192608";

void setup() {
  Serial.begin(9600);
  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  client.setInsecure();
}

void loop() {
  Serial.print("millis()\t: ");
  Serial.println(millis());
  Serial.println("<--Checking-->");
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    Serial.print("Bot_lasttime\t: ");
    Serial.println(Bot_lasttime);
    Serial.print("Bot_mtbs\t: ");
    Serial.println(Bot_mtbs);
    Serial.print("bot.last_message_received\t: ");
    Serial.println(bot.last_message_received);
    Serial.print("numNewMessages\t: ");
    Serial.println(numNewMessages);
    while(numNewMessages) {
      Serial.println("got response");
      for (int i=0; i<numNewMessages; i++) {
        Serial.println(bot.messages[i].chat_id);
        Serial.println(bot.messages[i].text);

        String chat_id = String(bot.messages[i].chat_id);
        String text = bot.messages[i].text;
        String from_name = bot.messages[i].from_name;
        if (from_name == "") from_name = "Shounen";

        if (text == "/start") {
          String welcome = "Ara-ara, irasshaimase " + from_name + "-san.\n";
          bot.sendMessage(chat_id, welcome, "Markdown");
        }else{
          bot.sendMessage(bot.messages[i].chat_id, bot.messages[i].text, "");
        }
      }
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
    Serial.print("Last Bot_lasttime\t: ");
    Serial.println(Bot_lasttime);
  }
  Serial.println("Done");
}
