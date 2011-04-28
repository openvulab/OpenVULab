$(document).ready(function() {
	$.ajax({
  			type: "POST",
   			url: "manage.php?where=survey_tool&lay=ajax&where_context=pre_existing&newid=<?php echo($project->pre_survey['id']);?>",
   			data: postdata,
   			success: function(html){
   			 	$('#surveytool').empty();
				$('#surveytool').attr('innerHTML',html);
				$('#surveytool').fadeIn('fast');
			}
   		});
   	$("#pre_existing").attr("checked",true);
});