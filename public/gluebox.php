<?php
/*
###################################################################
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
###################################################################
*/

/* $Id: survey.php,v 1.21 2007/07/09 12:58:21 liedekef Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

// Matthew Gregg
// <greggmc at musc.edu>

	require_once('../admin/include_all.php');
	require_once("./phpESP.first.php");	
	
	# error_reporting(E_ALL);
	//error_reporting(E_ALL);
  //ini_set('display_errors', '1');
	if (isset($_GET['ps']))
	{
		$sql = "SELECT * FROM `survey` WHERE `name` = '$_GET[ps]'";
		echo $sql;
		
		$result = execute_sql($sql);
		$sid = $result->fields[0];
		$sql = "SELECT * FROM `project` WHERE `presurvey` = $sid AND `action_url` = '$_GET[pid]'";
		echo $sql;
		
		$result = execute_sql($sql);
		$pid = $result->fields[0];
		$_GET['project'] = $pid;
	}
	if (isset($_GET['project'])) {
		$_id = _addslashes($_GET['project']);
		$project = new Project;
		$project->init($_id);
		unset($_GET['project']);
		$_SERVER['QUERY_STRING'] = ereg_replace('(^|&)project=[^&]*&?', '', $_SERVER['QUERY_STRING']);
	}
    	if (isset($_POST['project'])) {
        	$_id = _addslashes($_POST['project']);
        	unset($_POST['project']);
    	}

	if (!empty($_id)) {
        	$_sql = "SELECT id,name,presurvey,postsurvey,action_url FROM project WHERE id = $_id";
        	if ($_result = execute_sql($_sql)) {
            		if (record_count($_result) > 0)
                		list($sid, $_pname, $_pres,$_posts, $_action) = fetch_row($_result);
            		db_close($_result);
        	}
        	unset($_sql);
        	unset($_result);
	}

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" 
"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><?php echo(@$_pname); ?></title>

<style type="text/css">
body {
font-family:Tahoma;
}
a,
a:visited,
a:link {
color:black;
}
a:hover {
text-decoration:none;
}
.finishsurvey {
	display:none;
}
#TB_window {
}
#frameWrapper {
	text-align:center;
	display:none;
}
#webFrame {
	width:80%;
	height:500px;
	margin-top:15px;
}
</style>
<script type="text/javascript" src="<?php echo($ESPCONFIG['js_url']);?>default.js"></script>
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.2.6/jquery.min.js"></script>
<!--<script type="text/javascript" src="<?php echo($ESPCONFIG['js_url']);?>thickbox.js"></script>-->
<script type="text/javascript" src="/public/js/jquery.timers.js"></script>
<script type="text/javascript" src="<?php echo($ESPCONFIG['js_url']);?>rascal.js"></script>
<script type="text/javascript">
var survey = 0;
var change = 1;
window.onbeforeunload = pageExit;

function pageExit() {
  	if (change == 1) {
        return "Survey is not complete or survey video is still being uploaded.";
      }
  }

$(document).ready(function() {
	$('#followed').click(function() {
		$('#gluebox').fadeIn();
		$('#instructions').fadeOut();
	});
	$('a.startTest').click(function() {
		$('.startTest').hide();
		$('.finishsurvey').fadeIn();
		$('#webFrame').attr('src','<?php echo @$_action; ?>');
		$('#frameWrapper').fadeIn();
		started = startRecordingApplet();
		debug.log('started recording = '+started);
	});
	
	
	$('.finishsurveypost').click(function() {
		$('#frameWrapper').slideUp('slow');
		$('#gluebox').slideUp('slow');
		$('#instructions').empty();
		stopped = stopRecordingApplet();
		id = getSessionIdFromApplet();
		$('#instructions').attr('innerHTML','<center><p>We are uploading your testing video and audio, this can take a few minutes...<\/p><br/><img src="/images/ajax-loader.gif"/><\/center><iframe src="/public/survey.php?id=<?php echo($_posts);?>&stype=post&sessionid=<?php echo($id);?>" id="postIframe" width= "950" height="550"></iframe>');
		$('#instructions').fadeIn('fast');
		
		debug.log('stopped recording = '+stopped);
		$(this).everyTime("1s", 'doneCheck', function() {
			isRecording = isRecordingApplet();
			debug.log(isRecording);
			if (isRecording == false) {
				$(this).stopTime();
				$(this).everyTime("1s", 'hasID', function() {
						uploadComplete();
						document.write("Video uploaded successfully. Thank you for completing the survey.");
				});
			}
		});
	});
	
	$('.finishsurvey').click(function() {
		$('#frameWrapper').slideUp('slow');
		$('#gluebox').slideUp('slow');
		$('#instructions').empty();
		$('#instructions').attr('innerHTML','<center><p>We are uploading your testing video and audio, this can take a few minutes...<\/p><br/><img src="/images/ajax-loader.gif"/><\/center>');
		$('#instructions').fadeIn('fast');
		stopped = stopRecordingApplet();
		debug.log('stopped recording = '+stopped);
		$(this).everyTime("1s", 'doneCheck', function() {
			isRecording = isRecordingApplet();
			debug.log(isRecording);
			if (isRecording == false) {
				$(this).stopTime();
				$(this).everyTime("1s", 'hasID', function() {
					debug.log(getSessionIdFromApplet());
					if (getSessionIdFromApplet() != '') {
						id = getSessionIdFromApplet();
						if (id == '') {
							id = '12345667';
						}
						uploadComplete();
						window.location = "/public/survey.php?id=<?php echo($_posts);?>&stype=post&sessionid="+id;
					}
				});
			}
		});
	});
	
	
	var debug = {
		log: function() {
	        if (typeof console == 'object' && typeof console.log != "undefined") {
            	for (var i = 0, l = arguments.length; i < l; i++)
                	console.log(arguments[i]);
            }
        }
    }
    
	function startRecordingApplet(){
		return document.rascal.startRecording();
	}
	function stopRecordingApplet(){
		return document.rascal.stopRecording();
	}

	function isRecordingApplet(){
		return document.rascal.isRecording();
	}
	function getSessionIdFromApplet(){
		return document.rascal.getSessionid();
	}

	function uploadComplete() {
  	change = 0;
  }
  
  function postSurveyComplete() {
  	survey = 1;
  }
  
  function success() {
  	if (change == 1 && upload == 1) {
  		document.write("Thank you for completing the survey");
  	}
  }
});
</script>
<?php
    if (!empty($_css)) {
	    echo('<link rel="stylesheet" href="'. $GLOBALS['ESPCONFIG']['css_url'].$_css ."\" type=\"text/css\" />\n");
    }
    unset($_css);
    
    echo('<link rel="stylesheet" href="'. $GLOBALS['ESPCONFIG']['css_url'].'thickbox.css' ."\" media=\"screen\" type=\"text/css\" />\n");
?>
</head>
<body>
<APPLET name="rascal" ARCHIVE="rascal.jar" CODE="org.fluidproject.vulab.rascal.ui.ScreencastApplet.class" WIDTH="0" HEIGHT="0" mayscript>
	<param name="java_arguments" value="-Xmx512m"/>
	<param name="mode" value="nogui"/>			
</APPLET>
<div id="gluebox">
<?php /*<a href="<?php echo @$_action; ?>?keepThis=true&TB_iframe=true&height=400&width=780" title="Please perform the following test" class="thickbox startTest">Start Test!</a>*/ ?>
<a href="#start" title="Please perform the following test" class="startTest">Start Test!</a>
<a href='#finish' class='finishsurvey'>I'm finished, lets continue.</a>
<?php /*
	if (@$_posts == 0) {
		echo "<a href='#' class='finishsurvey'>Click here after you've clicked \"stop recording\"</a>";
	}
	else {
		echo "<a href='#' class='finishsurvey'>Click here after you've clicked \"stop recording\"</a>";
	}*/
?>
</div>
<div id="frameWrapper">
	<iframe src="" id="webFrame" height="50%"></iframe>
</div>
<div id="instructions" style='padding-left:100px;padding-top:50px;'>
<h1><?php echo $project->details['name']; ?></h1>
<br />
<h2>Introduction</h2>
<p><?php echo $project->details['intro']; ?></p>
<br/>
<?php if ($project->details['goal']) { ?>
	<h2>Study Goal</h2>
	<p><?php echo $project->details['goal']; ?></p>
	<br/>
<?php } ?>
<div style='padding-left:20px;font-size:12px;color:#4F4F4F'>
	<h2>You should know...</h2>
	<p>While taking this online survey your entire screen and your microphone will be recorded until you continue to the final step (experience survey)</p>
	<br/>


</div>
<br/>
<a href="#ok" id='followed'>I understand, I want to continue.</a><br/><br/>
<a href="javascript:self.close();">I understand, and no longer wish to participate</a>
</div>
</body>
</html>
