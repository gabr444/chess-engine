let pieces = {'p': 'wp', 'r': 'wr', 'b': 'wb', 'n': 'wn', 'k': 'wk', 'q': 'wq', 'P': 'bp', 'R': 'br', 'B': 'bb', 'N': 'bn', 'K': 'bk', 'Q': 'bq'};

function parseInput()
{
    board = "rnbqkbnr................................................RNBQKBNR";
    let pos = document.getElementsByClassName('image');
    for(let i=0;i<pos.length;i++)
    {
        if(board[i] != '.')
        {
            pos[i].innerHTML = "<img src='media/"+pieces[board[i]]+".png'>";
        }
        else
        {
            pos[i].innerHTML = "";
        }
    }
}

function hightlightMoves(moves)
{
    let box = document.getElementsByClassName('box');
    for(let i=0;i<moves.length;i++)
    {
        box[moves[i][0]*7+moves[i][1]].style.background = "rgb(255, 255, 255);";
    }
}

$(document).ready(function()
{
	$('form').on('submit', function(event)
  {
		$.ajax
    ({
      data : {
				response : $('#msg').val()
			},
			type : 'POST',
			url : '/process'
		})
		.done(function(data)
    {
      let botMsg = '<div class="box-bot"><div class="msg-bot">'+data.response+'</div></div>';
		  $('#chat').append(botMsg);
      // Clear the input input box
      document.getElementById('msg').value="";
		});

		event.preventDefault();

	});

});
