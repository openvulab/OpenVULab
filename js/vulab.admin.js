/*
File: 		vulab.admin.js \\v 1.0
Info:		- handle all /admin js functionality
Author: 	Blake Edwards
Email:		electBlake@gmail.com

License: 	http://source.fluidproject.org/svn/fluid/components/trunk/LICENSE.txt
*/



$(document).ready(function(){
	//jquery curvy corners
	  $(function(){
			
			
			$('.c').corner();
			$('.contents').corner({
			  tl: { radius: 12 },
			  tr: { radius: 12 },
			  bl: { radius: 12 },
			  br: { radius: 12 }});
			$('.c2').corner({
			  tl: { radius: 32 },
			  tr: { radius: 16 },
			  bl: { radius: 16 },
			  br: { radius: 16 },
			  antiAlias: true,
			  autoPad: false,
			  validTags: ["div"] });
			$('.c3').corner({
			  tl: { radius: 16 },
			  tr: false,
			  bl: false,
			  br: { radius: 16 },
			  antiAlias: true,
			  autoPad: true,
			  validTags: ["div"] });
			  
	});	

	$('.isolatetoggle').click(function(){
		$('.isolatetoggle').each (function(i) {
			var id = $(this).attr('id');
			$('.'+id).fadeOut('fast');
		});	
		var id = $(this).attr('id');
		$('.'+id).fadeIn('def');
		
	});

	$("#pre_none").click(function() {
		$('#surveytool').fadeOut('fast');
		$('#surveytitle').fadeOut('fast');
		$('#copysurvey').fadeOut('fast');
	});
	$("#post_none").click(function() {
		$('#surveytool').fadeOut('fast');
		$('#surveytitle').fadeOut('fast');
		$('#copysurvey').fadeOut('fast');
	});
	$("#pre_new").click(function() {
		$('#copysurvey').fadeOut('fast');
		$('#surveytool').fadeOut('fast');
		$('#surveytitle').fadeOut('fast');
		$('iframe#surveytool').attr('src','manage.php?where=survey_tool&lay=form&new=true');
		$('#surveytool').fadeIn('fast');
		
	});

	$("#post_new").click(function() {
		$('#copysurvey').fadeOut('fast');
		$('#surveytool').fadeOut('fast');
		$('#surveytitle').fadeOut('fast');
		$('iframe#surveytool').attr('src','manage.php?where=survey_tool&lay=form&new=true');
		$('#surveytool').fadeIn('fast');
	});
	$("#pre_copy").click(function() {
		$('#surveytool').fadeOut('fast');
		$('#copysurvey').fadeIn('fast');
	});
	$("#post_copy").click(function() {
		$('#surveytool').fadeOut('fast');
		$('#surveytitle').fadeOut('fast');
		$('#surveynote').fadeOut('fast');
		$('#copysurvey').fadeIn('fast');
	});
	$('#copysurvey option').click(function(){	
		
		var thisval = $(this).attr('value');
		$('#surveytool').fadeOut('fast');
		$('iframe#surveytool').attr('src','manage.php?where=survey_tool&lay=form&fromID='+thisval+'&new=true&makenew=true');
		$('#surveytool').fadeIn('fast');
	});

	
	$("#debug_toggle").click(function(){
		if ($(this).html() == 'minimize debug') {
			$(this).html('expand debug');
			$('.debug').slideUp();
			return;
		}
		if ($(this).html() == 'expand debug') {
			$(this).html('minimize debug');
			$('.debug').slideDown();
			return;
		}
	});
	
	$("#log_toggle").click(function(){
		if ($(this).html() == 'minimize log') {
			$(this).html('expand log');
			$('.log').slideUp();
			return;
		}
		if ($(this).html() == 'expand log') {
			$(this).html('minimize log');
			$('.log').slideDown();
			return;
		}
	});

	$('.noneWarning').click(function() {
	
	});
	
	//Utility for Checkboxes in Filters
	$('a[href="#checkall"]').click(function() {
		var keyClass = $(this).attr('class');
		$('input[type=checkbox]').each( function() {
			if ($(this).hasClass(keyClass)) {
//			console.log('check');
				$(this).attr('checked','checked');
			}
		});
	});
	$('a[href="#checknone"]').click(function() {
		$('input[type=checkbox]').each( function() {
		var keyClass = $(this).attr('class');
			if ($(this).hasClass(keyClass)) {
//			console.log('uncheck');
				$(this).attr('checked','');
			}
		});
	});
	
// Project JS
	$('a[href="#save"]').click(function() {
		$('input[name="go"]').attr('value',$('input[name="from"]').attr('value'));
		document.containerform.submit();
	});
	
	$('.hrefmodal').click(function() {	
		$.showAkModal('http://google.com',$(this).attr('alt'),230,170);
	});
});

function addLog(line) {
	if ($('.log')) { $('.log').append(line+"<br/>"); }
}
