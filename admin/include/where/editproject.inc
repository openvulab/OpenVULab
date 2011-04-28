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

	//error_reporting(E_ALL);
	
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


require ESP_BASE.'admin/sanitize.php';


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
	$project_name = sanitize($_POST['project_name']);
	$presurvey = sanitize($_POST['presurvey']);
	$postsurvey = sanitize($_POST['postsurvey']);
	$preactiontext = sanitize($_POST['preactiontext']);
	$postactiontext = sanitize($_POST['postactiontext']);
	$actionurl = sanitize($_POST['actionurl']);

	// Check the validity of the URL
	if (!validLink($actionurl))
	{
		// url is invalid
		echo("<h2>Invalid URL</h2>");
	}
//	elseif ($presurvey == $postsurvey)
//	{
//		echo("<h2>Postsurvey can not equal Presurvey</h2>");
//	}
	else
	{
	$sqlins = 'update project set' .
	"`name` = '$project_name', ".
	"`presurvey` = $presurvey, ".
	"`postsurvey` = $postsurvey, ".
	"`action_intro_msg` = '$preactiontext', ".
	"`action_outro_msg` = '$postactiontext', ".
	"`action_url` = '$actionurl' WHERE `id` = '$_GET[id]'";
	
	$result = execute_sql($sqlins);
	//echo $sqlins;
	echo ErrorMsg();
	
	$sql = "UPDATE `survey` SET `status` = '1' WHERE `id` = '$presurvey'";
	execute_sql($sql);
	$sql = "UPDATE `survey` SET `status` = '1' WHERE `id` = '$postsurvey'";
	execute_sql($sql);
	
	
	
	echo "<h2> $project_name edited. </h2>";
	}
		
} else {
	$id = sanitize($_GET['id']);
	$userid = sanitize($_SESSION['acl']['userid']);
	if ($_SESSION['acl']['superuser'] != 'Y')
	{
		$sql = "SELECT * FROM `userprojectrel` WHERE `userid` = '$userid' AND `projectid` = '$id' AND `admin` = 'Y'";
		
		//echo $sql."<br />";
		
		$result = execute_sql($sql);
		if ($result->RecordCount() <= 0)
		{
			die();
		}
	}
	$sql = "SELECT * FROM `project` WHERE `id` = '$id'";
	
		//echo $sql."<br />";
	
	$result = execute_sql($sql);
	
	if($_SESSION['acl']['superuser'] == 'Y') {
		$sql = "SELECT s.id, s.name, s.title, s.owner, s.realm
			FROM ".$GLOBALS['ESPCONFIG']['survey_table']." s ORDER BY s.id DESC";
			
	} else {
		$realms = array_to_insql(
		array_intersect(
		$_SESSION['acl']['pall'],
		$_SESSION['acl']['pdesign']));
		$sql = "SELECT s.id, s.name, s.title, s.owner, s.realm
				FROM ".$GLOBALS['ESPCONFIG']['survey_table']." s WHERE (s.owner = ".
		_addslashes($_SESSION['acl']['username']) ." || s.realm $realms) ORDER BY id DESC";
	}
	
			//echo $sql."<br />";
	
	$result2 = execute_sql($sql);

	$survey_opts_pre = "";
	$survey_opts_post = "";
	while(list($sid,$name,$title,$owner,$realm) = fetch_row($result2)) {
		$result2->MoveNext();
		$survey_opts_pre .= '"<option value="' . $sid .'" ';
		if ($sid == $result->fields[2])
			$survey_opts_pre .= "SELECTED";
		$survey_opts_pre .= '>' . $title . '</option>';
		
		$survey_opts_post .= '"<option value="' . $sid .'" ';
		if ($sid == $result->fields[3])
			$survey_opts_post .= "SELECTED";
		$survey_opts_post .= '>' . $title . '</option>';
	}
?>
<h2><?php echo(_('Edit Project')); ?></h2>
<form method="post" name="editprojectform"
	action="<?php echo($ESPCONFIG['ME'])."?where=editproject&id=$id"; ?>">
<div align="center">
<table>
	<tr>
		<td align="right">Project Name:</td>
		<td align="left"><input type="text" id="project_name"
			name="project_name" value="<?php echo($result->fields[1]);?>" maxlength="40" /></td>
	</tr>
	<tr>
		<td align="right">Pre-Survey:</td>
		<td align="left"><select name="presurvey">
			<option value="-1">none</option>
			<?php
			echo $survey_opts_pre;
			?>
		</select>
		<a href="<?php echo($ESPCONFIG['ME'])."?where=new"; ?>">create a new survey</a>
		</td>
	</tr>
	<tr>
		<td align="right">Post-Survey:</td>
		<td align="left"><select name="postsurvey">
			<option value="-1">none</option>
			<?
			echo $survey_opts_post;
			?>
		</select>
		<a href="<?php echo($ESPCONFIG['ME'])."?where=new"; ?>">create a new survey</a>
		</td>
	</tr>
	<tr>
		<!--
		<td align="right">Pre-Action Text:</td>
		<td align="left"><textarea rows="4" cols="40" name="preactiontext"><?php echo($result->fields[4]);?></textarea>
		</td>
		
	</tr>
	<tr>
		<td align="right">Post-Action Text:</td>
		<td align="left"><textarea rows="4" cols="40" name="postactiontext"><?php echo($result->fields[5]);?></textarea>
		</td>
		-->
	</tr>
	<tr>
		<td align="right">URL of Action:</td>
		<td align="left"><input type="text" value="<?php echo($result->fields[6]);?>" name="actionurl" />
		</td>
	</tr>

</table>
<input type="reset" value="Reset"> <input type="submit" name="submit"
	value="Save"></div>
</form>
			<?php } ?>