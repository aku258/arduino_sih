/* rawR&cv.ino Example sketch for IRLib2
    Illustrate how to capture raw timing values for an unknow protocol.
    You will capture a signal using this sketch. It will output data the
    serial monitor that you can cut and paste into the "rawSend.ino"
    sketch.
*/
// Recommend only use IRLibRecvPCI or IRLibRecvLoop for best results
#include <IRLibRecvPCI.h>
#include<Math.h>

IRrecvPCI myReceiver(2);//pin number for the receiver

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
  
}

int output[150], index = 0, valLength = 0;

void loop() {
  //Continue looping until you get a complete signal received0
  int j, binBuffer[18], k;
  if (myReceiver.getResults()) {
    for (int i = 0; i < 100; i++)  {
      output[i] = 0;
    }
    index = 0;
    Serial.println(F("Do a cut-and-paste of the following lines into the "));
    Serial.println(F("designated location in rawSend.ino"));
    Serial.print(F("\n#define RAW_DATA_LEN "));
    Serial.println(recvGlobal.recvLength, DEC);
    Serial.print(F("uint16_t rawData[RAW_DATA_LEN]={\n\t"));
    for ( j = 0 ; j < recvGlobal.recvLength ; j++)
    {
      int s = recvGlobal.recvBuffer[j];
      if (1250 <= s && s <= 1450) {
        output[j] = 1;
      } else if (350 <= s && s <= 600) {
        output[j] = 0;
      }
     // Serial.print(s);
     // Serial.print(" , ");
    }
  long a[4]={0};
  int i=0;
    for(int k=0 ; k<recvGlobal.recvLength;)
    {
      for(int j=0 ; j<32 ; j++)
      {
        a[i] += output[j+i*32]<<(31-j);
        if(i==0)
        {
          Serial.println(a[i]);
          Serial.println(output[j+i*2]);
          Serial.println(j+i*2);
        }
        k++;
      }
      Serial.println(a[i]);
      i++;
    }
    Serial.println(a[0]);
    for (int i = 0; i < recvGlobal.recvLength; i++) {
     // Serial.print(output[i]);
    }
    Serial.println();
    int sum = 0;
    for (k = 0 ; k < recvGlobal.recvLength;)
    {
      sum = 0;
      for (int l = 0 ; l < 4; l++)
      {
        
        if(l==0 &&output[k]==1)
          sum++;
      /*  Serial.print(k);
        Serial.print(", ");
        Serial.print(3-l);
        Serial.print(", ");
        Serial.print(pow(2, 3 - l) * output[k]);
        Serial.print(", ");
        
        Serial.print((int)(pow(2.00, (3.00 - l)) * output[k]));
        Serial.print(", ");
        Serial.print(sum);
        Serial.print(", ");
        */
        
        //Serial.println(output[k]);
        sum = sum + (pow(2.00, 3 - l) * output[k]);
        k++;
      }
      
      //Serial.print(" = ");
      
        
      switch (sum)
      {
        case 10:
          Serial.print("A");
          break;
        case 11:
          Serial.print("B");
          break;
        case 12:
          Serial.print("C");
          break;
        case 13:
          Serial.print("D");
          break;
        case 14:
          Serial.print("E");
          break;
        case 15:
          Serial.print("F");
          break;
        default: Serial.print(sum);
      }
     // Serial.println();
    }
    //if ( (i % 8) == 0) Serial.print(F("\n\t"));
    //}
    //    Serial.println(F("1000};"));//Add arbitrary trailing space
    myReceiver.enableIRIn();      //Restart receiver
  }
}


