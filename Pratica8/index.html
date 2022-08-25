<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Arduino connectivity test</title>

    <!-- Bootstrap -->
    <!-- Latest compiled and minified CSS -->
    <link rel="stylesheet" href="https://netdna.bootstrapcdn.com/bootstrap/3.1.1/css/bootstrap.min.css">

    <!-- Optional theme -->
    <link rel="stylesheet" href="https://netdna.bootstrapcdn.com/bootstrap/3.1.1/css/bootstrap-theme.min.css">

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
      <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>
  <body>
    <div class="container">
        <h1>johnny-five test</h1>
    <div class="row">
      <div class="col-md-12">
      <h4>LED piscante verde</h4>
      <div class="btn-group" data-toggle="buttons">
        <input id="ledBlinking" type="range" min="0" max="1024" step="1"/>
      </div>
      <h4>LED intensidade vermelho</h4>
      <div class="btn-group" data-toggle="buttons">
        <input id="ledIntensity" type="range" min="0" max="1024" step="1"/>
      </div>
      </div>
    </div>
    </div>
    <!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.0/jquery.min.js"></script>
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script src="https://netdna.bootstrapcdn.com/bootstrap/3.1.1/js/bootstrap.min.js"></script>
    <script src="/socket.io/socket.io.js"></script>
    <script>

      var socket = io.connect('http://localhost:8000/');

      socket.on('news', function (data) {
        console.log(data);
      });

      $('#ledBlinking').on('input', function(){
        var tmp = parseInt($('#ledBlinking').val(), 10);
        console.log("Setting LED Delay:", tmp)
        socket.emit('ledBlinking', {led_slider: tmp});
      });

      $('#ledIntensity').on('input', function(){
        var tmp = parseInt($('#ledIntensity').val(), 10);
        console.log("Setting LED Delay:", tmp)
        socket.emit('ledIntensity', {led_slider: tmp});
      });

    </script>
    </body>
</html>
