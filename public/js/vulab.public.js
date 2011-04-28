$(document).ready(function() {
	$('.thankbody,.returnlink').hide();
	$('#submitVID input[type="submit"]').click(function() {
		var vid = $('#submitVID input[name="vid"]').attr('value');
		var rid = $('#submitVID input[name="rid"]').attr('value');
		$('#submitVID').fadeOut('fast');
		 $.ajax({
   			type: "POST",
		    url: "mod.response.php",
			data: "vid="+vid+"&rid="+rid,
			success: function(msg){
				$('#submitVID').html(msg);
				$('#submitVID').fadeIn();
				$('.thankbody,.returnlink').fadeIn();
	   		}
		 });
	});
});