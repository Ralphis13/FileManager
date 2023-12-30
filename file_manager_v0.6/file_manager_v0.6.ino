#include <SPI.h>
#include <SD.h>
#include "U8glib.h"
U8GLIB_ST7920_128X64_1X u8g( 40, 42, 44);

String directory = "/";
String myStrings[255];
String myText[5];
int INDEX; 
int POSITIONcursor; 
int INDEXcursor;
int INDEXtextline;
bool up;
bool down;
bool left;
bool right;
bool TXTopen;
int TXTpage=1;
String text="";
int leterBUFER;
long leterNUMER;

void setup() {
  pinMode(7, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  printDirectory(SD.open(directory));//print the contents of the directory
}

void printDirectory(File dir) {
  int i=0;
  while (true) {  
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }

   myStrings[i] = entry.name();          
    if (entry.isDirectory()) {
      myStrings[i] += "/";
    }
    i=i+1;
    entry.close();
  }
}

void draw() {
up = digitalRead(7);
down = digitalRead(5);
left = digitalRead(2);
right = digitalRead(3);
u8g.setFont(u8g_font_6x12);
u8g.setColorIndex(1);

if(TXTopen==0){
u8g.drawBox(0,POSITIONcursor*10,128,12);  
}

if(TXTopen==0){
if (POSITIONcursor==0){
  u8g.setColorIndex(0);
u8g.setPrintPos( 0, 10); u8g.print(myStrings[INDEX]);  
u8g.setColorIndex(1);
}else{
  u8g.setPrintPos( 0, 10); u8g.print(myStrings[INDEX]);  
}
if (POSITIONcursor==1){
  u8g.setColorIndex(0);
u8g.setPrintPos( 0, 20); u8g.print(myStrings[INDEX+1]);  
u8g.setColorIndex(1);
}else{
  u8g.setPrintPos( 0, 20); u8g.print(myStrings[INDEX+1]);  
}
if (POSITIONcursor==2){
  u8g.setColorIndex(0);
u8g.setPrintPos( 0, 30); u8g.print(myStrings[INDEX+2]);  
u8g.setColorIndex(1);
}else{
  u8g.setPrintPos( 0, 30); u8g.print(myStrings[INDEX+2]);  
}
if (POSITIONcursor==3){
  u8g.setColorIndex(0);
u8g.setPrintPos( 0, 40); u8g.print(myStrings[INDEX+3]);  
u8g.setColorIndex(1);
}else{
  u8g.setPrintPos( 0, 40); u8g.print(myStrings[INDEX+3]);  
}
if (POSITIONcursor==4){
  u8g.setColorIndex(0);
u8g.setPrintPos( 0, 50); u8g.print(myStrings[INDEX+4]);  
u8g.setColorIndex(1);
}else{
  u8g.setPrintPos( 0, 50); u8g.print(myStrings[INDEX+4]);  
}
if (POSITIONcursor==5){
  u8g.setColorIndex(0);
u8g.setPrintPos( 0, 60); u8g.print(myStrings[INDEX+5]);  
u8g.setColorIndex(1);
}else{
  u8g.setPrintPos( 0, 60); u8g.print(myStrings[INDEX+5]);  
}
  
}
if(TXTopen==1){
u8g.setPrintPos( 0, 10); u8g.print(text.substring(0, 21));  
u8g.setPrintPos( 0, 20); u8g.print(text.substring(21, 42));  
u8g.setPrintPos( 0, 30); u8g.print(text.substring(42, 63));  
u8g.setPrintPos( 0, 40); u8g.print(text.substring(63, 84));  
u8g.setPrintPos( 0, 50); u8g.print(text.substring(84, 105));  
u8g.setPrintPos( 0, 60); u8g.print(text.substring(105, 126));    
}

if(up==0){
  if(TXTopen==0){
 if (INDEXcursor>0){
    INDEXcursor=INDEXcursor-1;
  }
  if(POSITIONcursor >=1){
    POSITIONcursor--;
  }else{
   if(INDEX>=1){
    if (POSITIONcursor==0){
       INDEX=INDEX-1;
    }
}
  }
 } 
    if(TXTopen==1){
      if(TXTpage>1){
    TXTpage=TXTpage-1;
    leterNUMER=leterNUMER-126-leterBUFER;
    OPEN_TXT_FILE();        
      }
  }
 delay(200);
}

if(down==0){
  if(TXTopen==0){
if(myStrings[INDEXcursor+1]!=""){  
  if (INDEXcursor<255){
    INDEXcursor=INDEXcursor+1;
  }
  if (POSITIONcursor <=4){
    POSITIONcursor++;
  }else{
if(INDEX<=255){
  if (POSITIONcursor==5){
  INDEX=INDEX+1;
  }    
  }
}
  
}
}
  if(TXTopen==1){
    if(leterBUFER==126){
    TXTpage=TXTpage+1;
    OPEN_TXT_FILE();      
    }
  }
 delay(200);
}

if(left==0){
  selectpoint(myStrings[INDEXcursor], 0);
  if(TXTopen==1){
    leterNUMER=0;
    TXTpage=1;
    TXTopen=0;
  }
  delay(300);
}
if(right==0){  
  if(TXTopen==0){
    selectpoint(myStrings[INDEXcursor], 1);
  }
  delay(300);
}
}
  
