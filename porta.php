

<?php

ini_set('display_errors', 0 ); // omite erro exibidos pelo servidor
error_reporting(0);

//$r = shell_exec('type COMx');
//echo " =".$r."=</br>";

// Define porta onde arduino está conectado
//$port = "COM1";
$port = "COM3";
//$port = "COM121";
  
// Configura velocidade de comunicação com a porta serial
exec("MODE $port BAUD=9600 PARITY=n DATA=8 XON=on STOP=1");





  
// Inicia comunicação serial
$fp = fopen($port, "w+");

if(!$fp) 
{
   echo "Nao foi possivel abrir conexão com a porta ". $port ."!";
	}
	else 
	{
				 $id1 = $_POST["valor1"];
				 $id2 = $_POST["valor2"];
				 $id3 = $_POST["valor3"];
				 $id4 = $_POST["valor4"];
				 $id5 = $_POST["valor5"];			   


				//**
				//** trecho para recebe dados vindo do Arduino via porta serial 

				/*
				while (true) { // Loop infinto, para  a leitura no Serial Monitor
				  $bytes = fread($fp, 1024); // Le uma linha da conexão, até 1024 bytes
				  if (strlen($bytes) > 0) { // Se o Arduino enviou algo ...
				    echo $bytes; // Imprime
				  }
				}
				*/  

				// Escreve na porta
				//fwrite($fp,'1');
				fwrite($fp,$id1);
				fwrite($fp,$id2);
				fwrite($fp,$id3);
				fwrite($fp,$id4);
				fwrite($fp,$id5);

				//fwrite($fp,'7');
				//fwrite($fp,$id);
				//fwrite($fp,"LED7:0");
				 sleep(1);
				  $bytes = fread($fp, 1024); // Le uma linha da conexão, até 1024 bytes
				  if (strlen($bytes) > 0) { // Se o Arduino enviou algo ...
				    echo $bytes; // Imprime
				}

				// Fecha a comunicação serial
				fclose($fp);
				//header("Location: automacao.php");
}

?>