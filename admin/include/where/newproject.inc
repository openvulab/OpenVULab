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

session_register('project_name');
//session_register('new_survey');
//session_register('last_tab');
//session_register('curr_q');

/* Use this hack to work around how PHP handles session vars.
 * When Register_Globals is on, the value of the global $foo
 * is saved, and $_SESSION['foo'] is ignored.
 * When Register_Globals is off, the global $foo is ignored
 * and $_SESSION['foo'] is saved.
 * By making $_SESSION['foo'] a copy of $foo
 * when reg_glob is on, we can use $_SESSION uniformly
 * from here on, regardless of the INI settings.
 */
if(ini_get('register_globals')) {
	$_SESSION['project_name']  = $project_name;
	//$_SESSION['new_survey'] = $new_survey;
	//$_SESSION['last_tab']   = $last_tab;
	//$_SESSION['curr_q']     = $curr_q;
}



if($_SESSION['acl']['superuser'] == 'Y') {
	$sql = "SELECT s.id, s.name, s.title, s.owner, s.realm
		FROM ".$GLOBALS['ESPCONFIG']['survey_table']." s WHERE s.status = 0 ORDER BY s.id DESC";
} else {
	$realms = array_to_insql(
	array_intersect(
	$_SESSION['acl']['pall'],
	$_SESSION['acl']['pdesign']));
	$sql = "SELECT s.id, s.name, s.title, s.owner, s.realm
			FROM ".$GLOBALS['ESPCONFIG']['survey_table']." s WHERE s.status = 0 AND (s.owner = ".
	_addslashes($_SESSION['acl']['username']) ." || s.realm $realms) ORDER BY id DESC";
}
$result = execute_sql($sql);

$survey_opts = "";


while(list($sid,$name,$title,$owner,$realm) = fetch_row($result)) {
	$result->MoveNext();
	$survey_opts .= '"<option value="' . $sid .'">' . $title . '</option>';
}

db_close($result); 
?>
</div>
</form>
<?php
function validLink($link) {
    if(preg_match("/http:\/\//", $link)) {
        return true;
    } else {
        return false;
    }
}

if(isset($_POST['submit'])) {
	unset($_POST['submit']);
	/*$project_name = $_POST['project_name'];
	$presurvey = $_POST['presurvey'];
	$postsurvey = $_POST['postsurvey'];
	$preactiontext = $_POST['preactiontext'];
	$postactiontext = $_POST['postactiontext'];
	$actionurl = $_POST['actionurl'];*/
	require ESP_BASE.'admin/sanitize.php';
	$project_name = sanitize($_POST['project_name']);
	$presurvey = sanitize($_POST['presurvey']);
	$postsurvey = sanitize($_POST['postsurvey']);
	$preactiontext = sanitize($_POST['preactiontext']);
	$postactiontext = sanitize($_POST['postactiontext']);
	$actionurl = sanitize($_POST['actionurl']);
	
	$sql = execute_sql("SELECT * FROM `project` WHERE `name` = '".$project_name."'");
	if ($sql->RecordCount() > 0)
	{
		// Project already exists
		echo("<h2>$project_name already exists.</h2>");
	}
	
	// Check the validity of the URL
	elseif (!validLink($actionurl))
	{
		// url is invalid
		echo("<h2>Invalid URL</h2>");
	}
	elseif ($presurvey == $postsurvey && ($presurvey!= -1))
	{
		echo("<h2>Postsurvey can not equal Presurvey</h2>");
	}
	else
	{
	$sqlins = 'insert into project' .
	 '(name,presurvey,postsurvey,action_intro_msg,action_outro_msg,action_url) values ( ' .
	"'$project_name', ".
	"$presurvey, ".
	"$postsurvey, ".
	"'$preactiontext', ".
	"'$postactiontext', ".
	"'$actionurl') ";
	
	$result = execute_sql($sqlins);
	echo ErrorMsg();
	
	$sqlresults = "select * from project WHERE name = '".$project_name."'";
	$result = execute_sql($sqlresults);
	$projectid = $result->fields[0];
	
	// Insert into userprojectrel table
	$sqlins = "insert into userprojectrel values ('','".$_SESSION['acl']['userid']."','".$projectid."','Y')";
	
	$result = execute_sql($sqlins);
	echo ErrorMsg();
	// Insert the root user record
	$sqlins = "insert into userprojectrel values ('','6','".$projectid."','Y')";
	
	$result = execute_sql($sqlins);
	echo ErrorMsg();
	
	$sql = "UPDATE `survey` SET `status` = '1' WHERE `id` = '$presurvey'";
	execute_sql($sql);
	$sql = "UPDATE `survey` SET `status` = '1' WHERE `id` = '$postsurvey'";
	execute_sql($sql);
	
	
	
	echo "<h2> $project_name added. </h2>";
	}
		
} else {

?>
<h2><?php echo(_('Create A New Project')); ?></h2>
<form method="post" name="newprojectform"
	action="<?php echo($ESPCONFIG['ME'])."?where=newproject"; ?>">
<div align="center">
<table>
	<tr>
		<td align="right">Project Name:</td>
		<td align="left"><input type="text" id="project_name"
			name="project_name" maxlength="40" /></td>
	</tr>
	<tr>
		<td align="right">Pre-Survey:</td>
		<td align="left"><select name="presurvey">
			<option value="-1">none</option>
			<?php
			echo $survey_opts;
			?>
		</select>
		<a href="<?php echo($ESPCONFIG['ME'])."?where=new"; ?>">create a new survey</a>
		</td>
	</tr>
	<tr>
		<td align="right">Post-Survey:</td>
		<td align="left"><select name="postsurvey">
			<option value="-1">none</option>
			<?php
			echo $survey_opts;
			?>
		</select>
		<a href="<?php echo($ESPCONFIG['ME'])."?where=new"; ?>">create a new survey</a>
		</td>
	</tr>
	<!--
	<tr>
		<td align="right">Pre-Action Text:</td>
		<td align="left"><textarea rows="4" cols="40" name="preactiontext"></textarea>
		</td>
	</tr>
	<tr>
		<td align="right">Post-Action Text:</td>
		<td align="left"><textarea rows="4" cols="40" name="postactiontext"></textarea>
		</td>
	</tr>
	-->
	<tr>
		<td align="right">URL of Action:</td>
		<td align="left"><input type="text" value="http://" name="actionurl" />
		</td>
	</tr>

</table>
<input type="reset" value="Reset"> <input type="submit" name="submit"
	value="Create"></div>
</form>
			<?php } ?>