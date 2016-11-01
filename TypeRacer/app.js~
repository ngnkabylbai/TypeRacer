$(document).ready(function(){
	var a = $('#header')[0];
	var b = $('a');
	b.click(function(event){
		$(this).addClass('bold');
		event.preventDefault();
	});

	var winner = $('#winner');
	winner.hide();
	
	var pText = $('p').text();

	var currTextChar = 0;
	var currInputChar = 0;
-
	$('input').keypress(function(event){
		

		var code = event.keyCode;
		console.log(code);

		var right = "false";

		if(code == 0)
			currInputChar++;


		if(code == 8) {
			if(currTextChar == currInputChar && currTextChar != 0) {
				currInputChar--;
				currTextChar--;
			} else {
				if(currInputChar > 0)
					currInputChar--;
			}
		}

		if(code == 0 && currInputChar-1 == currTextChar){

			var current = String.fromCharCode(event.which);
			var t = pText[currInputChar-1];

			if(t == current){
				$('input').css("border-color","green");

				currTextChar++;
				right = "true";
				console.log('ok');

			} else {
				$('input').css("border-color","red");
				current = "false";
				console.log(t + ' ' + 'curent' + currTextChar + ' ' + currInputChar);
				console.log('incorrect');
			}

			if(pText.length == currInputChar && right == "true"){
				winner.show('slow');
				console.log('You are the winner!');
			}
		}	
		console.log(currTextChar + ' ' + currInputChar + ' ' +right);

	});
});

