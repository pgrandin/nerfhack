<!DOCTYPE html>
<html>
    <head>
        <title>Nerf Hack</title>
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <!-- Bootstrap -->
        <link href="bootstrap/css/bootstrap.css" rel="stylesheet">
        <link rel="stylesheet" href="bootstrap/css/main.css">
        <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media
           queries -->
        <!-- WARNING: Respond.js doesn't work if you view the page
           via file:// -->
        <!--[if lt IE 9]>
           <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/
              html5shiv.js"></script>
           <script src="https://oss.maxcdn.com/libs/respond.js/1.3.0/
              respond.min.js"></script>
        <![endif]-->
        <style>
            @font-face{
                font-family:"digital-7";
                src: url(bootstrap/fonts/digital-7/digital-7-mono.ttf) format("truetype");
            }
        </style>
        
    </head>
    <body>
        <div class="navbar navbar-inverse navbar-fixed-top">
            <div class="navbar-inner">
                <div class="container">
                    <div class="nav-collapse collapse">
                        <ul class="nav">
                            <li class="active"><a href="main.php">New Game</a></li>
                            <li class="active"><a href="list.php">List</a></li>
                        </ul>
                    </div><!--/.nav-collapse -->
                </div>
            </div>
        </div>
        <div class="logo-container">
            <img src="bootstrap/img/logo.png" alt="Logo" height="22">
        </div>
        <div class="start-button-container">
            <a href="#" class="create-players">
                <img src="bootstrap/img/start_button.png" alt="Start">
            </a>
        </div>

        <div class="players-list" style='display: none;'>
            <div>
                <span id='player1-name' class='names'> Chintan </span>
                <span id='player1-score' class='numbers'> 00 </span>

            </div>
            <div>
                <span id='player2-name' class='names'> Tony </span>
                <span id='player2-score' class='numbers'> 00 </span>

            </div>
        </div>

        <div class="modal hide fade" id ="myModal">
            <div class="modal-dialog">
                <div class="modal-content">
                    <div class="modal-header">
                        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">X</button>
                        <h4 class="modal-title">Enter Player's Name</h4>
                    </div>
                    <div class='player-container'>
                        <div class='mode'>
                            <label class="radio">
                                <input type="radio" name="optionsRadios" id="single" value="single" checked>
                                Single Player Mode
                            </label>
                            <label class="radio">
                                <input type="radio" name="optionsRadios" id="double" value="double">
                                Double Player Mode
                            </label>
                            <div>
                                <div class="control-group">
                                    <label class="control-label" for="inputEmail">Player 1</label>

                                    <input type="text" id="player1" placeholder="Player 1 Name">

                                </div>
                                <div class="control-group">
                                    <label class="control-label" for="inputPassword">Player 2</label>
                                    <div class="controls">
                                        <input type="text" id="player2" placeholder="Player 2 Name">
                                    </div>
                                </div>
                            </div>
                            <div class="modal-footer">
                                <button class="btn" data-dismiss="modal" aria-hidden="true">Close</button>
                                <button class="btn btn-primary save-players">Begin!</button>
                            </div>
                        </div>
                    </div>
                </div>

                <!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
                <script src="https://code.jquery.com/jquery.js"></script>
                <!-- Include all compiled plugins (below), or include individual files as needed -->
                <script src="bootstrap/js/bootstrap.js"></script>
                <script src="bootstrap/js/main.js"></script>
                </body>
                </html>