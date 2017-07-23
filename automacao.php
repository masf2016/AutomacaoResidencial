<html>
<head>
	<title></title>
<link rel=”stylesheet” type=”text/css” href=”estilo.css” />
  <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.7.1/jquery.min.js"></script>

<style type="text/css">
<

.form1{
border-style: solid;
border-color: #CDAD00;
background-color: #FFD700;
width: 20%;
margin-bottom: 10px;


}
.form1 {
	font-family: Georgia, "Times New Roman", Times, serif;
	font-size: 14px;
	font-style: normal;
	line-height: normal;
	font-weight: normal;
	font-variant: normal;
	text-transform: uppercase;
	color: #000;
	background-color: #0CC;
	letter-spacing: normal;
	text-align: left;
	vertical-align: baseline;
	word-spacing: normal;
	border-top-style: solid;
	border-right-style: solid;
	border-bottom-style: solid;
	border-left-style: solid;
	position: absolute;
	height: 350px;
	width: 240px;
	left: 538px;
	top: 147px;
}
.texto {
	text-align:center;
	font-size: 36px;
	font-style: normal;
  position: 900px;
}
</style>

    <script type="text/javascript">
        function habilitaBtn () {
            var op = document.getElementById("valor5").value;

            if(op == "o")
            {
                if(!document.getElementById('valor1').disabled) document.getElementById('valor1').disabled=true;
                if(!document.getElementById('valor2').disabled) document.getElementById('valor2').disabled=true;
                if(!document.getElementById('valor3').disabled) document.getElementById('valor3').disabled=true;
                if(!document.getElementById('valor4').disabled) document.getElementById('valor4').disabled=true;              
            }

            else if(op == "f")
            {
                if(document.getElementById('valor1').disabled) document.getElementById('valor1').disabled=false;
                if(document.getElementById('valor2').disabled) document.getElementById('valor2').disabled=false;
                if(document.getElementById('valor3').disabled) document.getElementById('valor3').disabled=false;
                if(document.getElementById('valor4').disabled) document.getElementById('valor4').disabled=false;
            }
        }
    </script>

  <script type="text/javascript">
  jQuery(document).ready(function(){
    jQuery('#form1').submit(function(){
      var dados = jQuery( this ).serialize();
 
      jQuery.ajax({
        type: "POST",
        url: "porta_3.php",
        data: dados,
        success: function( data )
        {
         alert( data );
       }
     
      });
      
      return false;
    });
  });
  </script>


</head>
<body>
  <?php

//**
//** trecho para recebe dados vindo do Arduino via porta serial 

//while (true) { // Loop infinto, para  a leitura no Serial Monitor

  ?>
<p class="texto"> Automação Residencial </p>


  <?php
  
 // $bytes = fread($fp, 1024); // Le uma linha da conexão, até 1024 bytes
 // if (strlen($bytes) > 0) { // Se o Arduino enviou algo ...
 //   echo $bytes; // Imprime
 // }
 //}

  ?>
	
<form method="post" action="#" id="form1" class="form1">

 

<table width="200" border="0" cellspacing="3">
  <tr>
    <td><label>FRENTE</label></td>
    <td>

        <select name="valor1" id="valor1">
      <option value=1>DESLIGAR</option>
      <option value=2>LIGAR</option>
    </select>

    </td>
  </tr>
  <tr>
    <td> <label>SALA</label></td>
    <td>

        <select name="valor2" id="valor2">
      <option value=3 color="red">DESLIGAR</option>
      <option value=4>LIGAR</option>
    </select>
      </td>
  </tr>
  <tr>
    <td><label>QUARTO</label></td>
    <td> 
 
    <select name="valor3" id="valor3">
      <option value=5>DESLIGAR</option>
      <option value=6>LIGAR</option>
    </select>

     </td>
  </tr>
  <tr>
    <td><label>BANHEIRO</label></td>
    <td> 
     
    <select name="valor4" id="valor4">
      <option value=7>DESLIGAR</option>
      <option value=8>LIGAR</option>
      </select>

     </td>
  </tr>
  <tr>
    <td><label>SENSOR LUMINOSIDADE</label></td>
    <td>    
    <select name="valor5" onchange="habilitaBtn()" id="valor5">
      <option value='f'>DESLIGAR</option>
      <option value='o'>LIGAR</option>
      </select>
      </td>
  </tr>

  <tr>
    <td colspan="2"><center><input type="submit" value="enviar"> </center></td>
  </tr>
</table>

</form>

</body>
</html>