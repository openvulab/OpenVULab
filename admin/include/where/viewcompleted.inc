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
session_start();

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
if ($_GET[where] == 'create') {
	$_SESSION['mode'] = 'create';
	unset($_SESSION[pid]);
	unset($_SESSION[renamed]);
	unset($_SESSION[last_tab]);
	unset($_SESSION[curr_q]);
	unset($_SESSION[survey_id]);
	unset($_SESSION[new_survey]);
}
if ($_GET['pid']) {
	$_SESSION['mode'] = 'manage';
	$_SESSION['pid'] = $_GET['pid'];
}
//Popoulate edit mode
if ($_SESSION['mode'] == 'manage' AND $_SESSION['pid']) {
	$project = new Project;
	$project->init($_SESSION[pid]);
}

//Lets Figure out our Navigation Vars
$step = $_POST[step];
if ($_GET[step]) { $step = $_GET[step]; }
if ($_POST[go]) { $step = $_POST[go]; }

if ($_POST[where_sub] OR $_GET[where_sub]) {
	if ($_POST[where_sub]) {
		$step = $_POST[where_sub];
	} else {
		$step = $_GET[where_sub];
	}
}


if (!$step OR strtolower($step)== 'first' OR strtolower($step) == 'start') { $step = 5; }
$from = $_POST[from];


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

	
	$postid = $project->post_survey['id'];
    $ridSQL = "SELECT * FROM `response` WHERE `survey_id` = '$postid'";
    $ridResult = execute_sql($ridSQL);
    $ridCount = 0;
    while ($ridRow = fetch_row($ridResult)) {
    	if ($ridCount > 0) {
    		break;
    	}
    	$ridResult->MoveNext();
    	$firstPostRid = $ridRow[0];
    	++$ridCount;
    }
    
	$preid = $project->pre_survey['id'];
    $ridSQL = "SELECT * FROM `response` WHERE `survey_id` = '$preid'";
    $ridResult = execute_sql($ridSQL);
    $ridCount = 0;
    while ($ridRow = fetch_row($ridResult)) {
    	if ($ridCount > 0) {
    		break;
    	}
    	$ridResult->MoveNext();
    	$firstPreRid = $ridRow[0];
    	++$ridCount;
    }
    
?>

<div class="project_container">
<div id="project_topnav">
<div class="right"><a href="?where=deleteproject&amp;lay=ajax&amp;id=<?php echo($project->id);?>&amp;KeepThis=true&amp;TB_iframe=true&amp;height=200&amp;width=450" class="thickbox" title="Are you sure you want to delete this project?"><img src="../images/delete.png" alt="Delete" />Delete Project</a><a href="?where=activateproject&amp;lay=ajax&amp;id=<?php echo($project->id);?>&amp;KeepThis=true&amp;TB_iframe=true&amp;height=200&amp;width=450" class="thickbox activatebutton" title="Are you sure you want to activate this project?"><img src="../images/world_go.png" alt="Delete" />Re-Activate Project</a><a href="?where=manage"><img src="../images/exit.png" alt="Exit"/>Exit</a></div>
<h2>Project: <?php echo ($project->details[name] ? $project->details[name] : "Untitled"); ?> <small class="green">(completed)</small></h2>
</div>
<div id="steps">
<div class="left">
		<h1>Results:</h1>
	</div>
	<div class="right">
		<strong>Go To: <a href="?where=viewall&amp;type=completed">Completed Projects</a> | <a href="?where=viewall&amp;type=active">Active Projects</a></strong>
	</div>
	<div class="clear"></div>
<div style="margin-left:20px;text-align:left;font-size:13px;">
	<strong>
	<?php if ($project->pre_survey['id']) { echo '<a href="?where=results&amp;pid='.$project->id.'&amp;sid='.$project->pre_survey['id'].'">Pre-Survey Totals</a>'; }?>
	<?php if ($project->pre_survey['id'] AND $project->post_survey['id']) { echo ' - '; }?>
	<?php if ($project->post_survey['id']) { echo '<a href="?where=results&amp;pid='.$project->id.'&amp;sid='.$project->post_survey['id'].'">Post-Survey Totals</a>'; } ?>
	- <a href="?where=results&amp;pid=<?php echo($project->id);?>&amp;sid=<?php echo($project->post_survey['id']);?>&amp;rid=<?php echo($firstPostRid);?>">Browse Videos &amp; Responses by User</a>
	</strong>
	<br />
</div>

</div>
<div style="clear:both;"></div>
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
<div class="clear"></div>
</div>

<?php
if (!empty($_POST)) {
	echo "<div id='postdata'>";
	foreach($_POST as $name=>$value) {
		echo "$name=$value&";
	}
	echo "</div>";
}
?>
<?php 
		$statusok = (STATUS_ACTIVE | STATUS_DONE);
    $statusno = STATUS_DELETED;
    if ($_SESSION['acl']['superuser'] == 'Y') {
        $sql = "SELECT submitted,username,vid FROM ".$GLOBALS['ESPCONFIG']['response_table']."
        WHERE `vid` != '' AND `survey_id` =".$project->post_survey['id']." AND complete = 'Y'";
    } else {
        $realms = array_to_insql(
            array_intersect(
                $_SESSION['acl']['pall'],
                $_SESSION['acl']['pdata']));
                $sql = "SELECT submitted,username,vid
                FROM ".$GLOBALS['ESPCONFIG']['response_table']." WHERE `vid` != '' AND `survey_id` =".$project->post_survey['id']." AND complete = 'Y'";
    }
    $result = execute_sql($sql);
    ?>
    <div class="project_container">
    <h1>Videos:</h1>
	<table cellspacing="0" cellpadding="4">
    <tr class="header">
    <th><?php echo(_('User ID')); ?></th>
			<th><?php echo(_('Username')); ?></th>
			<th><?php echo(_('Date Submitted')); ?></th>
			<th><?php echo(_('Video')); ?></th>
	    </tr>
    <?php
    	$count = 0;
      while(list($submitted,$userid,$vid) = fetch_row($result)) {	
      		$count++;
          $result->MoveNext();
          if($bg != $ESPCONFIG['bgalt_color1'])
          $bg = $ESPCONFIG['bgalt_color1'];
          else
          $bg = $ESPCONFIG['bgalt_color2'];
      ?>
  		<tr style="background-color: <?php echo($bg); ?>; text-align:left">
  		<td><?php echo($userid);?></td>
  		<?php
  		$realms = array_to_insql(
          array_intersect(
              $_SESSION['acl']['pall'],
              $_SESSION['acl']['pdata']));
          $sql = "SELECT username FROM ".$GLOBALS['ESPCONFIG']['user_table']." WHERE `userid` =".$userid;
          $uid_result = execute_sql($sql);
          while (list($username) = fetch_row($uid_result)) {
                  $uid_result->MoveNext();
      ?>
  			<td><?php echo($username);?></td>
    	<?php } ?>
    			<td><?php echo ($submitted); ?></td>
          <td><a href="http://130.63.175.158/files/<?php echo($vid); ?>/<?php echo($vid).'.avi'; ?>"><?php echo($vid).".avi"; ?></a></td>
              </tr>
              <?php
      }
      if ($count == 0)
      	echo '<tr><td COLSPAN=4><span style="font-style:italic; font-weight:bold; color:#00336F; font-size:13px">No Video Submitted</span></td></tr>';
      db_close($result);
    ?>
    </table></div>