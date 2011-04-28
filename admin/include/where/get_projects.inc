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
//error_reporting(E_ALL);
echo "asdfadF";
echo "<pre>";
print_r(get_projects_by('6','1'));
echo "</pre>";


function get_projects_by($ownerid,$status) {
	if (!is_numeric($status)) { 
		if (strtolower($status) == 'draft' OR strtolower($status) == 'drafts' OR strtolower($status) == 'd') { $status = 1; }
		if (strtolower($status) == 'active' OR strtolower($status) == 'a') { $status = 2; }
		if (strtolower($status) == 'complete' OR strtolower($status) == 'completed' OR strtolower($status) == 'c') { $status = 3; }
	}
	$getSQL = "
	SELECT `project`.*
	FROM userprojectrel, project
	WHERE
		`userprojectrel`.projectid = `project`.`id`
		AND `userprojectrel`.`userid` = '$ownerid'
		AND `project`.`status` = '$status'
	";
	
	$proj_result = execute_sql($getSQL);
	while (!$proj_result->EOF) {
		
		
		list(	$p['id'],
				$p['name'],
				$p['pre_id'],
				$p['post_id'],
				$p['intro'],
				$p['outro'],
				$p['url'],
				$p['start'],
				$p['end'],
				$p['status'],
				$p['createstamp'],
				$p['editstamp'],
				$p['activestamp'],
				$p['completestamp']) = $proj_result->fields;	
		$p = array_reverse($p);
		print_r($p);
		$project = new Project;
		print_r($project->init($p['id']));
		
		$proj_result->MoveNext();
	}
	
	return $projects;
}

?>