char selectpoint(String filename, bool tipe){
  POSITIONcursor=0;
  INDEXcursor=0;
  INDEX=0;
for (int i = 0; i < 255; i++){
   myStrings[i]="";
   }
   if (tipe==0){
    //substring()
    //length()
if (directory.endsWith("/")==true){
  directory=directory.substring(0, directory.lastIndexOf("/"));
}else{
  directory=directory.substring(0, directory.lastIndexOf("/")+1);
}
if (directory.endsWith("/")==true){
  directory=directory.substring(0, directory.lastIndexOf("/"));
}else{
  directory=directory.substring(0, directory.lastIndexOf("/")+1);
}
   }
   if (tipe==1){
  directory+=filename;
  if (directory.length()-directory.lastIndexOf(".")<5){
    if (directory.substring(directory.lastIndexOf("."))==".TXT"){
      TXTopen=1;  
  POSITIONcursor=0;
  INDEXcursor=0;
  INDEX=0;
for (int i = 0; i < 255; i++){
   myStrings[i]="";
   }
      OPEN_TXT_FILE();     
    }    
  }

   }
  printDirectory(SD.open(directory));//print the contents of the directory
  Serial.println(directory);
}
 
void loop(){
    u8g.firstPage();
    do
    {
        draw();
    }
    while(u8g.nextPage());
    delay(10);
}
void OPEN_TXT_FILE(){
  File myfile = SD.open(directory);
  text="";
  leterBUFER=0;
  if (myfile){
    while (myfile.available() and leterBUFER<126){
      myfile.seek(leterNUMER);      
      byte leter;
     leter=myfile.read(); 
     //Serial.println(leter);
     if (leter==32){text+=" ";}if (leter==113){text+="q";}if (leter==119){text+="w";}if (leter==101){text+="e";}
     if (leter==114){text+="r";}if (leter==116){text+="t";}if (leter==121){text+="y";}if (leter==117){text+="u";}
     if (leter==105){text+="i";}if (leter==111){text+="o";}if (leter==112){text+="p";}if (leter==97){text+="a";}
     if (leter==115){text+="s";}if (leter==100){text+="d";}if (leter==102){text+="f";}if (leter==103){text+="g";}
     if (leter==104){text+="h";}if (leter==106){text+="j";}if (leter==107){text+="k";}if (leter==108){text+="l";}
     if (leter==122){text+="z";}if (leter==120){text+="x";}if (leter==99){text+="c";}if (leter==118){text+="v";}
     if (leter==98){text+="b";}if (leter==110){text+="n";}if (leter==109){text+="m";}if (leter==51){text+="3";}
     if (leter==52){text+="4";}if (leter==53){text+="5";}if (leter==54){text+="6";}if (leter==55){text+="7";}
     if (leter==56){text+="8";}if (leter==57){text+="9";}if (leter==46){text+=".";}if (leter==44){text+=",";}
     if (leter==81){text+="Q";}if (leter==87){text+="W";}if (leter==69){text+="E";}if (leter==82){text+="R";}
     if (leter==84){text+="T";}if (leter==89){text+="Y";}if (leter==85){text+="U";}if (leter==73){text+="I";}
     if (leter==79){text+="O";}if (leter==80){text+="P";}if (leter==65){text+="A";}if (leter==83){text+="S";}
     if (leter==68){text+="D";}if (leter==70){text+="F";}if (leter==71){text+="G";}if (leter==72){text+="H";}
     if (leter==74){text+="J";}if (leter==75){text+="K";}if (leter==76){text+="L";}if (leter==90){text+="Z";}
     if (leter==88){text+="X";}if (leter==67){text+="C";}if (leter==86){text+="V";}if (leter==66){text+="B";}
     if (leter==78){text+="N";}if (leter==77){text+="M";}
      leterBUFER++;
      leterNUMER++;
    }    
    Serial.println(text);   
    myfile.close();
  }  
  else
  {
    Serial.println("error opening the text file");
  }
}
