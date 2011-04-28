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


//Load All Projects for the direct access visitors
$projects = get_projects();

$ids = explode(',',$_GET[id]);

rm_projects($ids);
?>
<h2><?php echo(_('Remove Projects')); ?></h2>
<pre style="text-align:left;">
<?php
	while($project = fetch_row($projects))
	{
		$projects->MoveNext();
		echo "<pre>";
		print_r($project);
		echo "</pre>";
	}
?>
</pre>