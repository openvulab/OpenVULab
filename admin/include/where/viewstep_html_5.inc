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
File: 		step_html_5.inc \\v 1.0
Info:		for ?where=create&step=5 (invite users)
Author: 	Blake Edwards
Email:		electBlake@gmail.com

License: 	http://source.fluidproject.org/svn/fluid/components/trunk/LICENSE.txt
*/
?>
<div class="field_lines">
<div class="left">
	<h1>Select Testers to Invite</h1>
</div>
<div class="right">
		<strong>Go To: <a href="?where=view&amp;pid=<?php echo($_SESSION['pid']);?>">Results</a> | <a href="?where=viewall&amp;type=active">Active Projects</a></strong>
</div>
<div class="clear"></div>
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
$fields = array('option_checkbox','userid','username','fname','lname');
$aliases = array('userid'=>'User ID','username'=>'Username','fname'=>'First name','lname'=>'Last name');
$options = array('titles'=>true,'aliases'=>$aliases);
$testers = getUsers('tester');
$active = array();
foreach ($testers as $k => $tester) {
	$tester = new Perm('user',$tester->id);
	if (!is_numeric($tester->id) OR $tester->checkUser($project->id)) {
		$active[] = $testers[$k];
		unset($testers[$k]);
	}
}
if (count($testers) > 0) 
	echo '<input type="submit" value="Invite Users"/>';
unset ($active[count($active) - 1]); //Removes last entry, which is blank
echo display_users_table($fields,$testers,$options);
unset ($fields);
?>
<input type="hidden" name="from" value="5" id="from" />
<input type="hidden" name="go" value="5" id="go" />
<input type="hidden" name="where" value="view" id="where" />

<?php
if (count($testers) > 0) 
	echo '<input type="submit" value="Invite Users" />';
	?>
<div class="clear"></div><br/>
<h1>Active Testers</h1>
<?php 
	$fields = array('option_none','userid','username','fname','lname');
	echo display_users_table($fields,$active,$options);
?>
</div>