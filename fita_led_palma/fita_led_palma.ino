
#define Rout  9
#define Gout  10
#define Bout  11
#define Led 12
#define Palmain 7 // switch in

int R = 0, G = 0, B = 0, atual = 0, i;
boolean cont = 0, mudanca, palma, duracao;

//**********MATRIZ DE CORES*************
// inteiros
int cores[28][3]  = { // todas combinações possíveis considerando 0, 127 e 255
  0, 0, 0,
  0, 0, 255,
  0, 255, 0,
  0, 255, 255,
  255, 0, 0,
  255, 0, 255,
  255, 255, 0,
  255, 255, 255,

  //quebrados
  128, 0, 0,
  128, 0, 128,
  128, 0, 255,
  128, 128, 0,
  128, 128, 128,
  128, 128, 255,
  128, 255, 0,
  128, 255, 128,
  128, 255, 255,

  0, 128, 0,
  0, 128, 128,
  0, 128, 255,
  255, 128, 0,
  255, 128, 128,
  255, 128, 255,

  0, 0, 128,
  0, 255, 128,
  255, 0, 128,
  255, 255, 128
};
//*************************************

void printaLed(int Red, int Green, int Blue) {
  analogWrite(Rout, Red);
  analogWrite(Gout, Green);
  analogWrite(Bout, Blue);
}

void setup() {
  pinMode(Rout, OUTPUT);
  pinMode(Gout, OUTPUT);
  pinMode(Bout, OUTPUT);
  pinMode(Led, OUTPUT);
  pinMode(Palmain, INPUT);
  Serial.begin(9600);
}

void loop() {
  printaLed(R, G, B);
  Serial.println("debuger 0");
  palma = digitalRead(Palmain);
  Serial.println(palma);
  delay(10000);
  // *************COMECO DA DETECCAO DE PALMA****************
  do {
    palma = digitalRead(Palmain);
  } while (!palma);
  Serial.println("debuger 1");
  if (!palma) { //detecta comeco do sinal sonoro
    Serial.println("debuger 2");
    duracao = 0;
    while (!palma) { // mede a duracao do sinal sonoro : duracao(ms)
      palma = digitalRead(Palmain);
      delay(1);
      duracao++;
    }
    Serial.println("debuger 3");
    if (duracao < 200) { // se o sinal sonoro durar menos que 200ms, é a primeira palma
      Serial.println("debuger 4");
      while (i < 700 && palma) { // procura a segunda palma por 700ms
        palma = digitalRead(Palmain);
        delay(1);
        i++;
      }
      Serial.println("debuger 5");
      if (!palma) { // se detectou palma nos 200ms
        Serial.println("debuger 6");
        duracao = 0;
        while (!palma) { // detecta duracao da palma
          palma = digitalRead(Palmain);
          delay(1);
          duracao++;
        }
        Serial.println("debuger 7");
        if (duracao < 200) // se a palma durar menos de 200ms é a segunda plama
          mudanca = 1;
        else
          mudanca = 0;
        Serial.println("debuger 8");
      }
    }
  }
  // *************FINAL DA DETECCAO DE PALMA****************
  Serial.println("debuger 9");
  // *************INICIO DA TROCA DE COR*********************
  if (mudanca) {
    Serial.println("debuger 10");
    digitalWrite(Led, HIGH);
    //if (atual++ > 27) atual = 0;  // trocar em ordem
    atual = random(1, 28);  // cores randomicas
    R = cores[atual][0];
    G = cores[atual][1];
    B = cores[atual][2];
    printaLed(R, G, B);
    delay(200);
    mudanca = 0;
  }
  else {
    Serial.println("debuger 11");
    digitalWrite(Led, LOW);
  }
  //***************FINAL DA TROCA DE COR************* 
  digitalWrite(Led, LOW);
  delay(500);
  
  Serial.println("debuger final");
  Serial.println(mudanca);

  /*
    Serial.print("R: ");
    Serial.print(R);
    Serial.print(" G: ");
    Serial.print(G);
    Serial.print(" B: ");
    Serial.println(B);
  */
}

