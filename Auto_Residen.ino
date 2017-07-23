    /* 
    ** FACOL - 3º Periodo de Sistemas de Informação - Arquitetura de Software
    ** Projeto de Automação Residencial
    ** Data: 16/12/2014
    **
    ** Equipe:
    *** Mario Antonio 
    *** Raquel Monteiro
    *** Rafaella Costa
    *** Sandro Silva 
    *** Wilson José
    **
    ** Descrição:
    ** Codigo para controle remoto via pagina web de 4 lampadas em uma residencia, este modelo usa:
    ** um arduino Uno, um display LCD 16x2, um sensor LDR, um ponteciometro de 10 k,
    ** 4 LEDs de 5mm, 4 resistores de 100 ohm, 1 resistor de 10 k ohm
    ** nota: uma das lampadas será chaveada para ser ativada pelo sensor de luminosidade
    */ 


 
    #include <LiquidCrystal.h> // biblioteca para uso do dispositivo LCD

    //
    //Parametros das variáveis usadas pelos LEDs e sensor LDR
    //

    int LuzFora = 6;           //setar a variável com o pino de número correspondente (pino 6)
    int LuzSala = 7;           //setar a variável com o pino de número correspondente (pino 7)
    int LuzQt1  = 8;           //setar a variável com o pino de número correspondente (pino 8)
    int LuzQt2  = 9;           //setar a variável com o pino de número correspondente (pino 9)
    int LuzTeste = 10;         // luz usada para teste , não será usada no projeto final
    int SensorLuzLDR = 0;      //inicialização da variável que receberá o valor do sensor LDR
    int valorLuminosidade = 0; //variavel para teste de saida de dados no monitor serial
    
    //
    // parametros das variaveis usadas pelo LCD
    //

    LiquidCrystal lcd(12, 11, 5, 4, 3, 2);                                            //inicializa o lcd com os numeros dos pinos do Arduino onde faz conexão
    String linha1 = "Automacao Residencial - FACOL 2014.2 - Arquitetura de Software"; // texto inicial apresentado 
    String linha2 = "";
    int stringInicio, stringParada = 0;                                               // variaveis para marcação de inicio  e parada do cursor 
    int scrollCursor = 16;                                                            //tamanho de caracterer diponiveis no LCD a ser informada para a função de controle do 'rolar' do texto  
    int tamanho =0;                                                                   // variavel a ser usada para receber o tamanho da medida da string contida na variavel 'linha1'
    
    //
    //configuração inicial dos elementos no projeto
    //

    void setup()
    {
      
        lcd.begin(16, 2);          // seta o numero de colunas e linhas usadas no lcd

    
        
        Serial.begin(9600);        //inicializar a porta serial com uma taxa de 9,6kbps
        pinMode(LuzFora, OUTPUT);  // Define o pino (6) como pino de saída de sinal
        pinMode(LuzSala, OUTPUT);  // Define o pino (7) como pino de saída de sinal
        pinMode(LuzQt1, OUTPUT);   // Define o pino (8) como pino de saída de sinal
        pinMode(LuzQt2, OUTPUT);   // Define o pino (9) como pino de saída de sinal
        pinMode(LuzTeste, OUTPUT); // Define o pino (9) como pino de saída de sinal
       
        digitalWrite(LuzFora,HIGH);     //Define incialmente um sinal de nível lógico 1 para o pino 6
        digitalWrite(LuzSala,HIGH);     //Define incialmente um sinal de nível lógico 1 para o pino 7
        digitalWrite(LuzQt1,HIGH);      //Define incialmente um sinal de nível lógico 1 para o pino 8
        digitalWrite(LuzQt2,HIGH);      //Define incialmente um sinal de nível lógico 1 para o pino 9
        digitalWrite(LuzTeste,HIGH);    //Define incialmente um sinal de nível lógico 1 para o pino 10
         
    }

    //
    //bloco de execução efetiva do projeto (todo o código dentro do escopo está em um loop infinito)
    //

    void loop()
    {
        
              lcd.setCursor(scrollCursor,0);                            // seta o cursor do LCD na posição da coluna informada pela variavel 'scrollCursor' e a posição da linha
              lcd.print(linha1.substring(stringInicio,stringParada));   // imprime no LCD na posicao dada acima 
              lcd.setCursor(0, 1);                                      // seta o cursor do LCD na posição da coluna 1, linha 2
              lcd.print(linha2);                                        // imprime o conteudo de linha2 no LCD na posição dada acima
              delay(250);                                               // atraso de 250 ns
              scroll_sup();                                             // chama a função que executa o scroll 
              
              //
              //Verifica o tamanho da string
              //  
              tamanho = linha1.length();      // passa o tamanho para a variavel

                if (stringInicio == tamanho)  // se valor de 'stringInicio' for igual ao tamanho da string, 
                {                             // valores de 'stringInicio' e 'stringParada' são reinicializados
                  stringInicio = 0;  
                  stringParada = 0;  
                }  
                
              
      
          if (Serial.available()){                      //verifica se a entrada serial está disponível

                char caracterSer = Serial.read();       //lê o byte recebido da entrada serial
                 //
                 //Trecho responsável pelo chaveamento dos LEDs, dependendo dos valores repassados pela porta serial pode alteral o nível lógico do pino de 
                 //1 (ativando o pino) ou 0 (desliga o pino de saída).
                 //Para cada condição IF resulta também em uma mensagem no LCD, seguida de um pequeno atraso de 700 ns para que a mensagem seja visualizada 
                 //pelo usuario. Esse atraso é necessario, pois a rotina 'scroll_sup()' limpa a tela do LCD a cada interação do 'void loop()'
                
                if (caracterSer == 'o')
                {
                  lcd.clear();                        //limpa a tela do LCD
                  lcd.setCursor(0,1);
                  lcd.print("Sensor Ligado!");
                  delay(700);
                  
                sensorLuz(caracterSer);               // chamada da função do sensor de luminosidade, passado como parametro o valor que veio da porta serial 
                
                  lcd.clear();
                  lcd.setCursor(0,1);
                  lcd.print("Sensor Desligado!");
                  Serial.write("Sensor Desligado!");
                  delay(700);
                }
                              
                if (caracterSer == '1')
                {
                  digitalWrite(LuzFora, LOW);       // nível lógico vai para 0 (desliga o pino de saída)
                  lcd.clear();
                  lcd.setCursor(0,1);
                  lcd.print("Luz Exter.-> OFF");
                  delay(700);
                }
                if (caracterSer == '2')
                {
                  digitalWrite(LuzFora, HIGH);      // nível lógico vai para 1 (liga o pino de saída)
                  lcd.clear();
                  lcd.setCursor(0,1);
                  lcd.print("Luz Exter.-> ON");
                  delay(700);
                }
                
                if (caracterSer == '3')
                {
                  digitalWrite(LuzSala, LOW);
                  lcd.clear();
                  lcd.setCursor(0,1);
                  lcd.print("Luz Sala.-> OFF");
                  delay(700);
                }
                if (caracterSer == '4')
                {
                  digitalWrite(LuzSala, HIGH);
                  lcd.clear();
                  lcd.setCursor(0,1);
                  lcd.print("Luz Sala.-> ON");
                  delay(700);
                }
                if (caracterSer == '5')
                {
                  digitalWrite(LuzQt1, LOW);
                  lcd.clear();
                  lcd.setCursor(0,1);
                  lcd.print("Luz Quart.-> OFF");
                  delay(700);
                }
                if (caracterSer == '6')
                {
                  digitalWrite(LuzQt1, HIGH);
                  lcd.clear();
                  lcd.setCursor(0,1);
                  lcd.print("Luz Quart.-> ON");
                  delay(700);
                }
                if (caracterSer == '7')
                {
                  digitalWrite(LuzQt2, LOW);
                  lcd.clear();
                  lcd.setCursor(0,1);
                  lcd.print("Luz Quart.-> OFF");
                  delay(700);
                }
                if (caracterSer == '8')
                {
                  digitalWrite(LuzQt2, HIGH);
                  lcd.clear();
                  lcd.setCursor(0,1);
                  lcd.print("Luz Quart.-> ON");
                  delay(700);
                }

                // TESTE
                // lampada para teste
                if (caracterSer == '9')
                {
                  digitalWrite(LuzTeste, LOW);
                }
                if (caracterSer == '0')
                {
                  digitalWrite(LuzTeste, HIGH);
                }
                 
          }


      }
      
      void sensorLuz(char escolha)
      {        
              //
              // alerta visual para indicar o inicio da atividade do sensor LDR
              // piscará 10 vezes durante intervalos de 50 ns
              //

             for(int i = 0; i < 10; i++)  
             {
               digitalWrite(LuzFora,HIGH);
               delay(10);
                                           
               digitalWrite(LuzFora,LOW);
               delay(50);
             }

          while(escolha == 'o')                                   // enquanto variavel escolha contiver 'o' o laço continua
          {
                          // informa no LCD o fluxo luminoso recebido pel sensor LDR convertido em 'LUX'
                          lcd.clear();
                          lcd.setCursor(0,0);
                          lcd.print("Luminos. Ambiente:");
                          lcd.setCursor(0,1);
                          lcd.print(int(Light(analogRead(0))));         //imprime no LCD o retorno do valor truncado do sensor LDR repassado para a função 'Light()'
                          lcd.setCursor(4,1);
                          lcd.print(" Lux");
 
                          // TESTE
                          // imforma no serial monitor os dados do sensor LDR
                          valorLuminosidade = analogRead(SensorLuzLDR);
                          Serial.print(" Leitura do sensor LDR: ");
                          Serial.print(valorLuminosidade);
                        /*  Serial.print(" Lux: ");
                          Serial.println(int(Light(analogRead(0)))); // Converte em LUX o valor informado pelo sensor LDR
                          
                        */                            //
                                                      // condição de teste para ativação do led dependendo da luminosidade ambiente
                                                      //  
                                                      if (valorLuminosidade < 400)        // se o valor informado pelo LDR for menor que 400
                                                      { 

                                                             digitalWrite(LuzFora, HIGH); // led vai para 1             
    
                                                      } 
                                                      else
                                                      { 
                                                            digitalWrite(LuzFora, LOW);   // senão 0
              
                                                      } 
           
                                                      delay(1000);                        //atraso de 1 s no laço
                                                 
                                                          switch (Serial.read())          // lê a porta serial, esperando pelo valor 'f' que encerra a atividade do sensor LDR
                                                            {
                                                                case 'f' :
                                                                    Serial.println("Encerramento do sensor LDR!");
                                                                    escolha = Serial.read();
                                                                    break;

                                                            }

                    

                          // TESTE
                          // informa no serial monitor o valor da variavel escolha
                          Serial.print(" valor de 'escolha': ");
                          Serial.print(escolha);
                          Serial.println(""); 
                    }
       }

                            //
                            //função para converter os valores informados do sensor LDR em 'Lux'
                            //

                            double Light (int RawADC0){
                        
                            double Vout=RawADC0*0.0048828125; // repassa para variavel Vout a divisão entre o valor do LDR e a razão 
                                                              // entre a voltagem do pino A0 com 1024, valor maximo do LDR no pino digital
                            int lux=500/(10*((5-Vout)/Vout)); //use this equation if the LDR is in the upper part of the divider
                            //int lux=(500*(5-Vout))/(10*Vout);
                            
                            //int lux=(2500/Vout-500)/10;
                        
                            return 10*lux;
                            }

          void scroll_sup()   // funçao de rolagem da linha superior do LCD 16x2
          {  
            lcd.clear();      //limpa a tela
              if(stringInicio == 0 && scrollCursor > 0)   // se 'stringInicio' estiver na posição 0 da coluna e a poisção de 'scrollCursor' for maior que 0
              {  
                scrollCursor--;                           //decrementa uma posição de 'scrollCursor'
                stringParada++;                           //incrementa uma posição de 'stringParada'
              } else if (stringInicio == stringParada){  
                stringInicio = stringParada = 0;  
                scrollCursor = 16;  
                      } else if (stringParada == linha1.length() && scrollCursor == 0) {  
                        stringInicio++;  
                                } else {  
                                  stringInicio++;  
                                  stringParada++;  
                                }  
                                

          }  
