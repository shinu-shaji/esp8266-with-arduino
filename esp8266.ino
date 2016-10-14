/// this is a code to send data from an ultasound sensor to a database


int lastdistance=0;
int echopin = 11;
int triggerpin = 10;
String pass = "contra123";//wifi password
String ssid = "contra";//wifi ssid
boolean value = 0;
String SERVERIP = "192.168.43.196";//server ip addr
String connectionID = "0";



void setup(){
     
     Serial.begin(115200);
     pinMode(echopin,INPUT);
     pinMode(triggerpin,OUTPUT);
     connectwifi();
     delay(2000);
     Serial.write("AT+CIPMUX=1\r\n");   
     delay(100);   }

  
  void loop(){
      long distance = ultrasound();
      long lower  =distance-4;
      long higher =distance +4;
      if (lastdistance >= higher || lastdistance <= lower)  {
        String data = String(distance);
        String url = "GET /New1.php?dist=110 HTTP/1.0\r\nHost: 192.168.43.196\r\n ";
        int datalen= (url.length());
        
        String datalength = String(datalen);
        String url1="GET /New1.php?dist="+data+" ";
        String url2="HTTP/1.0\r\n";
        String url3="Host: 192.168.43.196\r\n  ";
        senddata(url1,url2,url3,datalength,connectionID);} //send the data
      lastdistance = distance;
      delay(1000);
    }
void senddata(String data1,String data2,String data3,String datalength,String connectionid){ //this function  connect and  send  the data
      String connection = "AT+CIPSTART=";
      connection = "AT+CIPSTART=0,\"TCP\",\""+SERVERIP+"\",80";
      delay(100);
      Serial.println(connection);
      delay(100);
       String tcpconnection = "AT+CIPSEND=";
      tcpconnection +=connectionid;
      tcpconnection +=",";
      tcpconnection +=datalength;
      tcpconnection +="\r\n";
      Serial.println(tcpconnection);
      delay(100);
      Serial.println(data1+"\r\n");
      Serial.println(data2+"\r\n");
      Serial.println(data3+"\r\n");
      delay(100);
      String connectionClose = "AT+CIPCLOSE=";
      connectionClose +=connectionid;
      connectionClose+="\r\n";
      delay(100);
      Serial.println(connectionClose);  
  }
  
  
  
    


void connectwifi(){   // function to connecting to wifi
        delay(100);
        while(true){
             Serial.println("AT\r\n");
             if (Serial.find("OK"))
               {   
                break;
                }
             else
                {
                 delay(100);
                  }
               }
          Serial.println("AT+CWMODE=3\r\n");
          delay(100);
        while(true){
              Serial.println("AT+CWJAP?");
              if (Serial.find("No AP"))
                 {
                    Serial.println("not connected");
                    Serial.println("AT+CWJAP=\""+ssid+"\",\""+pass+"\"\r\n");
                    delay(40000);
                   }
              else
                   {
                  Serial.println("connected");
                  break;
                     }
                        }
       }



        long ultrasound(){
    digitalWrite(triggerpin,LOW);
    delay(100);
    digitalWrite(triggerpin,HIGH);
    delay(100);
    digitalWrite(triggerpin,LOW);
    long duration = pulseIn(echopin,HIGH);
    long distance = duration/29/2;
    long cdistance = 200-distance;
    Serial.println(cdistance);
    return(distance);
     }
