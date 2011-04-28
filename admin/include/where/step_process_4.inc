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
if ($_SESSION['mode'] == 'edit') {
	//Make markers to remove emptied fields
	

	
	if ($_POST['activate'] == 'true') {
		$data = array('status'=>'2');
		$editresult = $project->update($data);
		$preid = $project->pre_survey['id'];
		$postid = $project->post_survey['id'];
		
		$surveydata = array('status'=>'1');
		if ($preid) {
			$pre_survey = new Survey($preid);
			$preresult = $pre_survey->update($surveydata);
			if (!$preresult) {
				$err[] = 'Error Updating Pre-Survey Status';
			}
		}
		if ($postid) {
			$post_survey = new Survey($postid);
			$postresult = $post_survey->update($surveydata);
			if (!$postresult) {
				$err[] = 'Error Updating Post-Survey Status';
			}
		}
		if (is_array($editresult)) {
			//set errors
			$err = $editresult;
		} else { //Set Success
			unset($project);
			$project = new Project;
			$project->init($_SESSION[pid]);
		}
	}
}
if (is_array($err)) {
	$step = $from;
}


?>