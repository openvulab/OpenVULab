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
//print_r($_SESSION);
error_reporting(E_ALL);
require ESP_BASE.'admin/sanitize.php';
if (!isset($_GET['project']))
{
	echo "<h2>My Projects</h2>";
	$sql = "SELECT * FROM `userprojectrel` WHERE `userid` = '".$_SESSION['acl']['userid']."' AND `admin` = 'Y'";
	$result = execute_sql($sql);
	$project_id = $result->fields[2];

	$sql = "SELECT * FROM `project` WHERE `id` = '$project_id'";

	$result = execute_sql($sql);

	$projects = array();
	while (!$result->EOF) {
		$projects[] = array($result->fields[1],$result->fields[0]);
		$result->MoveNext();
	}
	foreach ($projects as $project)
	{
		echo "<br /><a href='?where=testersproject&project=".$project[1]."'>".$project[0]."</a></li></ul>"; 
	}
}
else
{
	$sql = "SELECT * FROM `userprojectrel` WHERE `userid` = '".$_SESSION['acl']['userid']."' AND `admin` = 'Y' AND `projectid` = '".sanitize($_GET['project'])."'";
	$result = execute_sql($sql);
	if ($result->RecordCount() == 0)
		die("You are not authorized to view this project!");
	displayTheForm();
}
function displayTheForm()
{
?>
</form>
<h2>Add Tester to a Project</h2>
<form method="post" name="tpsaveform" action="<?php echo($GLOBALS['ESPCONFIG']['ME']);?>?where=tpsave">
<input type="hidden" name="project" value="<?php echo($_GET['project']);?>" />
<div align="center">
<table>
	<tr>
		<td align="right">Tester Name:</td>
		<td align="left">
			<select name="tester">
<?php
$sql = "SELECT * FROM `user` WHERE `isresearcher` = 'N'";
$result = execute_sql($sql);
$users = array();
while (!$result->EOF) {
		$users[] = array($result->fields[1],$result->fields[0]);
		$result->MoveNext();
}
foreach ($users as $user)
	echo "<option value='$user[1]'>$user[0]</option>";
?>
			</select>
		</td>
	</tr>
	<tr>
		<td align="right">Administrator?</td>
		<td align="left">
			<input type="radio" name="admin" value="1" />Yes<br />
			<input type="radio" name="admin" value="0" checked="checked" />No
		</td>
	</tr>
</table>
<input type="reset" value="Reset"> <input type="submit" name="submit"
	value="Add Tester"></div>
</form>
<?php
}
?>