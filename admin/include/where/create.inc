<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/
?><?php
/*
File: 		create.inc \\v 1.0
Info:		- File designed to handle all project creation/editing and survey (iframed) creation.
Author: 	Blake Edwards
Email:		electBlake@gmail.com

License: 	http://source.fluidproject.org/svn/fluid/components/trunk/LICENSE.txt
*/
?>
<?php
//error_reporting(E_ALL);
//ini_set('display_errors', '1');

//session_start();
//error_reporting(E_ALL);
ini_set('display_errors', '1');

/* $Id: create.inc,v 1.32 2007/12/03 13:08:13 liedekef Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

// Written by James Flemer
// For eGrad2000.com
// <jflemer@alum.rpi.edu>
//Some Legacy
$base =& $GLOBALS['ESPCONFIG']['ME'];
$bg = '';
////////////////


//Manage Modes
if ($_GET['where'] == 'create') {
	$_SESSION['mode'] = 'create';
	unset($_SESSION['pid']);
	unset($_SESSION['renamed']);
	unset($_SESSION['last_tab']);
	unset($_SESSION['curr_q']);
	unset($_SESSION['survey_id']);
	unset($_SESSION['new_survey']);
}
if ($_GET['pid']) {
	$_SESSION['mode'] = 'edit';
	$_SESSION['pid'] = $_GET['pid'];
}
//Popoulate edit mode
if ($_SESSION['mode'] == 'edit' AND $_SESSION['pid']) {
	$project = new Project;
	$project->init($_SESSION['pid']);
}

//Lets Figure out our Navigation Vars
$step = $_POST['step'];
if ($_GET['step']) { $step = $_GET['step']; }
if ($_POST['go']) { $step = $_POST['go']; }

if ($_POST['where_sub'] OR $_GET['where_sub']) {
	if ($_POST['where_sub']) {
		$step = $_POST['where_sub'];
	} else {
		$step = $_GET['where_sub'];
	}
}


if (!$step OR strtolower($step)== 'first' OR strtolower($step) == 'start') { $step = 1; }
$from = $_POST['from'];


//If there has been a step change, lets process!
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
	include(esp_where("step_process_$from"));
}

$stepswitch[$step] = 'on';
	if ($_SESSION[debug]) {
/*		if (@$project) {
			echo "<script type='text/javascript'>\n";
			echo "alert('asdfsf');\n";
			echo "$('.debug').append('";
			echo '<strong>project</strong>';
			print_r($project);
			echo "');\n";
			echo "</script>";		
		}*/
	
	}
if ($project->details['status'] == '2') {

}
?>
<div class="project_container">
<div id="project_topnav">
<div class="right">

<a href="#save"><img src="../images/save.png" alt="" />Save Project</a>

<a href="?where=deleteproject&amp;lay=ajax&amp;id=<?php echo($project->id);?>&amp;KeepThis=true&amp;TB_iframe=true&amp;height=200&amp;width=450" class="thickbox" title="Are you sure you want to delete this project?"><img src="../images/delete.png" alt="" />Delete Project</a>

<a href="?where=manage"><img src="../images/exit.png" alt="" />Exit Project</a>

<!--<a href="?where=activateproject&amp;lay=ajax&amp;id=<?php echo($project->id);?>&amp;KeepThis=true&amp;TB_iframe=true&amp;height=200&amp;width=450" class="thickbox activatebutton" title="Are you sure you want to activate this project?"><img src="../images/world_go.png" alt="Delete" />Activate Project</a>--></div>

<h1>Project: <?php echo ($project->details[name] ? $project->details[name] : "Untitled"); ?> <small>(draft)</small></h1>
</div>
<div id="steps">
        <input type="image" src="../images/steps1_<?php echo($stepswitch[1]);?>.png" value="1" onclick="getElementById('go').value='1';getElementById('where_sub').value=''" alt="<?php if($step==1) echo("Current Step."); else echo("Step One."); ?> Project Details"/>
        <input type="image" src="../images/steps2_<?php echo($stepswitch[2]);?>.png" value="2" onclick="getElementById('go').value='2';getElementById('where_sub').value=''" alt="<?php if($step==2) echo("Current Step."); else echo("Step Two."); ?> Create Pre Test Survey"/>
        <input type="image" src="../images/steps3_<?php echo($stepswitch[3]);?>.png" value="3" onclick="getElementById('go').value='3';getElementById('where_sub').value=''" alt="<?php if($step==3) echo("Current Step."); else echo("Step Three."); ?> Create Post Test Survey"/>
        <input type="image" src="../images/steps4_<?php echo($stepswitch[5]);?>.png" value="4" onclick="getElementById('go').value='5';getElementById('where_sub').value=''" alt="<?php if($step==5) echo("Current Step."); else echo("Step Four."); ?> Manage Project Testers"/>
        <!--<input type="image" src="../images/steps5_<?php echo($stepswitch[4]);?>.png" value="5" onclick="getElementById('go').value='4';getElementById('where_sub').value=''" alt="<?php if($step==4) echo("Current Step."); else echo("Step Five."); ?> Activate Project"/>-->
        <a href="?where=activateproject&amp;lay=ajax&amp;id=<?php echo($project->id);?>&amp;KeepThis=true&amp;TB_iframe=true&amp;height=200&amp;width=450" class="thickbox"title="Are you sure you want to activate this project?">
            <img src="../images/steps5_.png" alt="Activate Project"/>
        </a>
</div>
<?php
if ($err) { 
	echo "<div id='errors'>";
	foreach ($err as $msg) {
		if (is_array($msg)) {
			foreach ($msg as $m) { echo "<div>$m</div>"; }
		} else {
			echo "<div>$msg</div>";
		}
	}
	echo "</div>";
}
if ($note) { 
	echo "<div id='notes'>";
	foreach ($note as $msg) {
		echo "<div>$msg</div>";
	}
	echo "</div>";
}
if ($good) { 
	echo "<div id='goods'>";
	foreach ($good as $msg) {
		echo "<div>$msg</div>";
	}
	echo "</div>";
}
?>
<?php
	if ($step == '1') { 

		include(esp_where("step_html_$step"));

 	}
 	if ($step == '2') { 
 	
		include(esp_where("step_html_$step"));
	
	}
	if ($step == '3') {
	
		include(esp_where("step_html_$step"));
	}
	if ($step == '4') { 
	
		include(esp_where("step_html_$step"));
	}
	if ($step == '5') {
	
		include(esp_where("step_html_$step"));
	}
?>
<div class="clear"></div>
</div>
<?php
if (!empty($_POST)) {
	echo "<div id='postdata'>";
	foreach($_POST as $name=>$value) {
		echo "$name=$value&amp;";
	}
	echo "</div>";
}
?>