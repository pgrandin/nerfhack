$(document).ready(function() {

    $('#game-start-audio').get(0).play();

    newGameId = 0;
    var player1, player2, mode, myTimeout;

    $(".save-players").on('click', function() {
        player1 = $('#player1').val();
        player2 = $('#player2').val();
        mode = $('input[name=mode]:checked').val();
        console.log('Player 1 Name: ' + player1);
        console.log('Player 2 Name: ' + player2);
        console.log('Mode: ' + mode);
        if (!player1 || (mode === 'double' && !player2)) {
            alert('Player name is missing');
            return;
        }

        var APIurl = "http://192.168.162.136/api/create/" + mode + '/' + player1;

        if (mode === 'double')
            APIurl += '/' + player2;

        $.ajax({
            url: APIurl,
            type: "GET",
            success: function(response) {
                newGameId = response.id;
                console.log('New Game Id = ' + newGameId);
                setPlayerNames();
            }
        });
        //setPlayerNames();
        $('#myModal').modal('hide');
    });

    $(".create-players").on('click', function() {
        $('#myModal').modal({
            show: true,
            refresh: true,
        });
    });

    /*Show/hide player two*/
    $('input[name=mode]').on('change', function() {
        var radioValue = $('input[name=mode]:checked').val();
        if (radioValue === 'double') {
            $('.control-group.double').show();
        } else {
            $('.control-group.double').hide();
        }
    });

    setPlayerNames = function() {
        console.log('Calling setPlayerNames');
        $('#player1-score').html('00');
        $('#player1-name').html(player1);

        if (mode === 'double') {
            $('#player2-score').html('00');
            $('#player2-name').html(player2);
        }
        $('.start-button-container').hide();
        $('.players-list').show();
        updateScore();
    }

    updateScore = function() {
        console.log('Calling updateScore');
        $.ajax({
            url: "http://192.168.162.136/api/game/" + newGameId,
            type: "GET",
            success: function(response) {
                /**
                 * "Id": 1,
                 "Player1": "p1",
                 "Player2": "p2",
                 "Score1": 0,
                 "Score2": 0
                 */
                console.log('Player 1 Score : ' + response.Score1);
                var player1Score = (typeof response.Score1 === 'undefined') ? 0 : response.Score1;
                console.log('updated Player 1 Score : ' + player1Score);
                $('#player1-score').html(("0" + player1Score).slice(-2));
                
                if (mode === 'double') {
                    if (player1Score >= 16) {
                        winningMessage(1);
                        clearTimeout(myTimeout);
                        return;
                    }

                    console.log('Player 2 Score : ' + response.Score2);
                    var player2Score = (typeof response.Score2 === 'undefined') ? 0 : response.Score2;
                    console.log('Updated Player 2 Score : ' + player2Score);
                    $('#player2-score').html(("0" + player2Score).slice(-2));
                                        
                    if (player2Score >= 16) {
                        winningMessage(2);
                        clearTimeout(myTimeout);
                        return;
                    }
                } else if(mode === 'single' && player1Score == 32){
                    winningMessage(1);
                    clearTimeout(myTimeout);
                    return;
                }

            }
        });
        
        myTimeout = setTimeout(updateScore, 2000);
    }

    winningMessage = function(playerNumber) {
        console.log('Calling winningMessage');
        $('#winning-audio').get(0).play();
        $(".player-dashboard").not('.player-' + playerNumber).hide();
        $('.winning-trophy').show();
    }

    playAudioAgain = function() {
        console.log('Calling playAudioAgain');
        $('#game-start-audio').get(0).play();
    }
});



